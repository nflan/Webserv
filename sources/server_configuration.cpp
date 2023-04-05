/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_configuration.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:06:26 by mgruson           #+#    #+#             */
/*   Updated: 2023/04/05 16:06:26 by mgruson          ###   ########.fr       */
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
_Port(findPort()),
_ClientMaxBodySize(findClientMaxBodySize()),
_ErrorPage(findErrorPage()),
_Location(findLocation()),
_Loc(findLoc())
{
	setCgi();
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
		size_t space_pos = root.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			return (root.substr(0, space_pos));
		}
	}
	return ("Not found");
}

int server_configuration::fillCgi(size_t pos)
{
	size_t tmp = 0;
	std::pair<std::string, std::string> cgi_pair;
	for (tmp = pos; _ConfigFile[pos] != ' '; pos++) {}
	cgi_pair.first = _ConfigFile.substr(tmp, pos - tmp);
	for (; _ConfigFile[pos] == ' '; pos++) {}
	if (_ConfigFile[pos] == ';')
		throw CgiException();
	for (tmp = pos; _ConfigFile[pos] != ' ' && _ConfigFile[pos] != ';'; pos++) {}
	cgi_pair.second = _ConfigFile.substr(tmp, pos - tmp);
	_cgi.insert(cgi_pair);
	return (pos + 1);
}

void server_configuration::setCgi()
{
	size_t pos = _ConfigFile.find("cgi");
	if (pos == std::string::npos)
		return ;
	pos += strlen("cgi");
	for (; _ConfigFile[pos] == ' '; pos++) {}
	if (_ConfigFile[pos] == ';' || _ConfigFile[pos] != '.')
		throw CgiException();
	for (; _ConfigFile[pos] != ';' && _ConfigFile[pos] != '\n';)
		pos = fillCgi(pos);
//	for (std::map<std::string, std::string>::iterator it = _cgi.begin(); it != _cgi.end(); it++) // Print CGI
//		std::cout << "first = '" << it->first << "' && second = '" << it->second << "'" << std::endl; // Print CGI
}

int server_configuration::findPort()
{
	if (_ConfigFile.find("listen 0.0.0.0:") != std::string::npos)
	{
		size_t pos = _ConfigFile.find("listen 0.0.0.0:");
		if (pos != std::string::npos) {
			pos += strlen("listen 0.0.0.0:");
			std::string port = _ConfigFile.substr(pos);
			size_t space_pos = port.find_first_of(" \n;");
			if (space_pos != std::string::npos) {
				if (DEBUG)
					std::cout << "server_configuration::findPort() " << port.substr(0, space_pos).c_str() << std::endl;
				return (atoi(port.substr(0, space_pos).c_str()));
			}
		}
	}
	else if (_ConfigFile.find("listen") != std::string::npos)
	{
		size_t pos = _ConfigFile.find("listen");
		if (pos != std::string::npos) {
			pos += strlen("listen");
			std::string port = _ConfigFile.substr(pos + 1);
			size_t space_pos = port.find_first_of(" \n;");
			if (space_pos != std::string::npos) {
				if (DEBUG)
					std::cout << "server_configuration::findPort() " << port.substr(0, space_pos).c_str() << std::endl;
				return (atoi(port.substr(0, space_pos).c_str()));
			}
		}
	}
	return (0);
}

size_t server_configuration::findClientMaxBodySize()
{
	size_t pos = _ConfigFile.find("client_max_body_size");
	if (pos != std::string::npos) {
		pos += strlen("client_max_body_size");
		std::string port = _ConfigFile.substr(pos + 1);
		size_t space_pos = port.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			if (DEBUG)
				std::cout << "server_configuration::findPort() " << port.substr(0, space_pos).c_str() << std::endl;
			int ClientBodySize = atoi(port.substr(0, space_pos).c_str());
			if (DEBUG)
				std::cout << "DEBUG : " << port.at(space_pos - 1) << std::endl;
			if (port.at(space_pos - 1) == 'M')
				return (ClientBodySize * 1048576);
			else if (port.at(space_pos - 1) == 'K')
				return (ClientBodySize * 1024);
			else
				return (ClientBodySize);
		}
	}
	return (1048576);
}

std::string server_configuration::findErrorPage()
{
	size_t pos = _ConfigFile.find("error_page");
	if (pos != std::string::npos) {
		pos += strlen("error_page");
		std::string port = _ConfigFile.substr(pos + 5);
		size_t space_pos = port.find_first_of(" \n;");
		if (space_pos != std::string::npos) {
			if (DEBUG)
				std::cout << "server_configuration::findPort() " << port.substr(0, space_pos).c_str() << std::endl;
			return (port.substr(0, space_pos).c_str());
		}
	}
	return ("");
}

std::map<std::string, std::string> server_configuration::findLocation()
{
	std::map<std::string, std::string> location_map;
	std::pair<std::string, std::string> location_pair;
	size_t pos = 0;
	size_t end_loc = 0;
	
	while (pos != std::string::npos)
	{
		pos = _ConfigFile.find("location /", pos);
		if (pos != std::string::npos)
		{
			pos += strlen("location"); 
			std::cout << "pos: " << pos << std::endl;
			std::string location_path = _ConfigFile.substr(pos + 1); 
			size_t space_pos = location_path.find_first_of("{"); 
			if (space_pos == std::string::npos) 
			{
				location_pair.first = "NULL";
				location_pair.second = "NULL";
			}
			location_pair.first = location_path.substr(0, space_pos);
			end_loc = location_path.find_first_of("{}", space_pos + 1);
			int j = 0;
			while (location_path[end_loc] == '{')
			{
				j++;
				end_loc = location_path.find_first_of("{}", end_loc + 1);
			}
			for (int i = 0; i < j; i++)
			{
				end_loc = location_path.find_first_of("}", end_loc + 1);
			}
			std::cout << "end_loc: " << end_loc << std::endl;
			if (end_loc == std::string::npos)
			{
				location_pair.first = "NULL";
				location_pair.second = "NULL";
			}
			location_pair.second = location_path.substr(space_pos + 1, end_loc);
			std::cout << "pos 0: " << pos << std::endl;
			pos = pos + end_loc;
			std::cout << "pos 1: " << pos << std::endl;
			end_loc = 0;
		}
		else
		{
			location_pair.first = "NULL";
			location_pair.second = "NULL";
		}
		location_map.insert(location_pair);
	}
	return (location_map);
}

std::map<std::string, class server_location_configuration*> server_configuration::findLoc()
{
	std::map<std::string, class server_location_configuration*>	map_location;
	std::pair<std::string, class server_location_configuration*>	pair_location;
	
	for (std::map<std::string, std::string>::iterator it = _Location.begin(); it != _Location.end(); it++)
	{
		pair_location.first = it->first;
		server_location_configuration* tmp = new server_location_configuration(it->second);
		pair_location.second = tmp;
		map_location.insert(pair_location);
	}
	return (map_location);
	
}


void	server_configuration::printCgi()
{
		for (std::map<std::string, std::string>::iterator it = _cgi.begin(); it != _cgi.end(); it++) // Print CGI
			std::cout << "- extension = '" << it->first << "' && root = '" << it->second << "'" << std::endl; // Print CGI
}

std::ostream&	server_configuration::printLocation(std::ostream &out)
{
		for (std::map<std::string, std::string>::iterator it = _Location.begin(); it != _Location.end(); it++)
			out << "\npath : " << it->first << "\nconf : " << it->second ;
		return (out);
}

std::ostream&	server_configuration::printLoc(std::ostream &out)
{
		
		for (std::map<std::string, class server_location_configuration*>::iterator it = _Loc.begin(); it != _Loc.end(); it++)
		{
			out << "\nLocation configurations  for " << it->first \
			<< "\nRoot : " << it->second->getRoot() \
			<< "\nDirectoryListing : " << it->second->getDirectoryListing() \
			<< "\nDirectoryRequest : " << it->second->getDirectoryRequest() \
			<< "\nCGI : " \
			<< "\n UploadStore : " << it->second->getUploadStore();
		}
		return (out);
}

std::string server_configuration::getConfigFile() { return _ConfigFile;}
std::string server_configuration::getServerName() { return _ServerName;}
std::string server_configuration::getRoot() { return _Root;}
int server_configuration::getPort() { return _Port;}
size_t server_configuration::getClientMaxBodySize() { return _ClientMaxBodySize;}
std::map<std::string, std::string> server_configuration::getCgi() { return (_cgi); }
std::string server_configuration::getErrorPage() { return _ErrorPage;}

const char *	server_configuration::CgiException::what() const throw()
{
	return ("CGI error\n");
}

std::ostream& operator <<(std::ostream &out, server_configuration &ServConfig)
{
	out << "Server name : " << ServConfig.getServerName() \
		<< "\nRoot : " << ServConfig.getRoot() \
		<< "\nPort : " << ServConfig.getPort() \
		<< "\nCliend Body Limit : " << ServConfig.getClientMaxBodySize() \
		<< "\nError page : " << ServConfig.getErrorPage() \
		<< "\nCGI : " \
		// << "\nLocation : " << ServConfig.printLocation(out) 
		<< "\nLocation : " << ServConfig.printLoc(out) << std::endl;

	return (out);
}

// 	std::map<std::string, class server_location_configuration*> _Loc;
