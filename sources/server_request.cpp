/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:31:36 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/23 15:32:05 by mgruson          ###   ########.fr       */
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
_PathToFile(findPathToFile()),
_ContentType(findContentType()),
_ContentLength(findContentLength())
{
}

std::string server_request::findContentType()
{
	size_t pos = _ServerRequest.find("Content-Type:"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
		pos += strlen("Content-Type:"); // move the position to the end of "server_name"
		std::string ContentType = _ServerRequest.substr(pos + 1); // extract the substring starting from the next character
		size_t space_pos = ContentType.find_first_of(" \n"); // find the position of the first space or newline character
		if (space_pos != std::string::npos) { // check if a space character was found
			if (DEBUG)
				std::cout << "std::string server_configuration::findServerName() " << ContentType.substr(0, space_pos) << std::endl;
			return(ContentType.substr(0, space_pos)); // extract the substring before the space character
		}
	}
	return ("Not found");
}

unsigned int server_request::findContentLength()
{
	size_t pos = _ServerRequest.find("Content-Length:"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
		pos += strlen("Content-Length:"); // move the position to the end of "server_name"
		std::string ContentLength = _ServerRequest.substr(pos + 1); // extract the substring starting from the next character
		size_t space_pos = ContentLength.find_first_of(" \n"); // find the position of the first space or newline character
		if (space_pos != std::string::npos) { // check if a space character was found
			if (DEBUG)
				std::cout << "std::string server_configuration::findServerName() " << ContentLength.substr(0, space_pos) << std::endl;
			return(atoi(ContentLength.substr(0, space_pos).c_str())); // extract the substring before the space character
		}

	}
	return (0);
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

std::string server_request::findPathToFile()
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
std::string server_request::getPathToFile() const
{
	return (_PathToFile);
}

std::string server_request::getContentType() const
{
	return (_ContentType);
}

unsigned int server_request::getContentLength() const
{
	return (_ContentLength);
}

std::ostream& operator <<(std::ostream &out, server_request &ServRequest)
{
	out << "Method : " << ServRequest.getMethod() \
		<< "\nPathToFile : " << ServRequest.getPathToFile() \
		<< "\nContent-Type : " << ServRequest.getContentType() \
		<< "\nContentLength : " << ServRequest.getContentLength();
	return (out);
}