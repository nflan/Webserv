/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:31:36 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/20 17:16:29 by mgruson          ###   ########.fr       */
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
_PathToFile(findPathToFile())
{
}


std::string server_request::findMethod()
{
	size_t pos = _ServerRequest.find(" ");
	if (pos == std::string::npos)
		return ("");
	std::string tmp = _ServerRequest.substr(0, pos);	_ServerRequest.erase(0, pos + 1);
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

std::ostream& operator <<(std::ostream &out, server_request &ServRequest)
{
	out << "Method : " << ServRequest.getMethod() \
		<< "\nPathToFile : " << ServRequest.getPathToFile();
	return (out);
}