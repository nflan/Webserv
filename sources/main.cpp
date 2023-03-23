/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:39:03 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/23 17:25:43 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sys/epoll.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <arpa/inet.h>
#include <fcntl.h>
#include <csignal>

#include "server_configuration.hpp"
#include "server_response.hpp"

#define READ_SIZE 1000
#define MAX_EVENTS 10

void sigint_handler(int signum)
{
    std::cerr << "\nSignal SIGINT (" << signum << ") received." << std::endl;
	close(8083); // Port 1
	close(8086); // Port 2
	close(3); // listen_socket 1
	close(4); // listen_socket 2
	close(5); // epoll_create1
	close(6); // accept AF_INET socket conn_sock ev.data.fd Conf1
	close(7); // accept AF_INET socket conn_sock ev.data.fd Conf1
	close(8); // accept AF_INET socket conn_sock ev.data.fd Conf2
	close(9); // accept AF_INET socket conn_sock ev.data.fd Conf2
	// close(0); // bind listen
	// close(1); // nfds

}

void DeleteServers(std::vector<server_configuration*> servers)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		delete servers[i];
	}
}

int setnonblocking(int sockfd) {
	int flags;
	flags = fcntl(sockfd, F_GETFL, 0);
	if (flags == -1) {
		return -1;
	}
	flags |= SOCK_NONBLOCK;
	if (fcntl(sockfd, F_SETFL, flags) == -1) {
		return -1;
	}
	return 0;
}

void handle_connection(server_configuration *servers, int conn_sock) {
	char buffer[1024];
	int n = read(conn_sock, buffer, 1024);
	if (n <= 0) {
		// close(conn_sock);
		return;
	}
	buffer[n] = '\0';
	std::string request;
	request.append(buffer);
	while (n > 0)
	{
		n = read(conn_sock, buffer, 1024);
		if (n > 0)
			request.append(buffer);
	}
	// std::cout << request << std::endl;
	server_request* ServerRequest = new server_request(request);
	server_response ServerResponse;
	ServerResponse.todo(*ServerRequest, conn_sock, servers->getRoot());
	// std::string answer = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	// std::cout << *ServerRequest << std::endl;
	// write(conn_sock, answer.c_str() , strlen(answer.c_str()));
	delete ServerRequest;
}

void	CloseSockets(int *listen_sock, int tablen, std::vector<server_configuration*> servers, sockaddr_in *addr)
{
	for (int i = 0; i < tablen; i++)
	{
		close(listen_sock[i]);
		close(servers[i]->getPort());
		close(addr[i].sin_port);
	}
}

int StartServer(std::vector<server_configuration*> servers, int tablen)
{
	struct sockaddr_in addr[tablen];
	socklen_t addrlen[tablen];
	int conn_sock, nfds, epollfd;
	int listen_sock[tablen];
	
	for (int i = 0; i < tablen; i++)
	{
		addrlen[i] = sizeof(addr[i]);
		listen_sock[i] = socket(AF_INET, SOCK_STREAM, 0);
		if (listen_sock[i] == -1) {
			std::fprintf(stderr, "Error: cannot create socket: %s\n", strerror(errno));
			return(EXIT_FAILURE);
		}
		memset(&addr[i], 0, sizeof(addr[i]));
		addr[i].sin_family = AF_INET;
		addr[i].sin_addr.s_addr = htonl(INADDR_ANY);
		addr[i].sin_port = htons(servers[i]->getPort());

		int val = 1;
		if (setsockopt(listen_sock[i], SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val)) < 0) {
			std::fprintf(stderr, "Error: setsockopt() failed: %s\n", strerror(errno));
			return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
		}
		if (bind(listen_sock[i], (struct sockaddr *) &addr[i], addrlen[i]) == -1) {
			std::fprintf(stderr, "Error: bind failed: %s\n", strerror(errno));
			return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
		}
		if (listen(listen_sock[i], SOMAXCONN) == -1) {
			std::fprintf(stderr, "Error: listen failed: %s\n", strerror(errno));
			return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
		}
	}

	epollfd = epoll_create1(0);
	if (epollfd == -1) {
		std::fprintf(stderr, "Error: epoll_create1: %s\n", strerror(errno));
		return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
	}


	struct epoll_event ev, events[MAX_EVENTS];

	for (int i = 0; i < tablen; i++)
	{
		ev.events = EPOLLIN;
		ev.data.fd = listen_sock[i];
		if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock[i], &ev) == -1) 
		{
			std::fprintf(stderr, "Error: epoll_ctl: listen_sock, %s\n", strerror(errno));
			return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
		}
	}

	for (;;) {
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			std::fprintf(stderr, "Error: epoll_wait: %s\n", strerror(errno));
			return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
		}
		for (int n = 0; n < nfds; ++n) {
			for (int i = 0; i < tablen; i++)
			{
				if (events[n].data.fd == listen_sock[i])
				{
					conn_sock = accept(listen_sock[i], (struct sockaddr *) &addr[i], &addrlen[i]);
					if (conn_sock == -1) {
						std::fprintf(stderr, "Error: server accept failed: %s\n", strerror(errno));
						return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
					}
					if (setnonblocking(conn_sock) == -1) {
						std::fprintf(stderr, "Error: setnonblocking: %s\n", strerror(errno));
						return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
					}
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = conn_sock;
					if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
						std::fprintf(stderr, "Error: epoll_ctl: conn_sock, %s\n", strerror(errno));
						return(CloseSockets(listen_sock, tablen, servers, addr), EXIT_FAILURE);
					}
				} else {
					handle_connection(servers[i], events[n].data.fd);
				}
			}
		}
	}
	return 0;
}


std::vector<server_configuration*> SetupNewServers(std::string filename)
{
	std::ifstream input_file(filename.c_str());

	if (!input_file.is_open()) {
		std::cout << "Failed to open file " << filename << std::endl;
		exit (-1) ;
	}
	
	std::vector<server_configuration*> servers;
	std::string ConfigFileStr;
	std::getline(input_file, ConfigFileStr, '\0');
	
	while (ConfigFileStr.find("server {") != std::string::npos)
	{
		server_configuration* myserver = new server_configuration(ConfigFileStr);
		servers.push_back(myserver);
		size_t pos1 = ConfigFileStr.find("server {");
		if (pos1 != std::string::npos)
		{
			size_t pos2 = ConfigFileStr.find("server {", pos1 + 1);
			if (pos2 != std::string::npos)
				ConfigFileStr = ConfigFileStr.substr(pos2);
			else
				ConfigFileStr = ConfigFileStr.substr(ConfigFileStr.size());
			if (DEBUG)
				std::cout << " main " << ConfigFileStr << std::endl;
		}
	}
	return (servers);
}

void PrintServer(std::vector<server_configuration*> servers)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		server_configuration* server = servers[i];
		std::cout << "Server " << i << ":" << std::endl;
		std::cout << *server << std::endl;
	}
	
	// ANOTHER WAY OF DOING IT USING ITERATOR
	// for (std::vector<server_configuration*>::iterator it = servers.begin(); it != servers.end(); ++it)
	// {
	//     server_configuration* server = *it;
	//     // std::cout << "Server " << std::distance(servers.begin(), it) << ":" << std::endl;
	//     std::cout << *server << std::endl;
	// }
}

int main(int argc, char const **argv)
{
	if (argc != 2)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return -1;
	}
	signal(SIGINT, sigint_handler);

	std::vector<server_configuration*> servers = SetupNewServers(argv[1]);
	// PrintServer(servers);
	StartServer(servers, servers.size());
	DeleteServers(servers);
	return 0;
}