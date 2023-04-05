/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_configuration.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:03:12 by mgruson           #+#    #+#             */
/*   Updated: 2023/04/05 15:29:41 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONFIGURATION_HPP
#define SERVER_CONFIGURATION_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include "server_location_configuration.hpp"
#include <vector>
#define DEBUG 0

class server_configuration
{
	private:
	std::string _ConfigFile;
	std::string _ServerName;
	std::string	_Root;
	std::map<std::string, std::string>	_cgi;
	int			_Port;
	size_t		_ClientMaxBodySize;
	std::string _ErrorPage; // refaire cela avec map TODO
	std::map<std::string, std::string> _Location;
	std::map<std::string, class server_location_configuration*> _Loc;
	
	
	public:
	server_configuration();
	server_configuration(std::string ConfigFile);
	server_configuration(server_configuration const &obj);
	~server_configuration();
	server_configuration &operator=(server_configuration const &obj);

	std::string convertConfigFile(std::string ConfigFile);
	std::string findServerName();
	int findPort();
	std::string findRoot();
	std::map<std::string, std::string> findLocation();
	void setCgi();
	int fillCgi(size_t pos);
	std::map<std::string, class server_location_configuration*> findLoc();


	void	printCgi();
	std::ostream&	printLocation(std::ostream &out);
	std::ostream&	printLoc(std::ostream &out);
	
	size_t findClientMaxBodySize();
	std::string findErrorPage();
	std::string getConfigFile();
	std::string getServerName();
	std::map<std::string, std::string> getCgi();
	std::string getRoot();
	int getPort();

	class CgiException: public std::exception {
		public:
			virtual const char *	what() const throw();
	};
	size_t getClientMaxBodySize();
	std::string getErrorPage();
};

std::ostream& operator <<(std::ostream &out, server_configuration &ServConfig);

#endif
