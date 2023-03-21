/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_response.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:09:46 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/20 15:09:51 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_response.hpp"

server_response::server_response()
{
	std::cout << "server_response Default Constructor called" << std::endl;
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
	std::cout << "server_response Copy assignment operator called" << std::endl;
	return *this;
}
