/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:31:36 by mgruson           #+#    #+#             */
/*   Updated: 2023/04/05 17:51:20 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_request.hpp"

server_request::server_request()
{
	std::cout << "server_request Default Constructor called" << std::endl;
}

server_request::server_request(server_request const &obj)
{
	*this = obj;
}

server_request::~server_request()
{
	std::cout << "server_request Destructor called" << std::endl;
}

server_request &server_request::operator=(server_request const &obj)
{
	(void)obj;
	std::cout << "server_request Copy assignment operator called" << std::endl;
	return *this;
}

server_request::server_request(std::string ServerRequest) :
_ServerRequest(ServerRequest),
_Method(findMethod()),
_RequestURI(findRequestURI())
{
}

std::string server_request::findMethod()
{
	size_t pos = _ServerRequest.find(" ");
	if (pos == std::string::npos)
		return ("");
	std::string tmp = _ServerRequest.substr(0, pos);
	_ServerRequest.erase(0, pos + 1);
	return (tmp);
}

std::string server_request::findRequestURI()
{
	size_t pos = _ServerRequest.find(" ");
	if (pos == std::string::npos)
		return ("");
	std::string tmp = _ServerRequest.substr(0, pos);
	_ServerRequest.erase(0, pos);
	return (tmp);
}

std::string server_request::getServerRequest() const
{
	return (_ServerRequest);
}
std::string server_request::getMethod() const
{
	return (_Method);
}
std::string server_request::getRequestURI() const
{
	return (_RequestURI);
}

std::ostream& operator <<(std::ostream &out, server_request &ServRequest)
{
	out << "Method : " << ServRequest.getMethod() \
		<< "\nRequestURI : " << ServRequest.getRequestURI() \
		<< "\nServerRequest : " << ServRequest.getServerRequest() << "\n";
	return (out);
}

void server_request::request_parser()
{
    std::string request = "GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\n\r\n";
    
    // Extraire la méthode HTTP (GET/POST/DELETE)
    std::string::size_type method_end = request.find(' ');
    this->_method = request.substr(0, method_end);

    // Extraire le chemin de la ressource (/index.html)
    std::string::size_type path_end = request.find(' ', method_end + 1);
    this->_path = request.substr(method_end + 1, path_end - method_end - 1);

    // Extraire la version HTTP (HTTP/1.1)
    std::string::size_type version_end = request.find("\r\n", path_end + 1);
    this->_version = request.substr(path_end + 1, version_end - path_end - 1);

    // Extraire l'en-tête Host (www.example.com)
    std::string::size_type host_start = request.find("Host: ");
    std::string::size_type host_end = request.find("\r\n", host_start);
    this->_host = request.substr(host_start + 6, host_end - host_start - 6);

    // Extraire le type de connexion (keep-alive)
    std::string::size_type ctype_start = request.find("Connection: ");
    std::string::size_type ctype_end = request.find("\r\n", ctype_start);
    this->_connectionType = request.substr(ctype_start + 12, ctype_end - ctype_start - 12);

    // Extraire le type de MIME (image/png) IF GET
    std::string::size_type mtype_start = request.find("Accept: ");
    std::string::size_type mtype_end = request.find("\r\n", mtype_start);
    this->_mimeType = request.substr(mtype_start + 8, mtype_end - mtype_start - 8);

    // Extraire le type de MIME (multipart/form-data) IF POST
    std::string::size_type cotype_start = request.find("Content-Type: ");
    std::string::size_type cotype_end = request.find("\r\n", cotype_start);
    this->_contentType = request.substr(cotype_start + 14, cotype_end - cotype_start - 14);

    // Extraire le type de MIME (multipart/form-data) IF POST
    std::string::size_type colength_start = request.find("Content-Length: ");
    std::string::size_type colength_end = request.find("\r\n", colength_start);
    this->_contentLength = request.substr(colength_start + 16, colength_end - colength_start - 16);

    // Afficher les résultats
    std::cout << "\nMéthode : " << this->_method << std::endl;
    std::cout << "Chemin : " << this->_path << std::endl;
    std::cout << "Version : " << this->_version << std::endl;
    std::cout << "Host : " << this->_host << std::endl;
    std::cout << "Connection : " << this->_connectionType <<  std::endl;
    std::cout << "MIME : " << this->_mimeType <<  std::endl;
    std::cout << "Content Type : " << this->_contentType <<  std::endl;
    std::cout << "Content Length : " << this->_contentLength << "\n" <<  std::endl;
}

