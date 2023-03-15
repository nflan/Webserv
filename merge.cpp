/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:39:03 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/15 16:26:34 by mgruson          ###   ########.fr       */
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

#define MAX_EVENTS 5
#define READ_SIZE 1000
#define PORT 8081

int main(int argc, char const *argv[])
{
	int		new_socket;
	long	valread;

	/*
	The sockaddr_in struct is a part of the BSD sockets API in Linux and is used to specify internet addresses.
	It contains the following fields:

	sin_family: Specifies the address family used by the socket, typically AF_INET (IPv4) or AF_INET6 (IPv6).
	sin_port: Specifies the port number for the socket (between 0 and 65535), in network byte order (i.e., big-endian).
	sin_addr: Specifies the IP address for the socket.
	sin_zero: Padding field.
	*/
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	std::string answer = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
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

	/*-------------------------------------------------*/

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
	std::cout << "Waiting for new connection" << std::endl;
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
	{
		perror("In accept");
		exit(EXIT_FAILURE);
	}
	size_t bytes_read;
	char read_buffer[READ_SIZE + 1];
	struct epoll_event event, events[MAX_EVENTS];
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1) {
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}
	event.events = EPOLLIN; 
	event.data.fd = new_socket;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &event)) {
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(epoll_fd);
		return 1;
	}
	int event_count = 0;
	while (1) {
		std::cout << "Polling for input..." << std::endl;
		event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
		std::cout << "Polling for input..." << event_count << std::endl;
		std::cout << event_count << " ready_event" << std::endl;
		for (int i = 0; i < event_count; i++) {
			std::cout << "Reading file descriptor " << events[i].data.fd << std::endl;
			int bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
			read_buffer[bytes_read] = '\0';
			printf("Read '%s'\n", read_buffer);
		}
	}
	if (close(epoll_fd)) {
		fprintf(stderr, "Failed to close epoll file descriptor\n");
		return 1;
	}
	return 0;
}