/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:39:03 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/17 16:48:29 by mgruson          ###   ########.fr       */
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
#include <unistd.h>    // for close(), read()
#include <sys/epoll.h> // for epoll_create1(), epoll_ctl(), struct epoll_event
#include <string.h>    // for strncmp
#include <iostream>
#include <vector>
#include <iterator>

#define MAX_EVENTS 5
#define READ_SIZE 1000
#define PORT 8085

#include "server_configuration.hpp"

int getServerFd(server_configuration *server)
{
	(void)server;

	int		new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	int server_fd;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;

	address.sin_addr.s_addr = INADDR_ANY;
	std::cout << "server.getPort " << server->getPort() << std::endl;
	address.sin_port = htons( server->getPort() );
	memset(address.sin_zero, '\0', sizeof address.sin_zero);


	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("In bind");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 2) < 0)
	{
		perror("In listen");
		exit(EXIT_FAILURE);
	}

	std::cout << "Waiting for acception" << std::endl;
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
	{
		perror("In accept");
		exit(EXIT_FAILURE);
	}
	return (new_socket);
}

int	start_server(int new_socket)
{

	std::string answer = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	char read_buffer[READ_SIZE + 1];
	struct epoll_event events[MAX_EVENTS];
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1) {
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}
	
	int i = 0;
	events[i].events = EPOLLIN; 
	events[i].data.fd = new_socket;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &events[i])) {
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(epoll_fd);
		return 1;
	}
	int event_count = 0;
	while (1) {
		std::cout << "Waiting for new request" << std::endl;
		event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
		std::cout << "Polling for input..." << event_count << std::endl;
		std::cout << event_count << " ready_event" << std::endl;
		std::cout << "Reading file descriptor " << events[i].data.fd << std::endl;
		int bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
		read_buffer[bytes_read] = '\0';
		std::cout << read_buffer << std::endl;
		write(new_socket , answer.c_str() , strlen(answer.c_str()));
		}
	if (close(epoll_fd)) {
		fprintf(stderr, "Failed to close epoll file descriptor\n");
		return 1;
	}	
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

void DeleteServers(std::vector<server_configuration*> servers)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		delete servers[i];
	}
}

int main(int argc, char const **argv)
{
	if (argc != 2)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return -1;
	}
	std::vector<server_configuration*> servers = SetupNewServers(argv[1]);
	// PrintServer(servers);
	int newsocket[servers.size()];
	int i = 0;
	std::cout << "server " << servers[i]->getPort() << std::endl;
	std::cout << "server2 " << *servers[i] << std::endl;
	newsocket[i] = getServerFd(servers[i]); // a finir
	std::cout << "newsocket" << newsocket[i] << std::endl; //4
	start_server(newsocket[0]);
	DeleteServers(servers);
	return 0;
}