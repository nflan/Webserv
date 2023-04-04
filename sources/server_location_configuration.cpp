/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_location_configuration.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:08:06 by mgruson           #+#    #+#             */
/*   Updated: 2023/04/04 17:14:50 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_location_configuration.hpp"

server_location_configuration::server_location_configuration()
{
	std::cout << "server_location_configuration Default Constructor called" << std::endl;
}
server_location_configuration::server_location_configuration(server_location_configuration const &obj)
{
	*this = obj;
}
server_location_configuration::~server_location_configuration()
{
	std::cout << "server_location_configuration Destructor called" << std::endl;
}
server_location_configuration &server_location_configuration::operator=(server_location_configuration const &obj)
{
	std::cout << "server_location_configuration Copy assignment operator called" << std::endl;
	return *this;
}

std::string server_location_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
} // OK

std::string server_location_configuration::findUploadStore()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}

std::string server_location_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}

std::string server_location_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}

std::string server_location_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}

std::string server_location_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}

std::string server_location_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}

std::string server_location_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}

std::string server_location_configuration::findRoot()
{
	size_t pos = _ConfigFile.find("root");
	if (pos != std::string::npos) {
		pos += strlen("root");
		std::string root = _ConfigFile.substr(pos + 1);
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}