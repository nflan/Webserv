/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_configuration.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:03:12 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/17 14:52:34 by mgruson          ###   ########.fr       */
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

#define DEBUG 0

class server_configuration
{
	private:
	std::string _ConfigFile;
	std::string _ServerName;
	std::string	_Root;
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

	std::string getConfigFile();
	std::string getServerName();
	std::string getRoot();
	int getNumberOfPorts();
	int getPort();
};

std::ostream& operator <<(std::ostream &out, server_configuration &ServConfig);

#endif