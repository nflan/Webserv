#include<bits/stdc++.h>

#include <stdio.h>
#include <iostream>
#include <string>
//socket && liten && accept
#include <sys/socket.h>
#include <errno.h>
//strcut sockaddr_in && bin
#include <netinet/in.h>
#include <string.h>
//read && write
#include <unistd.h>
// for epoll_create1(), epoll_ctl(), struct epoll_event
#include <sys/epoll.h>

#include <csignal>

#define MAX_EVENTS 5
#define READ_SIZE 1000
#define PORT 8082

void sigint_handler(int signum)
{
    std::cout << "Signal SIGINT (" << signum << ") received." << std::endl;
	std::exit(1);
    // Ajouter ici le code pour gérer le signal SIGINT selon les besoins.
}

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
    int srv_socket = 0;
    int client_socket = 0;
	struct sockaddr_in addr;
	socklen_t client_addrlen = 0;

	/*
	Socket() : 
		Type of IP : AF_INET for IPv4 (AF_INET6 for IPv6 addresses)
		Type of protocol to exchance (SOCK_STREAM for TCP) and the protocol (0 for default protocol).
	Therefore, server_fd = socket(AF_INET, SOCK_STREAM, 0) creates a new socket file descriptor for IPv4 TCP connections.
	*/

    if ((srv_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::fprintf(stderr, "Error: cannot create socket: %s\n", strerror(errno));
        return(EXIT_FAILURE);
    }

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	/*
	addr.sin_addr.s_addr is a field of the sockaddr_in struct that is used to specify the IP address of the server. Here, INADDR_ANY is being assigned to this field.
	INADDR_ANY is a special constant value that represents "any" or "all" available IP addresses on the host machine. When the server socket is bound to a port using this IP address, it means that the server is willing to accept connections from clients that are connecting via any interface and any IP address on the host machine.
	For example, if a machine has multiple interfaces (such as Ethernet and Wi-Fi) with different IP addresses, then binding to INADDR_ANY would allow clients to connect using either interface and either IP address.
	*/
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	/* htons() stands for "host-to-network short", and it converts a 16-bit unsigned integer from host-byte-order to network-byte-order. This function is typically required by most networking functions that deal with port numbers since different computer architectures might have different byte-orders (endianness).*/
	addr.sin_port = htons(PORT);

	/*
	The bind() function binds a socket to a specific address and port number.
	It takes three arguments:
	- the first one is the server file descriptor;
	- the second one is a pointer to a struct sockaddr that contains the IP address and the port number to bind to;
	- the third one is the size of the struct sockaddr object.
	In this case, the bind() function is binding the server_fd socket to the address and port number defined in address. The sizeof(address) is passed as the third argument to specify the size of the struct sockaddr object passed in.
	*/

	if (bind(srv_socket, (sockaddr *) &addr, sizeof(addr)) < 0)
	{
		std::fprintf(stderr, "Error: bind failed: %s\n", strerror(errno));
		return(EXIT_FAILURE);
	}
	/*
	The listen() function allows the program to listen on the socket for incoming connections.
	The first argument is the socket file descriptor returned by socket().
	The second argument is the maximum number of queued connections that are pending.
	*/
	if (listen(srv_socket, 2) < 0)
	{
		std::fprintf(stderr, "Error: listen failed: %s\n", strerror(errno));
		return(EXIT_FAILURE);
	}
	/*
	accept() is a system call that accepts connections on the socket, it extracts one connection from the queue of pending connections of the listening socket.
	The first parameter in this function call is the socket file descriptor returned by socket(). The second argument points to a buffer where the address of the connecting client should be stored. And the last argument is set to the size of the sockaddr_in structure pointed to by the second argument.
	The accept() function returns another file descriptor(client_socket) for the newly created TCP socket created between the server and the client, through which the server will communicate with the client.
	*/
	std::cout << "Waiting for acception" << std::endl;
	if ((client_socket = accept(srv_socket, (sockaddr *) &addr, &client_addrlen)) < 0)
	{
		std::fprintf(stderr, "Error: server accept failed: %s\n", strerror(errno));
		return(EXIT_FAILURE);
	}
	std::fprintf(stderr, "AFTER ACCEPT\n");
	return (client_socket);
}

int	start_server(int new_socket)
{
	struct epoll_event event, events[MAX_EVENTS];
	size_t bytes_read;
	std::string answer = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	char read_buffer[READ_SIZE + 1];
	int epoll_fd = epoll_create1(0);

	if (epoll_fd == -1)
	{
		std::fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}
	event.events = EPOLLIN; 
	event.data.fd = new_socket;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &event)) {
		std::fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(epoll_fd);
		return 1;
	}
	int event_count = 0;
	while (1)
	{
		std::cout << "Waiting for new request" << std::endl;
		event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
		std::cout << "Polling for input..." << event_count << std::endl;
		std::cout << event_count << " ready_event" << std::endl;
		for (int i = 0; i < event_count; i++)
		{
			std::cout << "Reading file descriptor " << events[i].data.fd << std::endl;
			bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
			read_buffer[bytes_read] = '\0';
			std::cout << read_buffer << std::endl;
			// parsing Request 
			send(new_socket , answer.c_str(), answer.size(), 0);
		}
	}
	if (close(epoll_fd))
	{
		std::fprintf(stderr, "Failed to close epoll file descriptor\n");
		return 1;
	}	
}


//Parsing request

int parse_request(char *request)
{
	
}

int main()
{
	signal(SIGINT, sigint_handler);

	int new_socket = getServerFd();
	std::fprintf(stderr, "CONNECTION TRY\n");

	start_server(new_socket);
	if (close(new_socket) == -1)
	{
		std::fprintf(stderr, "Failed to close epoll file descriptor\n");
	}
	return 0;
}