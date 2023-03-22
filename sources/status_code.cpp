/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:33:22 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/20 14:57:02 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status_code.hpp"

status_code::status_code()
{
	std::cout << "status_code Default Constructor called" << std::endl;
}
status_code::status_code(status_code const &obj)
{
	*this = obj;
}
status_code::~status_code()
{
	std::cout << "status_code Destructor called" << std::endl;
}
status_code &status_code::operator=(status_code const &obj)
{
	std::cout << "status_code Copy assignment operator called" << std::endl;
	return *this;
}

std::string getStatus100() const
{
	return (_Status100)
}

std::string getStatus101() const
{
	return (_Status101)
}

std::string getStatus200() const
{
	return (_Status200)
}

std::string getStatus201() const
{
	return (_Status201)
}

std::string getStatus202() const
{
	return (_Status202)
}

std::string getStatus203() const
{
	return (_Status203)
}

std::string getStatus204() const
{
	return (_Status204)
}

std::string getStatus205() const
{
	return (_Status205)
}

std::string getStatus206() const
{
	return (_Status206)
}

std::string getStatus300() const
{
	return (_Status300)
}

std::string getStatus301() const
{
	return (_Status301)
}

std::string getStatus302() const
{
	return (_Status302)
}

std::string getStatus303() const
{
	return (_Status303)
}

std::string getStatus304() const
{
	return (_Status304)
}

std::string getStatus305() const
{
	return (_Status305)
}

std::string getStatus307() const
{
	return (_Status307)
}

std::string getStatus400() const
{
	return (_Status400)
}

std::string getStatus401() const
{
	return (_Status401)
}

std::string getStatus402() const
{
	return (_Status402)
}

std::string getStatus403() const
{
	return (_Status403)
}

std::string getStatus404() const
{
	return (_Status404)
}

std::string getStatus405() const
{
	return (_Status405)
}

std::string getStatus406() const
{
	return (_Status406)
}

std::string getStatus407() const
{
	return (_Status407)
}

std::string getStatus408() const
{
	return (_Status408)
}

std::string getStatus409() const
{
	return (_Status409)
}

std::string getStatus410() const
{
	return (_Status410)
}

std::string getStatus411() const
{
	return (_Status411)
}

std::string getStatus412() const
{
	return (_Status412)
}

std::string getStatus413() const
{
	return (_Status413)
}

std::string getStatus414() const
{
	return (_Status414)
}

std::string getStatus415() const
{
	return (_Status415)
}

std::string getStatus416() const
{
	return (_Status416)
}

std::string getStatus417() const
{
	return (_Status417)
}

std::string getStatus500() const
{
	return (_Status500)
}

std::string getStatus501() const
{
	return (_Status501)
}

std::string getStatus502() const
{
	return (_Status502)
}

std::string getStatus503() const
{
	return (_Status503)
}

std::string getStatus504() const
{
	return (_Status504)
}

std::string getStatus505() const
{
	return (_Status505)
}
