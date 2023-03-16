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

#define PORT 8080

int main()
{
    int srv_socket = 0;
    if ((srv_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
        perror("error: cannot create socket");
        return(1);
    }
    struct sockaddr_in addr; // Déclaration de la structure sockaddr_in 
    memset(&addr, 0, sizeof(addr)); // Initialisation de la structure à 0 
    addr.sin_family = AF_INET; // Famille d'adresse IPV4 
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // Adresse IP de la machine locale 
    addr.sin_port = htons(PORT);// Port d'écoute du serveur 
    if (bind(srv_socket, (sockaddr *)&addr, sizeof(addr)) < 0) // Liaison du socket à l'adresse et au port spécifiés
	{
        perror("bind failed");
        return(1);
    }
    if (listen(srv_socket, 3) < 0) // Ecoute sur le port spécifié avec une file d'attente de 3 connexions maximum
	{
        perror("In listen");
        return (1);
    }
    int client_socket = 0; // Socket pour les échanges de données entre le client et le serveur 
    socklen_t client_addrlen = 0; // Longueur de l'adresse du client connecté au serveur  
    while(1)
	{
        std::cout << "+++++++ Waiting for new connection ++++++++\n" << std::endl;
        if ((client_socket = accept(srv_socket, (sockaddr *) &addr, &client_addrlen))<0)
		{
            perror("In accept");
            return(1);
        }
        char buffer[256];
        int received_bytes = recv(client_socket, buffer, 255, 0);
        if(received_bytes<0)
        {
            std::cout << "Error reading from socket";
        }
		char hello[] = "Hello from server";
        printf("%s\n",buffer );
        // write(client_socket , buffer , strlen(buffer));
		send(client_socket , hello , strlen(hello) , 0 );
        std::cout << "Message sent" << std::endl;
        close(client_socket);
    }
    return(0);
}