/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_location_configuration.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:07:36 by mgruson           #+#    #+#             */
/*   Updated: 2023/04/04 17:14:29 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_LOCATION_CONFIGURATION_HPP
#define SERVER_LOCATION_CONFIGURATION_HPP

#include <iostream>

class server_location_configuration
{
	private:
	std::string	_Uri;
	std::string	_HttpAccepted;
	std::string	_HttpRedirection;
	std::string	_Root;
	bool		_DirectoryListing;
	std::string	_DirectoryRequest;
	std::map<std::string, std::string>	_Cgi; // To SEE
	std::string Method;
	std::string UploadStore;

	public:
	server_location_configuration();
	server_location_configuration(server_location_configuration const &obj);
	~server_location_configuration();
	server_location_configuration &operator=(server_location_configuration const &obj);

	std::string findRoot();
	std::string findUploadStore();


};

#endif