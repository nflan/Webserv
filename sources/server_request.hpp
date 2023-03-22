/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_request.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:29:37 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/20 16:33:48 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_REQUEST_HPP
#define SERVER_REQUEST_HPP

#include <iostream>

class server_request
{
	private:
	std::string _ServerRequest;
	std::string _Method;
	std::string _RequestURI;
	std::string _PathToFile;
	server_request();

	public:
	server_request(std::string ServerRequest);
	server_request(server_request const &obj);
	~server_request();
	server_request &operator=(server_request const &obj);
	
	std::string findPathToFile();
	std::string findMethod();
	std::string getServerRequest() const;
	std::string getMethod() const;
	std::string getPathToFile() const;
};

std::ostream& operator <<(std::ostream &out, server_request &ServRequest);

#endif