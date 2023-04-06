/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_response.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:09:46 by mgruson           #+#    #+#             */
/*   Updated: 2023/04/06 16:32:06 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_response.hpp"

server_response::server_response() : _status_code(200), _body(""), _ServerResponse("")
{
	this->addType();
	std::cout << "server_response Default Constructor called" << std::endl;
}
server_response::server_response(server_response const &obj)
{
	*this = obj;
}

server_response::~server_response()
{
	std::cout << "server_response Destructor called" << std::endl;
}

server_response &server_response::operator=(server_response const &obj)
{
	(void)obj;
	std::cout << "server_response Copy assignment operator called" << std::endl;
	return *this;
}

// void server_response::generate_post_response(const std::string& request_uri, const std::string& data)
// {
// 	// Par exemple, on pourrait simplement renvoyer un message de confirmation avec les données reçues
// 	std::string response_body = "Données reçues : " + data;
	
// 	// Ensuite, on prépare et envoie la réponse
// 	std::ostringstream response_stream;
// 	response_stream << "HTTP/1.1 200 OK\r\n"
// 					<< "Content-Type: text/plain\r\n"
// 					<< "Content-Length: " << response_body.length() << "\r\n"
// 					<< "\r\n"
// 					<< response_body;
// 	std::string response = response_stream.str();
// 	send_response_to_client(response);
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "server_configuration.hpp"

// void handle_post_request(int client_socket)
// {
// 	// Récupérer les données de la requête POST
// 	std::stringstream response;
// 	const int buffer_size = 1024;
// 	char buffer[buffer_size];
// 	std::memset(buffer, 0, buffer_size);
// 	ssize_t bytes_received = recv(client_socket, buffer, buffer_size, 0);

// 	// Extraire le contenu binaire
// 	std::string raw_data(buffer, bytes_received);
// 	size_t begin_content = raw_data.find("\r\n\r\n") + 4;
// 	std::string binary_data(raw_data.begin() + begin_content, raw_data.end());

// 	//Ecrire les Données dans un fichier
// 	std::ofstream output_file("file.bin", std::ios::out | std::ios::binary);
// 	output_file.write(binary_data.c_str(), binary_data.size());
// 	output_file.close();

// 	// Vérifier que toutes les données ont été reçues
// 	int content_length_pos = raw_data.find("Content-Length:");
// 	if (content_length_pos != std::string::npos) {
// 		size_t end_pos = raw_data.find("\r\n", content_length_pos);
// 		std::string content_length_str = raw_data.substr(content_length_pos + strlen("Content-Length:"), end_pos - content_length_pos - strlen("Content-Length:"));
// 		int expected_length = std::stoi(content_length_str);
// 		if (expected_length != binary_data.size()) {
// 			std::cout << "Erreur : Taille incomplète des données binaires" << std::endl;
// 		}
// 	}

// 	// Envoyer une réponse réussie au client
// 	response << "HTTP/1.1 200 OK\r\n";
// 	response << "Content-Type: text/plain; charset=UTF-8\r\n";
// 	response << "Content-Length: 10\r\n";
// 	response << "\r\n";
// 	response << "Succès !\r\n";
// 	std::string response_str = response.str();
// 	send(client_socket, response_str.c_str(), response_str.length(), 0);
// }

void	server_response::addType()
{
	_contentType.insert(std::make_pair<std::string, std::string>("html", "Content-Type: text/html\r\n"));
	_contentType.insert(std::make_pair<std::string, std::string>("jpg", "Content-Type: image/jpeg\r\n"));
}

std::string server_response::getType(std::string type)
{
	for (std::map<std::string, std::string>::iterator it = _contentType.begin(); it != _contentType.end(); it++)
	{
		if (type == it->first)
			return (it->second);
	}
	return ("Content-Type: text/plain; charset=UTF-8\r\n");
}

void	server_response::todo(const server_request& Server_Request, int conn_sock, server_configuration *server)
{
	enum imethod {GET, POST, DELETE};
	std::string	Root = server->getRoot();
	int n = 0;
	const std::string ftab[3] = {"GET", "POST", "DELETE"};
	(void)Root;
	for (; n < 4; n++)
	{
		if (n != 3 && ftab[n] == Server_Request.getMethod())
		{
			break ;
		}
	}
	switch (n)
	{
		case GET :
		{
			// std::string answer = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
			// send(conn_sock, answer.c_str() , answer.size(), 0);
			std::string tmp;
			if (Root.size() == 1 && Root.find("/", 0, 1))
				tmp = "." + Server_Request.getRequestURI();
			else
				tmp = Root + Server_Request.getRequestURI();
			std::cout << "\nC0 = '" << tmp << "'\n" << std::endl;
			if (tmp.size() == 3 && tmp.find(".//") != std::string::npos)
			{
				// tmp.erase();
				std::cout << "\nC1\n" << std::endl;
				tmp += "index.html";
			}
			if (tmp[tmp.size() - 1] == '/')
			{
				tmp += "index.html";
			}
			std::ifstream file(tmp.c_str());
			std::stringstream buffer;
			std::stringstream response;
			if (!file.is_open())
			{
				std::cerr << "\nERROR IS_OPEN\r\n" << std::endl;
				response << "HTTP/1.1 404 Not Found\r\n";
			//	Ne peut pas fonctionner si on ne sait pas quel serveur recoit et du coup que les pages ne sont pas initialisees
				if (server->getErrorPage().size() != 0 && server->getErrorPage().find("404") != server->getErrorPage().end())
					buffer << server->getErrorPage().find("404")->second;
				else
				//Actuellement j'utilise la page erreur 404 mais il va falloir trouver comment automatiser pour afficher la page d'erreur qu'il faut. De plus, il faudra check si la page erreur est precisee dans le fichier de config, sachant qu'on ne donne pas le serveur qui recoit la requete (du coup pour l'instant on ne peut pas)
					buffer << server->getDefErrorPage().find("Not Found")->second;//file.rdbuf();
				std::string content = buffer.str();
				// response << "Content-Type: text/plain; charset=UTF-8\r\n";
				response << "Content-Length: " << content.size() << "\r\n";
				response << "\r\n";
				response << content << "\r\n";
				// response << "Content-Type: text/html\r\n";
			}
			else
			{
				std::cout << "\nC2\n" << std::endl;
				buffer << file.rdbuf();
				// std::cout << "\nBUFFER = " << buffer.str() << "\r\n" << std::endl;
				std::string content = buffer.str();
				response << "HTTP/1.1 200 OK\r\n";
				response << this->getType(Server_Request.getType());
				// response << "Content-Type: text/html\r\n";
				// response << "Content-Type: text/plain; charset=UTF-8\r\n";
				response << "Content-Length: " << content.size() << "\r\n";
				response << "\r\n";
				response << content << "\r\n";
			}
			// response << "Hello world!\r\n";
			std::cerr << "AFTER RESPONSE IFSTREAM\r\n" << std::endl;
			std::string response_str = response.str();
			send(conn_sock, response_str.c_str() , response_str.size(), 0);
			std::cerr << "\nREPONSE SEND :\n";
			// std::cerr << response_str << std::endl;
			break ;
		}
		case POST :
		{
			// std::string infilename = "./site/42.jpg";
			// std::ifstream inputFile(infilename.c_str(), std::ios::binary);
			// std::stringstream response1;
			std::string outfilename = "./test.jpg";
			std::ofstream outputFile(outfilename.c_str(), std::ios::binary);

			// // Get the file size
			// inputFile.seekg(0, std::ios::end);
			// int fileSize = inputFile.tellg();
			// inputFile.seekg(0, std::ios::beg);
			
			// // Read the contents of the file into a buffer
			// std::vector<unsigned char> fileBuffer(fileSize);
			// inputFile.read(reinterpret_cast<char*>(fileBuffer.data()), fileSize);
			
			// inputFile.close();

			// outputFile << reinterpret_cast<char*>(fileBuffer.data());
			// outputFile.close();

			std::string tmp = "./site/42.jpg";
            std::cout << "\nC0bis = '" << tmp << "'\n" << std::endl;
            std::ifstream file(tmp.c_str(), std::ifstream::binary);
            // std::stringstream buffer;
            std::stringstream response;
            std::filebuf* pbuf = file.rdbuf();
            std::size_t size = pbuf->pubseekoff(0, file.end, file.in);
            pbuf->pubseekpos (0,file.in);
            char *buffer= new char[size];
            pbuf->sgetn(buffer, size);
            file.close();
            std::string content(buffer, size);
			std::cout << "\nC2\n" << std::endl;
            // buffer << file.rdbuf();
            // std::cout << "\nBUFFER = " << buffer.str() << "\r\n" << std::endl;
            // std::string content = buffer.str();
            response << "HTTP/1.1 200 OK\r\n";
            response << "content-Type: image/jpeg\r\n";
            // response << "Content-Type: text/plain; charset=UTF-8\r\n";
            response << "content-Length: " << size << "\r\n";
            response << "\r\n";
            response << content << '\0' << "\r\n";
			outputFile << content ;
			outputFile.close();
            // }
            // response << "Hello world!\r\n";
            std::cerr << "AFTER RESPONSE IFSTREAM\r\n" << std::endl;
            std::cout << buffer << std::endl;
            std::string response_str = response.str();
            send(conn_sock, response_str.c_str() , response_str.size(), 0);
/**********************************************************************************/
			// std::cout << "Successfully wrote to " << outfilename << std::endl;
			// response1 << "HTTP/1.1 200 OK\r\n";
			// response1 << "Content-Length: " << fileSize << "\r\n";
			// response1 << "\r\n";
			// response1.write(reinterpret_cast<char*>(fileBuffer.data()), fileSize);
			// std::string response_str1 = response1.str();
			// send(conn_sock, response_str1.c_str() , response_str1.size(), 0);

			break ;
		}
		case DELETE :
		{
			break ;
		}
		default :
		{
			break ;
		}
	}
	return ;
}
