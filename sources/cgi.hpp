/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:06 by nflan             #+#    #+#             */
/*   Updated: 2023/03/27 18:54:11 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <iostream>

class Cgi
{
	public:
		Cgi(std::string & cgi_path, std::string & file_path, std::vector<std::string> & env);
		Cgi(const Cgi & o);
		~Cgi();

		Cgi & operator=(const Cgi & o);
		void	print() const;
		const int*	getPdes() const;
		char**	getCmd() const;
		char**	getEnvp() const;
		pid_t	getPid() const;
		void	setPid();
		void	setPdes();
		void	closePdes();


	private:
		char**	_cmd;
		char**	_envp;
		pid_t	_pid;
		int		_pdes[2];


		Cgi();

};

class PipeException: public std::exception {
	public:
		virtual const char *	what() const throw();
};
class ExecveException: public std::exception {
	public:
		virtual const char *	what() const throw();
};
class ForkException: public std::exception {
	public:
		virtual const char *	what() const throw();
};

#endif
