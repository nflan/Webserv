/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_configuration.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:03:12 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/28 16:37:04 by nflan            ###   ########.fr       */
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

#define DEBUG 0

class server_configuration
{
	private:
	std::string _ConfigFile;
	std::string _ServerName;
	std::string	_Root;
	std::map<std::string, std::string>	_cgi;
	int			_Port;
	
	public:
	server_configuration();
	server_configuration(std::string ConfigFile);
	server_configuration(server_configuration const &obj);
	~server_configuration();
	server_configuration &operator=(server_configuration const &obj);

	std::string findServerName();
	int findPort();
	std::string convertConfigFile(std::string ConfigFile);
	std::string findRoot();
	void setCgi();
	int fillCgi(size_t pos);

	std::string getConfigFile();
	std::string getServerName();
	std::string getRoot();
	int getNumberOfPorts();
	int getPort();

	class CgiException: public std::exception {
		public:
			virtual const char *	what() const throw();
	};
};

std::ostream& operator <<(std::ostream &out, server_configuration &ServConfig);

#endif
