/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_response.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:09:46 by mgruson           #+#    #+#             */
/*   Updated: 2023/04/12 13:02:36 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_response.hpp"

server_response::server_response() : _status_code(200), _body(""), _ServerResponse("")
{
	this->addType();
	std::cout << "server_response Default Constructor called" << std::endl;
}

server_response::server_response(int stat) : _status_code(stat), _body(""), _ServerResponse("")
{
	this->addType();
	std::cout << "server_response int Constructor called" << std::endl;
}

server_response::server_response(server_response const &obj)
{
	*this = obj;
}

server_response::~server_response()
{
	std::cout << "server_response Destructor called" << std::endl;
}

server_response &server_response::operator=(server_response const &obj)
{
	(void)obj;
	std::cout << "server_response Copy assignment operator called" << std::endl;
	return *this;
}

// void server_response::generate_post_response(const std::string& request_uri, const std::string& data)
// {
// 	// Par exemple, on pourrait simplement renvoyer un message de confirmation avec les données reçues
// 	std::string response_body = "Données reçues : " + data;
	
// 	// Ensuite, on prépare et envoie la réponse
// 	std::ostringstream response_stream;
// 	response_stream << "HTTP/1.1 200 OK\r\n"
// 					<< "Content-Type: text/plain\r\n"
// 					<< "Content-Length: " << response_body.length() << "\r\n"
// 					<< "\r\n"
// 					<< response_body;
// 	std::string response = response_stream.str();
// 	send_response_to_client(response);
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

void	server_response::addType()
{
	_contentType.insert(std::make_pair<std::string, std::string>("html", "Content-Type: text/html\r\n"));
	_contentType.insert(std::make_pair<std::string, std::string>("jpg", "Content-Type: image/jpeg\r\n"));
}

std::string server_response::getType(std::string type)
{
	std::cout << "TEST : " << type << std::endl;
	for (std::map<std::string, std::string>::iterator it = _contentType.begin(); it != _contentType.end(); it++)
	{
		if (type == it->first)
			return (it->second);
	}
	return ("Content-Type: text/html\r\n");
}

void	server_response::todo(const server_request& Server_Request, int conn_sock, server_configuration *server)
{
	enum imethod {GET, POST, DELETE};
	std::stringstream response;
	std::string	Root = server->getRoot();
	int n = 0;
	const std::string ftab[3] = {"GET", "POST", "DELETE"};
	std::string		content;
	(void)Root;
	std::string tmp;
	if (Root.size() == 1 && Root.find("/", 0, 1))
		tmp = "." + Server_Request.getRequestURI();
	else
		tmp = Root + Server_Request.getRequestURI();
	std::cout << "\nC0 = '" << tmp << "'\n" << std::endl;
	if (tmp.size() == 3 && tmp.find(".//") != std::string::npos)
	{
		// tmp.erase();
		std::cout << "\nC1\n" << std::endl;
		tmp += "index.html";
	}
	if (tmp[tmp.size() - 1] == '/')
	{
		tmp += "index.html";
	}

	for (; n < 4; n++)
	{
		if (n != 3 && ftab[n] == Server_Request.getMethod()) // OK 
		{
			break ;
		}
	}
	switch (n)
	{
		case GET :
		{
			std::ifstream file(tmp.c_str());
			std::stringstream buffer;
			if (!file.is_open())
			{
				if (_status_code == 200)
					_status_code = 404;
			}
			else
			{
				buffer << file.rdbuf();
				content = buffer.str();
			}
			std::cerr << "AFTER RESPONSE IFSTREAM\r\n" << std::endl;
			createResponse(server, content, Server_Request);
			std::cout << std::endl << "SERVER RESPONSE CONSTRUITE -> " << std::endl << _ServerResponse << std::endl << std::endl;
			send(conn_sock, _ServerResponse.c_str() , _ServerResponse.size(), 0);
			std::cerr << "\nREPONSE SEND :\n";
			std::cerr << _ServerResponse << std::endl;
			break ;
		}
		case POST :
		{
			// std::string infilename = "./site/42.jpg";
			// std::ifstream inputFile(infilename.c_str(), std::ios::binary);
			// std::stringstream response1;
			std::string outfilename = "./test.jpg"; // OK 1
			std::ofstream outputFile(outfilename.c_str(), std::ios::binary); // OK 1

			// // Get the file size
			// inputFile.seekg(0, std::ios::end);
			// int fileSize = inputFile.tellg();
			// inputFile.seekg(0, std::ios::beg);
			
			// // Read the contents of the file into a buffer
			// std::vector<unsigned char> fileBuffer(fileSize);
			// inputFile.read(reinterpret_cast<char*>(fileBuffer.data()), fileSize);
			
			// inputFile.close();

			// outputFile << reinterpret_cast<char*>(fileBuffer.data());
			// outputFile.close();

			/*OK 1*/
			std::string tmp = "./site/42.jpg";
            std::cout << "\nC0bis = '" << tmp << "'\n" << std::endl;
            std::ifstream file(tmp.c_str(), std::ifstream::binary);
            // std::stringstream buffer;
            std::filebuf* pbuf = file.rdbuf();
            std::size_t size = pbuf->pubseekoff(0, file.end, file.in);
            pbuf->pubseekpos (0,file.in);
            char *buffer= new char[size];
            pbuf->sgetn(buffer, size);
            file.close();
            std::string content(buffer, size);
			std::cout << "\nC2\n" << std::endl;
			/*OK 1*/

            // buffer << file.rdbuf();
            // std::cout << "\nBUFFER = " << buffer.str() << "\r\n" << std::endl;
            // std::string content = buffer.str();
            response << "HTTP/1.1 200 OK\r\n";
            response << "content-Type: image/jpeg\r\n";
            // response << "Content-Type: text/plain; charset=UTF-8\r\n";
            response << "content-Length: " << size << "\r\n";
            response << "\r\n";
            response << content << '\0' << "\r\n";
			outputFile << content ;
			outputFile.close();
            // }
            // response << "Hello world!\r\n";
            std::cerr << "AFTER RESPONSE IFSTREAM\r\n" << std::endl;
            std::cout << buffer << std::endl;
			delete [] buffer;
			_ServerResponse = response.str();
			send(conn_sock, _ServerResponse.c_str() , _ServerResponse.size(), 0);
/**********************************************************************************/
			// std::cout << "Successfully wrote to " << outfilename << std::endl;
			// response1 << "HTTP/1.1 200 OK\r\n";
			// response1 << "Content-Length: " << fileSize << "\r\n";
			// response1 << "\r\n";
			// response1.write(reinterpret_cast<char*>(fileBuffer.data()), fileSize);
			// std::string response_str1 = response1.str();
			// send(conn_sock, response_str1.c_str() , response_str1.size(), 0);

			break ;
		}
		case DELETE :
		{
//delete -> nftw avec flag pour partir de la fin
			std::cout << "\ntmp.c_str() = " << tmp << "\n" << std::endl;
			try
			{
				this->delete_dir(tmp.c_str()); // penser a changer le status code en 404 / 403 si besoin;
			}
			catch (server_response::DeleteException& e) {}
			if (_status_code == 200)
				content = "OK delete";
	//		if (std::remove(tmp.c_str()) != 0) // the remove function returns 0 on success
			createResponse(server, content, Server_Request);
			send(conn_sock, _ServerResponse.c_str() , _ServerResponse.size(), 0);
			break ;
		}
		default :
		{
			response << addHeader(STATUS500, server->getErrorPage().find(STATUS500)->second, Server_Request);
			response << addBody(server->getErrorPage()[STATUS500].second);
			_ServerResponse = response.str();
			send(conn_sock, _ServerResponse.c_str() , _ServerResponse.size(), 0);
			break ;
		}
	}
	return ;
}

static int	delete_fct(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
	static_cast<void>(sb);
	static_cast<void>(ftwbuf);

	if (tflag == FTW_DP)
		return (rmdir(fpath), 1);
	else
		if (unlink(fpath))
			return (1);
	return (0);
}

void	server_response::delete_dir(const char* path)
{
	if (access(path, X_OK))
		_status_code = 403;
	if (nftw(path, delete_fct, 500, FTW_DEPTH))
		_status_code = 404;
}

/*void	server_response::delete_dir(const char * path)
{
	DIR	*dir = NULL;
	struct dirent *send = NULL;
	std::string	test;

	dir = opendir(path);
	if (errno == EACCES || errno == EMFILE || errno == ENFILE || errno == ENOENT || errno == ENOMEM || errno == ENOTDIR)
	{
		if (errno == ENOENT)
			_status_code = 404;
		else if (errno == ENOTDIR && std::remove(path) != 0) // the remove function returns 0 on success
			_status_code = 404;
		else if (errno == EACCES)
			_status_code = 403;
		else if (errno == EMFILE || errno == ENFILE || errno == ENOMEM)
			_status_code = 500;
		throw DeleteException();
	}
	send = readdir(dir);
	if (!send)
	{
		_status_code = 500;
		closedir(dir);
		throw DeleteException();
	}
	while (send)
	{
		test = send->d_name;
		std::cerr << "coucou je suis dans un dossier et je vais dans un fichier ou dossier" << std::endl;
		std::cerr << "name -> " << send->d_name << std::endl;
		if (test != "." && test != "..")
			delete_dir(send->d_name);
		send = readdir(dir);
	}
}*/

std::string	server_response::addHeader(std::string statusMsg, std::pair<std::string, std::string> statusContent, const server_request& Server_Request)
{
	std::string	header;
	std::stringstream	response;
	
	response << Server_Request.getVersion() << " " << _status_code << " " << statusMsg << "\r\n";  /* ajouter la version HTTP (parsing) */ 
	if (statusContent.first != "")
	{
		if (statusContent.first.find('.', 0) != std::string::npos)
			response << this->getType(statusContent.first.substr(statusContent.first.find('.', 0) + 1));
	}
	else
		response << this->getType(Server_Request.getType()); // modif text/html (parsing) -> peut etre faire map de content type / mime en fonction de .py = /truc .html = /text/html etc.
	header = response.str();
	return (header);
}

std::string	server_response::addBody(std::string msg)
{
	std::string	body;
	std::stringstream	response;

	response << "Content-Length: " << msg.size() << "\r\n\r\n";
	response << msg << "\r\n";
	body = response.str();
	return (body);
}

void	server_response::createResponse(server_configuration * server, std::string file, const server_request& Server_Request)
{
	std::stringstream	response;
	enum	status { INFO, SUCCESS, REDIRECTION, CLIENT, SERVER };
	int	n = 0;
	int	tmp = _status_code / 100 - 1;
	for (; n != tmp && n < 5; n++) {}
	switch (n)
	{
		case INFO:
		{
			std::cout << "JE SUIS DANS INFO" << std::endl;
			switch (_status_code)
				case 100:
				{
					response << addHeader(STATUS100, server->getErrorPage().find(STATUS100)->second, Server_Request);
					response << addBody(server->getErrorPage()[STATUS100].second);
					break;
				}
				case 101:
				{
					response << addHeader(STATUS101, server->getErrorPage().find(STATUS101)->second, Server_Request);
					response << addBody(server->getErrorPage()[STATUS101].second);
					break;
				}
			break;
		}
		case SUCCESS:
		{
			std::cout << "JE SUIS DANS SUCCESS" << std::endl;
			switch (_status_code)
			{
				case 200:
				{
					response << addHeader(STATUS200, server->getErrorPage().find(STATUS200)->second, Server_Request);
					response << addBody(file);
					break;
				}
				case 201:
				{
					break;
				}
				case 202:
				{
					break;
				}
				case 203:
				{
					break;
				}
				case 204:
				{
					break;
				}
				case 205:
				{
					break;
				}
				case 206:
				{
					break;
				}
			}
			break;
		}
		case REDIRECTION:
		{
			std::cout << "JE SUIS DANS REDIRECTION" << std::endl;
			switch (_status_code)
				case 300:
				{
					break;
				}
				case 301:
				{
					break;
				}
				case 302:
				{
					break;
				}
				case 303:
				{
					break;
				}
				case 304:
				{
					break;
				}
				case 305:
				{
					break;
				}
				case 307:
				{
					break;
				}
			break;
		}
		case CLIENT:
		{
			std::cout << "JE SUIS DANS CLIENT" << std::endl;
			switch (_status_code)
			{
				case 400:
				{
					break;
				}
				case 401:
				{
					break;
				}
				case 402:
				{
					break;
				}
				case 403:
				{
					break;
				}
				case 404:
				{
					response << addHeader(STATUS404, server->getErrorPage().find(STATUS404)->second, Server_Request);
					response << addBody(server->getErrorPage()[STATUS404].second);
					break;
				}
				case 405:
				{
					break;
				}
				case 406:
				{
					break;
				}
				case 407:
				{
					break;
				}
				case 408:
				{
					break;
				}
				case 409:
				{
					break;
				}
				case 410:
				{
					break;
				}
				case 411:
				{
					break;
				}
				case 412:
				{
					break;
				}
				case 413:
				{
					break;
				}
				case 414:
				{
					break;
				}
				case 415:
				{
					break;
				}
				case 416:
				{
					break;
				}
				case 417:
				{
					break;
				}
			}
			break;
		}
		case SERVER:
		{
			std::cout << "JE SUIS DANS SERVER" << std::endl;
			switch (_status_code)
			{
				case 500:
				{
					response << addHeader(STATUS500, server->getErrorPage().find(STATUS500)->second, Server_Request);
					response << addBody(server->getErrorPage()[STATUS500].second);
					break;
				}
				case 501:
				{
					break;
				}
				case 502:
				{
					break;
				}
				case 503:
				{
					break;
				}
				case 504:
				{
					break;
				}
				case 505:
				{
					break;
				}
			}
			break;
		}
		default:
			std::cout << "default" << std::endl;
	}
	_ServerResponse = response.str();
}

const char *	server_response::DeleteException::what() const throw()
{
	return ("Delete error\n");
}
