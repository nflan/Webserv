/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_configuration.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:06:26 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/17 13:47:07 by mgruson          ###   ########.fr       */
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
_NumberOfPorts(findNumberOfPorts(_ConfigFile)),
_Port(findPort())
{
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

std::string server_configuration::convertConfigFile(std::string ConfigFile)
{
	std::ifstream file(ConfigFile.c_str());
	
	// Check if we successfully opened the file
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file for reading");
	}
	
	// Read the entire file into a string
    std::string ConfigFileStr;
    std::getline(file, ConfigFileStr, '\0');
	// Close the file
	file.close();

	return (ConfigFileStr);
}

int server_configuration::findNumberOfPorts(std::string &str)
{
	std::string subStr("server {");
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(subStr, pos)) != std::string::npos) {
        ++count;
        pos += subStr.length();
    }
    return count;
}

std::string server_configuration::findServerName()
{
	size_t pos = _ConfigFile.find("server_name"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
	    pos += strlen("server_name"); // move the position to the end of "server_name"
	    std::string server_name = _ConfigFile.substr(pos + 1); // extract the substring starting from the next character
		size_t space_pos = server_name.find_first_of(" \n"); // find the position of the first space or newline character
	    if (space_pos != std::string::npos) { // check if a space character was found
	        return(server_name.substr(0, space_pos)); // extract the substring before the space character
	    }
	}
	return ("Not found");
}

std::string server_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
	    pos += strlen("root"); // move the position to the end of "server_name"
	    std::string root = _ConfigFile.substr(pos + 1); // extract the substring starting from the next character
		size_t space_pos = root.find_first_of(" \n"); // find the position of the first space or newline character
	    if (space_pos != std::string::npos) { // check if a space character was found
	        return (root.substr(0, space_pos)); // extract the substring before the space character
	    }
	}
	return ("Not found");
}

int server_configuration::findPort()
{
	size_t pos = _ConfigFile.find("listen 0.0.0.0:"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
		pos += strlen("listen 0.0.0.0:"); // move the position to the end of "server_name"
		std::string port = _ConfigFile.substr(pos); // extract the substring starting from the next character
		size_t space_pos = port.find_first_of(" \n"); // find the position of the first space or newline character
		if (space_pos != std::string::npos) { // check if a space character was found
			if (DEBUG)
				std::cout << "server_configuration::findPort() " << port.substr(0, space_pos).c_str() << std::endl;
			return (atoi(port.substr(0, space_pos).c_str())); // extract the substring before the space character
		}
	}
	return (0);
}

std::string server_configuration::getConfigFile() { return _ConfigFile;}
std::string server_configuration::getServerName() { return _ServerName;}
std::string server_configuration::getRoot() { return _Root;}
int server_configuration::getNumberOfPorts() { return _NumberOfPorts;}
int server_configuration::getPort() { return _Port;}

std::ostream& operator <<(std::ostream &out, server_configuration &ServConfig)
{
	out << "Server name : " << ServConfig.getServerName() \
		<< "\nRoot : " << ServConfig.getRoot() \
		<< "\nNumberOfPorts : " << ServConfig.getNumberOfPorts() \
		<< "\nPort : " << ServConfig.getPort();
		
	return (out);
}