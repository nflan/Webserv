/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:23 by nflan             #+#    #+#             */
/*   Updated: 2023/03/27 19:13:52 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>

Cgi::Cgi(std::string & cgi_path, std::string & file_path, std::vector<std::string> & env)
{
	_cmd = new char*[3];
	_cmd[0] = &(cgi_path[0]);
	_cmd[1] = &(file_path[0]);
	_cmd[2] = NULL;
	_envp = new char* [env.size() + 1];
	size_t	i = 0;
	for (std::vector<std::string>::iterator it = env.begin(); it != env.end(); it++, i++)
		_envp[i] = &((*it)[0]);
	_envp[env.size()] = NULL;
	_pid = -1;
}

Cgi::~Cgi()
{
	delete [] _cmd;
	delete [] _envp;
}

const int*	Cgi::getPdes() const
{
	return (_pdes);
}

pid_t	Cgi::getPid() const
{
	return (_pid);
}

char**	Cgi::getCmd() const
{
	return (_cmd);
}

char**	Cgi::getEnvp() const
{
	return (_envp);
}

void	Cgi::setPid()
{
	_pid = fork();
	if (static_cast<int>(_pid) == -1)
		throw ForkException();
}

void	Cgi::setPdes()
{
	if (pipe(_pdes) == -1)
		throw PipeException();
}

void	Cgi::closePdes()
{
	if (_pdes[0] > 2)
		close(_pdes[0]);
	if (_pdes[1] > 2)
		close(_pdes[1]);
}

void	Cgi::print() const
{
	size_t	i = 0;
	for (; _cmd[i]; i++)
		printf("cmd = '%s'\n", _cmd[i]);
	for (i = 0; _envp[i]; i++)
		printf("envp = '%s'\n", _envp[i]);
}

const char *	PipeException::what() const throw()
{
	return ("Pipe Error!");
}

const char *	ForkException::what() const throw()
{
	return ("Pipe Error!");
}

const char *	ExecveException::what() const throw()
{
	return ("Pipe Error!");
}

int	main(int ac, char **av, char **envp)
{
	int	status;
	if (ac != 2)
		return (1);
	std::vector<std::string>	env;
	for (size_t i = 0; envp[i]; i++)
		env.push_back(envp[i]);
	std::string a("/usr/bin/php-cgi");
	std::string cmd(av[1]);
	std::string	tmp;
	std::string	tmp2;
	try {
		Cgi	test(a, cmd, env);
		test.setPdes();
		test.setPid();
	//	dup2(test.getPdes()[1], STDOUT_FILENO);
		if (test.getPid() == 0)
		{
			if (execve((test.getCmd())[0], test.getCmd(), test.getEnvp()))
				throw ExecveException();
		}
		waitpid(test.getPid(), &status, 0);
		while (read(test.getPdes()[1], &tmp, 10))
			tmp2 += tmp;
		test.closePdes();
		std::cout << tmp2 << std::endl;
	}
	catch ( std::exception& e )
	{
		return (std::cerr << e.what() << std::endl, 1);
	}
	return (0);
}
