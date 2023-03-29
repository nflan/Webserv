/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_configuration.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:06:26 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/29 16:23:59 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_configuration.hpp"

server_configuration::server_configuration()
{
	if (DEBUG)
		std::cout << "server_configuration Default Constructor called" << std::endl;
}


server_configuration::server_configuration(std::string ConfigFile) : 
_ConfigFile(convertConfigFile(ConfigFile)),
_ServerName(findServerName()),
_Root(findRoot()),
_Port(findPort())
{
	if (DEBUG)
	{
		std::cout << "server_configuration Overload Constructor called" << std::endl;
		std::cout << "server_configuration::server_configuration(std::string ConfigFile)\n" << ConfigFile << std::endl;
		std::cout << "Server name " << this->_ServerName << std::endl;
	}
}

server_configuration::server_configuration(server_configuration const &obj)
{
	*this = obj;
}
server_configuration::~server_configuration()
{
	if (DEBUG)
		std::cout << "server_configuration Destructor called" << std::endl;
}
server_configuration &server_configuration::operator=(server_configuration const &obj)
{
	if (DEBUG)
		std::cout << "server_configuration Copy assignment operator called" << std::endl;
	(void)obj;
	return *this;
}

std::string server_configuration::convertConfigFile(std::string ConfigFileStr)
{
	return (ConfigFileStr);
}

std::string server_configuration::findServerName()
{
	size_t pos = _ConfigFile.find("server_name"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
	    pos += strlen("server_name"); // move the position to the end of "server_name"
	    std::string server_name = _ConfigFile.substr(pos + 1); // extract the substring starting from the next character
		size_t space_pos = server_name.find_first_of(" \n"); // find the position of the first space or newline character
	    if (space_pos != std::string::npos) { // check if a space character was found
			if (DEBUG)
				std::cout << "std::string server_configuration::findServerName() " << server_name.substr(0, space_pos) << std::endl;
	        return(server_name.substr(0, space_pos)); // extract the substring before the space character
	    }
	}
	return ("Not found");
}



std::string server_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
	    pos += strlen("root");
	    std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n");
	    if (space_pos != std::string::npos) {
	        return (root.substr(0, space_pos));
	    }
	}
	return ("Not found");
}



int server_configuration::findPort()
{
	size_t pos = _ConfigFile.find("listen 0.0.0.0:");
	if (pos != std::string::npos) {
		pos += strlen("listen 0.0.0.0:");
		std::string port = _ConfigFile.substr(pos);
		size_t space_pos = port.find_first_of(" \n");
		if (space_pos != std::string::npos) {
			if (DEBUG)
				std::cout << "server_configuration::findPort() " << port.substr(0, space_pos).c_str() << std::endl;
			return (atoi(port.substr(0, space_pos).c_str()));
		}
	}
	return (0);
}

std::string server_configuration::getConfigFile() { return _ConfigFile;}
std::string server_configuration::getServerName() { return _ServerName;}
std::string server_configuration::getRoot() { return _Root;}
int server_configuration::getPort() { return _Port;}

std::ostream& operator <<(std::ostream &out, server_configuration &ServConfig)
{
	out << "Server name : " << ServConfig.getServerName() \
		<< "\nRoot : " << ServConfig.getRoot() \
		<< "\nPort : " << ServConfig.getPort();
		
	return (out);
}