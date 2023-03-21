/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_response.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:09:26 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/20 15:12:34 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP

#include <iostream>

class server_response
{
	private:
	std::string _ServerResponse;
	
	public:
	server_response();
	server_response(server_response const &obj);
	~server_response();
	server_response &operator=(server_response const &obj);
};

#endif
