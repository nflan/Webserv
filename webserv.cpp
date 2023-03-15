#include <stdio.h>
#include <iostream>
#include <string>

//socket
#include <sys/socket.h>
#include <errno.h>
//strcut sockaddr_in && bin
#include <netinet/in.h>
#include <string.h>
//liten && accept
#include <sys/socket.h>
//read && write
#include <unistd.h>

#define PORT 8080

int main(void)
{
	int srv_fd = 0;
	// socket(domaine, type, protocole)
	// domaine : AF_INET (IP), AF_INET6 (IPv6), AF_UNIX (local channel, similar to pipes),
	// AF_ISO (ISO protocols)et AF_NS (Xerox Network Systems protocols)
	// type : SOCK_STREAM (virtual circuit service), SOCK_DGRAM (datagram service), SOCK_RAW (direct IP service)
	// protocole : if types need value, for TCP/IP one type of service = 0
	if ((srv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("error: cannot create socket");
		return (1);
	}
	// sockaddr : struct container for identify family address (2 octets)
	// sockaddr_in for IP
	// sin_family : family use for create socket AF_INET
	// sin_addr : address socket - IP machine - INADDR_ANY = 0.0.0.0 for all
	// sin_port : port use - random if 0
	struct sockaddr_in addr;
	memset((char *)&addr, 0, sizeof(addr)); 
	addr.sin_family = AF_INET ; 
	addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	addr.sin_port = htons(PORT);

	// bind(socket, address, addr_len)
	if (bind(srv_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
	{
		perror("bind failed"); 
		return(1); 
	}
	// listen (socket, backlog)
	// backlog = nbr of max waiting entry connections before refuse)
	if (listen(srv_fd, 3) < 0) 
	{
		perror("In listen"); 
		return(1);
	}

	// first socket only use for accept connections not for echange data
	// accept(socket, sockaddr, addr_len)
	// by default : synchronous, blocking. accept block until connection is present onthe queue
	int new_socket = 0;
	int addrlen = 0;
	while (1)
	{
		printf("\n+++++++ Waiting for new connection ++++++++\n\n");
		if ((new_socket = accept(srv_fd, (struct sockaddr *) &addr, (socklen_t*) &addrlen))<0)
		{ 
			perror ("In accept");
			return(1);
		}
		// CONNECTION IS ACTIVE - NOW NEED we need to read and write on new_socket
		char buffer[1024] = {0};
		int valread = read( new_socket , buffer, 1024); 
		printf("%s\n",buffer );
		if(valread < 0)
		{ 
			printf("No bytes are there to read");
		}
		std::string hello = "Hello from the server"; //IMPORTANT! WE WILL GET TO IT
		write(new_socket , hello.c_str() , hello.size());
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
	}

	return (0);
}

