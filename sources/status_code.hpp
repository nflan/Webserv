/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:33:06 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/20 14:56:10 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_CODE_HPP
#define STATUS_CODE_HPP

#include <iostream>

class status_code
{
	private:
	const std::string _Status100 = "100 Continue";
	const std::string _Status101 = "101 Switching Protocols";
	const std::string _Status200 = "200 OK";
	const std::string _Status201 = "201 Created";
	const std::string _Status202 = "202 Accepted";
	const std::string _Status203 = "203 Non-Authoritative Information";
	const std::string _Status204 = "204 No Content";
	const std::string _Status205 = "205 Reset Content";
	const std::string _Status206 = "206 Partial Content";
	const std::string _Status300 = "300 Multiple Choices";
	const std::string _Status301 = "301 Moved Permanently";
	const std::string _Status302 = "302 Found";
	const std::string _Status303 = "303 See Other";
	const std::string _Status304 = "304 Not Modified";
	const std::string _Status305 = "305 Use Proxy";
	const std::string _Status307 = "307 Temporary Redirect";
	const std::string _Status400 = "400 Bad Request";
	const std::string _Status401 = "401 Unauthorized";
	const std::string _Status402 = "402 Payment Required";
	const std::string _Status403 = "403 Forbidden";
	const std::string _Status404 = "404 Not Found";
	const std::string _Status405 = "405 Method Not Allowed ";
	const std::string _Status406 = "406 Not Acceptable";
	const std::string _Status407 = "407 Proxy Authentication Required";
	const std::string _Status408 = "408 Request Time-out";
	const std::string _Status409 = "409 Conflict";
	const std::string _Status410 = "410 Gone";
	const std::string _Status411 = "411 Length Required";
	const std::string _Status412 = "412 Precondition Failed";
	const std::string _Status413 = "413 Request Entity Too Large";
	const std::string _Status414 = "414 Request-URI Too Large";
	const std::string _Status415 = "415 Unsupported Media Type";
	const std::string _Status416 = "416 Requested range not satisfiable";
	const std::string _Status417 = "417 Expectation Failed";
	const std::string _Status500 = "500 Internal Server Error";
	const std::string _Status501 = "501 Not Implemented";
	const std::string _Status502 = "502 Bad Gateway";
	const std::string _Status503 = "503 Service Unavailable";
	const std::string _Status504 = "504 Gateway Time-out";
	const std::string _Status505 = "505 HTTP Version not supported";
	
	public:
	status_code();
	status_code(status_code const &obj);
	~status_code();
	status_code &operator=(status_code const &obj);
	
	static std::string getStatus100() const;
	static std::string getStatus101() const;
	static std::string getStatus200() const;
	static std::string getStatus201() const;
	static std::string getStatus202() const;
	static std::string getStatus203() const;
	static std::string getStatus204() const;
	static std::string getStatus205() const;
	static std::string getStatus206() const;
	static std::string getStatus300() const;
	static std::string getStatus301() const;
	static std::string getStatus302() const;
	static std::string getStatus303() const;
	static std::string getStatus304() const;
	static std::string getStatus305() const;
	static std::string getStatus307() const;
	static std::string getStatus400() const;
	static std::string getStatus401() const;
	static std::string getStatus402() const;
	static std::string getStatus403() const;
	static std::string getStatus404() const;
	static std::string getStatus405() const;
	static std::string getStatus406() const;
	static std::string getStatus407() const;
	static std::string getStatus408() const;
	static std::string getStatus409() const;
	static std::string getStatus410() const;
	static std::string getStatus411() const;
	static std::string getStatus412() const;
	static std::string getStatus413() const;
	static std::string getStatus414() const;
	static std::string getStatus415() const;
	static std::string getStatus416() const;
	static std::string getStatus417() const;
	static std::string getStatus500() const;
	static std::string getStatus501() const;
	static std::string getStatus502() const;
	static std::string getStatus503() const;
	static std::string getStatus504() const;
	static std::string getStatus505() const;
	
};

#endif

