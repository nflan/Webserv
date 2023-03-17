/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:39:03 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/17 15:29:56 by mgruson          ###   ########.fr       */
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
#define PORT 8082

#include "server_configuration.hpp"

int getServerFd()
{

	/*
	The sockaddr_in struct is a part of the BSD sockets API in Linux and is used to specify internet addresses.
	It contains the following fields:

	sin_family: Specifies the address family used by the socket, typically AF_INET (IPv4) or AF_INET6 (IPv6).
	sin_port: Specifies the port number for the socket (between 0 and 65535), in network byte order (i.e., big-endian).
	sin_addr: Specifies the IP address for the socket.
	sin_zero: Padding field.
	*/
	int		new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	/*
	Socket() : 
		Type of IP : AF_INET for IPv4 (AF_INET6 for IPv6 addresses)
		Type of protocol to exchance (SOCK_STREAM for TCP) and the protocol (0 for default protocol).
	Therefore, server_fd = socket(AF_INET, SOCK_STREAM, 0) creates a new socket file descriptor for IPv4 TCP connections.
	*/

	int server_fd;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	/*
	address.sin_addr.s_addr is a field of the sockaddr_in struct that is used to specify the IP address of the server. Here, INADDR_ANY is being assigned to this field.
	INADDR_ANY is a special constant value that represents "any" or "all" available IP addresses on the host machine. When the server socket is bound to a port using this IP address, it means that the server is willing to accept connections from clients that are connecting via any interface and any IP address on the host machine.
	For example, if a machine has multiple interfaces (such as Ethernet and Wi-Fi) with different IP addresses, then binding to INADDR_ANY would allow clients to connect using either interface and either IP address.
	*/
	address.sin_addr.s_addr = INADDR_ANY;
	/* htons() stands for "host-to-network short", and it converts a 16-bit unsigned integer from host-byte-order to network-byte-order. This function is typically required by most networking functions that deal with port numbers since different computer architectures might have different byte-orders (endianness).*/
	address.sin_port = htons( PORT );
	memset(address.sin_zero, '\0', sizeof address.sin_zero);

	/*
	The bind() function binds a socket to a specific address and port number.
	It takes three arguments:
	- the first one is the server file descriptor;
	- the second one is a pointer to a struct sockaddr that contains the IP address and the port number to bind to;
	- the third one is the size of the struct sockaddr object.
	In this case, the bind() function is binding the server_fd socket to the address and port number defined in address. The sizeof(address) is passed as the third argument to specify the size of the struct sockaddr object passed in.
	*/

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("In bind");
		exit(EXIT_FAILURE);
	}
	/*
	The listen() function allows the program to listen on the socket for incoming connections.
	The first argument is the socket file descriptor returned by socket().
	The second argument is the maximum number of queued connections that are pending.
	*/
	if (listen(server_fd, 2) < 0)
	{
		perror("In listen");
		exit(EXIT_FAILURE);
	}
	/*
	accept() is a system call that accepts connections on the socket, it extracts one connection from the queue of pending connections of the listening socket.
	The first parameter in this function call is the socket file descriptor returned by socket(). The second argument points to a buffer where the address of the connecting client should be stored. And the last argument is set to the size of the sockaddr_in structure pointed to by the second argument.
	The accept() function returns another file descriptor(new_socket) for the newly created TCP socket created between the server and the client, through which the server will communicate with the client.
	*/
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
	/*
	epoll() is a high-performance I/O completion notification interface that allows an application to monitor multiple file 
	descriptors/sockets returning readiness information about them.
	In other words, it's a system call that monitors multiple input/output events and provides an efficient way to handle a
	large number of file descriptors compared to select or poll system call.
	
	Some resources :	https://kaleid-liner.github.io/blog/2019/06/02/epoll-web-server.html
						https://suchprogramming.com/epoll-in-3-easy-steps/
						
	*/

	std::string answer = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	char read_buffer[READ_SIZE + 1];
	struct epoll_event event, events[MAX_EVENTS];
	/* on epoll : https://copyconstruct.medium.com/the-method-to-epolls-madness-d9d2d6378642
	*/
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1) {
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}

	/*
	EPOLLIN means that the associated file descriptor (fd) is available for read operations. 
	The file descriptor being set here is 0, which typically refers to standard input (stdin).
	This indicates to the epoll instance that the program wants to be notified whenever there is
	data available to be read from standard input.
	*/
	event.events = EPOLLIN; 
	event.data.fd = new_socket;

	/*	
	epoll_ctl() is the function that manages the epoll instance by adding and removing file descriptors from the list to be watched
	The second parameter EPOLL_CTL_ADD instructs epoll to add a new file descriptor to its watch list.
	The third parameter 0 refers to the file descriptor itself we want to add/remove.
	The fourth parameter &event is a pointer to the struct epoll_event which specifies the event types that we want to monitor for this file descriptor.

	In summary, epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event) is asking the kernel to add a new file descriptor to epoll's event set, where epoll_fd is the epoll file descriptor.

	epoll_ctl() has three operations that we can use:

	EPOLL_CTL_ADD - Add a file descriptor to the monitored set.
	EPOLL_CTL_MOD - Update and modify the monitored set with new settings data.
	EPOLL_CTL_DEL - Remove a file descriptor from the monitored set.
	*/

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &event)) {
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(epoll_fd);
		return 1;
	}

	/*
	epoll_wait(epoll_fd, events, MAX_EVENTS, 30000). This function blocks until at least one event occurs
	or the specified timeout (30 seconds in this case) elapses. It returns the number of events that occurred
	and stores
	*/
	int event_count = 0;
	while (1) {
		std::cout << "Waiting for new request" << std::endl;
		event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
		std::cout << "Polling for input..." << event_count << std::endl;
		std::cout << event_count << " ready_event" << std::endl;
		for (int i = 0; i < event_count; i++) {
			std::cout << "Reading file descriptor " << events[i].data.fd << std::endl;
			int bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
			read_buffer[bytes_read] = '\0';
			std::cout << read_buffer << std::endl;
			//answer = handle_request(read_buffer);
			write(new_socket , answer.c_str() , strlen(answer.c_str()));
		}
	}
	if (close(epoll_fd)) {
		fprintf(stderr, "Failed to close epoll file descriptor\n");
		return 1;
	}	
}

std::vector<server_configuration*> SetupServers(std::string filename)
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
	
	std::vector<server_configuration*> servers = SetupServers(argv[1]);
	PrintServer(servers);
	DeleteServers(servers);

	return 0;
	
}