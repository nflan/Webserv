/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_response.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:09:46 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/22 12:40:13 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_response.hpp"

server_response::server_response() : _body(""), _status_code(200)
{
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
	std::cout << "server_response Copy assignment operator called" << std::endl;
	return *this;
}

server_response::server_response(const std::string& body, int status_code) : _body(body), _status_code(status_code)
{
	std::cout << "server_response Overload Constructor called" << std::endl;
}

void server_response::generate_post_response(const std::string& request_uri, const std::string& data)
{
	// Par exemple, on pourrait simplement renvoyer un message de confirmation avec les données reçues
	std::string response_body = "Données reçues : " + data;
	
	// Ensuite, on prépare et envoie la réponse
	std::ostringstream response_stream;
	response_stream << "HTTP/1.1 200 OK\r\n"
					<< "Content-Type: text/plain\r\n"
					<< "Content-Length: " << response_body.length() << "\r\n"
					<< "\r\n"
					<< response_body;
	std::string response = response_stream.str();
	send_response_to_client(response);
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

void handle_post_request(int client_socket)
{
	// Récupérer les données de la requête POST
	std::stringstream response;
	const int buffer_size = 1024;
	char buffer[buffer_size];
	std::memset(buffer, 0, buffer_size);
	ssize_t bytes_received = recv(client_socket, buffer, buffer_size, 0);

	// Extraire le contenu binaire
	std::string raw_data(buffer, bytes_received);
	size_t begin_content = raw_data.find("\r\n\r\n") + 4;
	std::string binary_data(raw_data.begin() + begin_content, raw_data.end());

	//Ecrire les Données dans un fichier
	std::ofstream output_file("file.bin", std::ios::out | std::ios::binary);
	output_file.write(binary_data.c_str(), binary_data.size());
	output_file.close();

	// Vérifier que toutes les données ont été reçues
	int content_length_pos = raw_data.find("Content-Length:");
	if (content_length_pos != std::string::npos) {
		size_t end_pos = raw_data.find("\r\n", content_length_pos);
		std::string content_length_str = raw_data.substr(content_length_pos + strlen("Content-Length:"), end_pos - content_length_pos - strlen("Content-Length:"));
		int expected_length = std::stoi(content_length_str);
		if (expected_length != binary_data.size()) {
			std::cout << "Erreur : Taille incomplète des données binaires" << std::endl;
		}
	}

	// Envoyer une réponse réussie au client
	response << "HTTP/1.1 200 OK\r\n";
	response << "Content-Type: text/plain; charset=UTF-8\r\n";
	response << "Content-Length: 10\r\n";
	response << "\r\n";
	response << "Succès !\r\n";
	std::string response_str = response.str();
	send(client_socket, response_str.c_str(), response_str.length(), 0);
}
