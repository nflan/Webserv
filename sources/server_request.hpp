/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_request.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:29:37 by mgruson           #+#    #+#             */
/*   Updated: 2023/04/06 15:43:26 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_REQUEST_HPP
#define SERVER_REQUEST_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>

#define DEBUG 0

class server_request
{
	private:
	std::string _ServerRequest;
	std::string _Method; //old
	std::string _method;
	std::string _RequestURI; //old
	std::string _path;
	std::string _type;
	std::string _version;
	std::string _host;
	std::string _connectionType;
	std::string _mimeType;
	std::string _contentType;
	std::string _contentLength;
	std::string _body;

	server_request();

	public:
	server_request(std::string ServerRequest);
	server_request(server_request const &obj);
	~server_request();
	server_request &operator=(server_request const &obj);
	
	std::string findRequestURI();
	std::string findMethod();
	std::string getServerRequest() const;
	std::string getMethod() const;
	std::string getRequestURI() const;
	std::string getType() const;
	std::string	getBody() const;
	void request_parser();
};

std::ostream& operator <<(std::ostream &out, server_request &ServRequest);

#endif