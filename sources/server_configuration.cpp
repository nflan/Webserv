/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_config.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:06:26 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/16 12:49:28 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_configuration.hpp"

server_configuration::server_configuration()
{
	std::cout << "server_configuration Default Constructor called" << std::endl;
}

std::string server_configuration::convertConfigFile(std::string &ConfigFile)
{
	std::ifstream file(ConfigFile);
	
	// Check if we successfully opened the file
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file for reading");
	}
	
	// Read the entire file into a string
	std::string ConfigFileStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Close the file
	file.close();

	return (ConfigFileStr);
}

int server_configuration::findNumberOfPorts()
{
	int count = utils::countSubstringOccurrences(_ConfigFile, "server {");
	return (count);
}

std::string server_configuration::findServerName()
{
	int pos = _ConfigFile.find("server_name"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
	    pos += strlen("server_name"); // move the position to the end of "server_name"
	    std::string server_name = input.substr(pos + 1); // extract the substring starting from the next character
		size_t space_pos = server_name.find_first_of(" \n"); // find the position of the first space or newline character
	    if (space_pos != std::string::npos) { // check if a space character was found
	        return(server_name.substr(0, space_pos)); // extract the substring before the space character
	    }
	}
	return ("Not found");
}

std::string server_configuration::findRoot()
{
	int pos = _ConfigFile.find("root"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
	    pos += strlen("root"); // move the position to the end of "server_name"
	    std::string root = input.substr(pos + 1); // extract the substring starting from the next character
		size_t space_pos = root.find_first_of(" \n"); // find the position of the first space or newline character
	    if (space_pos != std::string::npos) { // check if a space character was found
	        return (root.substr(0, space_pos)); // extract the substring before the space character
	    }
	}
	return ("Not found");
}

server_configuration::findPort()
{
	int pos = _ConfigFile.find("listen 0.0.0.0:"); // find the position of "server_name" in the string
	if (pos != std::string::npos) { // check if "server_name" was found
	    pos += strlen("listen 0.0.0.0:"); // move the position to the end of "server_name"
	    std::string port = input.substr(pos + 1); // extract the substring starting from the next character
		size_t space_pos = port.find_first_of(" \n"); // find the position of the first space or newline character
	    if (space_pos != std::string::npos) { // check if a space character was found
	        return (std::stoi(port.substr(0, space_pos))); // extract the substring before the space character
	    }
	}
	return ("Not found");
}

server_configuration::server_configuration(std::string ConfigFile) : 
_ConfigFile(convertConfigFile(ConfigFile)),
_NumberOfPorts(findNumberOfPorts()),
_ServerName(findServerName())
_Root(findRoot())
_Port(findPort())
{
}

server_configuration::server_configuration(server_configuration const &obj)
{
	*this = obj;
}
server_configuration::~server_configuration()
{
	std::cout << "server_configuration Destructor called" << std::endl;
}
server_configuration &server_configuration::operator=(server_configuration const &obj)
{
	std::cout << "server_configuration Copy assignment operator called" << std::endl;
	return *this;
}

