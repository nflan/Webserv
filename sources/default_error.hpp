/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_error.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:18:43 by nflan             #+#    #+#             */
/*   Updated: 2023/04/04 18:40:01 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Sources: https://www.rfc-editor.org/rfc/rfc9110.html (rfc9110 status codes) and https://http.cat/ (examples and pictures)

#ifndef DEFAULT_ERROR_HPP
#define DEFAULT_ERROR_HPP

//1XX --> status code d'information (requete recu et continue son cours)
# define STATUS100 "Continue"
# define HTML100 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>100 Continue</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>100 Continue</h1><img src=\"https://http.cat/100\" style=\"display: block;margin: auto;\" alt=\"100 Continue\"g><p>webserv</p></body></html>"

# define STATUS101 "Switching Protocols"
# define HTML101 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>101 Switching Protocols</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>101 Switching Protocols</h1><img src=\"https://http.cat/101\" style=\"display: block;margin: auto;\" alt=\"101 Switching Protocols\"g><p>webserv</p></body></html>"

//2XX --> Success (requete recu, comprise, acceptee)
# define STATUS200 "OK"
# define HTML200 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>200 OK</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>200 OK</h1><img src=\"https://http.cat/200\" style=\"display: block;margin: auto;\" alt=\"200 OK\"g><p>webserv</p></body></html>"

# define STATUS201 "Created"
# define HTML201 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>201 Created</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>201 Created</h1><img src=\"https://http.cat/201\" style=\"display: block;margin: auto;\" alt=\"201 Created\"g><p>webserv</p></body></html>"

# define STATUS202 "Accepted"
# define HTML202 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>202 Accepted</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>202 Accepted</h1><img src=\"https://http.cat/202\" style=\"display: block;margin: auto;\" alt=\"202 Accepted\"g><p>webserv</p></body></html>"

# define STATUS203 "Non-Authoritative Information"
# define HTML203 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>203 Non-Authoritative Information</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>203 Non-Authoritative Information</h1><img src=\"https://http.cat/203\" style=\"display: block;margin: auto;\" alt=\"203 Non-Authoritative Information\"><p>webserv</p></body></html>"

# define STATUS204 "No Content"
# define HTML204 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>204 No Content</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>204 No Content</h1><img src=\"https://http.cat/204\" style=\"display: block;margin: auto;\" alt=\"204 No Content\"g><p>webserv</p></body></html>"

# define STATUS205 "Reset Content"
# define HTML205 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>205 Reset Content</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>205 Reset Content</h1><img src=\"https://us.123rf.com/450wm/upixel123/upixel1231405/upixel123140500085/28651041-signe-de-l-ordinateur-205-r%C3%A9initialiser-contenu.jpg?ver=6\" style=\"display: block;margin: auto;\" alt=\"205 Reset Content\"g><p>webserv</p></body></html>"

# define STATUS206 "Partial Content"
# define HTML206 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>206 Partial Content</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>206 Partial Content</h1><img src=\"https://http.cat/206\" style=\"display: block;margin: auto;\" alt=\"206 Partial Content\"><p>webserv</p></body></html>"

//3XX --> Redirection (autres actions a faire pour completer la requete)
# define STATUS300 "Multiple Choices"
# define HTML300 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>300 Multiple Choices</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>300 Multiple Choices</h1><img src=\"https://http.cat/300\" style=\"display: block;margin: auto;\" alt=\"300 Multiple Choices\"g><p>webserv</p></body></html>"

# define STATUS301 "Moved Permanently"
# define HTML301 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>301 Moved Permanently</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>301 Moved Permanently</h1><img src=\"https://http.cat/301\" style=\"display: block;margin: auto;\" alt=\"301 Moved Permanently\"g><p>webserv</p></body></html>"

# define STATUS302 "Found"
# define HTML302 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>302 Found</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>302 Found</h1><img src=\"https://http.cat/302\" style=\"display: block;margin: auto;\" alt=\"302 Found\"g><p>webserv</p></body></html>"

# define STATUS303 "See Other"
# define HTML303 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>303 See Other</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>303 See Other</h1><img src=\"https://http.cat/303\" style=\"display: block;margin: auto;\" alt=\"303 See Other\"><p>webserv</p></body></html>"

# define STATUS304 "Not Modified"
# define HTML304 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>304 Not Modified</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>304 Not Modified</h1><img src=\"https://http.cat/304\" style=\"display: block;margin: auto;\" alt=\"304 Not Modified\"><p>webserv</p></body></html>"

# define STATUS305 "Use Proxy"
# define HTML305 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>305 Use Proxy</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>305 Use Proxy</h1><img src=\"https://http.cat/305\" style=\"display: block;margin: auto;\" alt=\"305 Use Proxy\"><p>webserv</p></body></html>"

# define STATUS307 "Temporary Redirect"
# define HTML307 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>307 Temporary Redirect</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>307 Temporary Redirect</h1><img src=\"https://http.cat/307\" style=\"display: block;margin: auto;\" alt=\"307 Temporary Redirect\"><p>webserv</p></body></html>"

//4XX --> Client error (erreur de requete / requete ne peut pas etre traitee)
# define STATUS400 "Bad Request"
# define HTML400 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>400 Bad Request</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>400 Bad Request</h1><img src=\"https://http.cat/400\" style=\"display: block;margin: auto;\" alt=\"400 Bad Request\"><p>webserv</p></body></html>"

# define STATUS401 "Unauthorized"
# define HTML401 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>401 Unauthorized</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>401 Unauthorized</h1><img src=\"https://http.cat/401\" style=\"display: block;margin: auto;\" alt=\"401 Unauthorized\"><p>webserv</p></body></html>"

# define STATUS403 "Forbidden"
# define HTML403 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>403 Forbidden</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>403 Forbidden</h1><img src=\"https://http.cat/403\" style=\"display: block;margin: auto;\" alt=\"403 Forbidden\"><p>webserv</p></body></html>"

# define STATUS404 "Not Found"
# define HTML404 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>404 Not Found</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>404 Not Found</h1><img src=\"https://http.cat/404\" style=\"display: block;margin: auto;\" alt=\"404 Not Found\"><p>webserv</p></body></html>"

# define STATUS405 "Method Not Allowed"
# define HTML405 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>405 Method Not Allowed</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>405 Method Not Allowed</h1><img src=\"https://http.cat/405\" style=\"display: block;margin: auto;\" alt=\"405 Method Not Allowed\"><p>webserv</p></body></html>"

# define STATUS406 "Not Acceptable"
# define HTML406 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>406 Not Acceptable</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>406 Not Acceptable</h1><img src=\"https://http.cat/406\" style=\"display: block;margin: auto;\" alt=\"406 Not Acceptable\"><p>webserv</p></body></html>"

# define STATUS407 "Proxy Authentification Required"
# define HTML407 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>407 Proxy Authentification Required</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>407 Proxy Authentification Required</h1><img src=\"https://http.cat/407\" style=\"display: block;margin: auto;\" alt=\"407 Proxy Authentification Required\"><p>webserv</p></body></html>"

# define STATUS408 "Request Timeout"
# define HTML408 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>408 Request Timeout</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>408 Request Timeout</h1><img src=\"https://http.cat/408\" style=\"display: block;margin: auto;\" alt=\"408 Request Timeout\"><p>webserv</p></body></html>"

# define STATUS409 "Conflict"
# define HTML409 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>409 Conflict</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>409 Conflict</h1><img src=\"https://http.cat/409\" style=\"display: block;margin: auto;\" alt=\"409 Conflict\"><p>webserv</p></body></html>"

# define STATUS410 "Gone"
# define HTML410 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>410 Gone</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>410 Gone</h1><img src=\"https://http.cat/410\" style=\"display: block;margin: auto;\" alt=\"410 Gone\"><p>webserv</p></body></html>"

# define STATUS411 "Length Required"
# define HTML411 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>411 Length Required</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>411 Length Required</h1><img src=\"https://http.cat/411\" style=\"display: block;margin: auto;\" alt=\"411 Length Required\"><p>webserv</p></body></html>"

# define STATUS412 "Precondition Failed"
# define HTML412 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>412 Precondition Failed</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>412 Precondition Failed</h1><img src=\"https://http.cat/412\" style=\"display: block;margin: auto;\" alt=\"412 Precondition Failed\"><p>webserv</p></body></html>"

# define STATUS413 "Request Entity Too Large"
# define HTML413 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>413 Request Entity Too Large</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>413 Request Entity Too Large</h1><img src=\"https://http.cat/413\" style=\"display: block;margin: auto;\" alt=\"413 Request Entity Too Large\"><p>webserv</p></body></html>"

# define STATUS414 "Request-URI Too Long"
# define HTML414 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>414 Request-URI Too Long</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>414 Request-URI Too Long</h1><img src=\"https://http.cat/414\" style=\"display: block;margin: auto;\" alt=\"414 Request-URI Too Long\"><p>webserv</p></body></html>"

# define STATUS415 "Unsupported Media Type"
# define HTML415 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>415 Unsupported Media Type</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>415 Unsupported Media Type</h1><img src=\"https://http.cat/415\" style=\"display: block;margin: auto;\" alt=\"415 Unsupported Media Type\"><p>webserv</p></body></html>"

# define STATUS416 "Request Range Not Satisfiable"
# define HTML416 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>416 Requested Range Not Satisfiable</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>416 Requested Range Not Satisfiable</h1><img src=\"https://http.cat/416\" style=\"display: block;margin: auto;\" alt=\"416 Requested Range Not Satisfiable\"g><p>webserv</p></body></html>"

# define STATUS417 "Expectation Failed"
# define HTML417 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>417 Expectation Failed</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>417 Expectation Failed</h1><img src=\"https://http.cat/417\" style=\"display: block;margin: auto;\" alt=\"417 Expectation Failed\"g><p>webserv</p></body></html>"

//5XX --> Server error
# define STATUS500 "Internal Server Error"
# define HTML500 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>500 Internal Server Error</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>500 Internal Server Error</h1><img src=\"https://http.cat/500\" style=\"display: block;margin: auto;\" alt=\"500 Internal Server Error\"><p>webserv</p></body></html>"

# define STATUS501 "Not Implemented"
# define HTML501 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>501 Not Implemented</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>501 Not Implemented</h1><img src=\"https://http.cat/501\" style=\"display: block;margin: auto;\" alt=\"501 Not Implemented\"><p>webserv</p></body></html>"

# define STATUS502 "Bad Gateway"
# define HTML502 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>502 Bad Gateway</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>502 Bad Gateway</h1><img src=\"https://http.cat/502\" style=\"display: block;margin: auto;\" alt=\"502 Bad Gateway\"><p>webserv</p></body></html>"

# define STATUS503 "Service Unavailable"
# define HTML503 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>503 Service Unavailable</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>503 Service Unavailable</h1><img src=\"https://http.cat/503\" style=\"display: block;margin: auto;\" alt=\"503 Service Unavailable\"><p>webserv</p></body></html>"

# define STATUS504 "Gateway Timeout"
# define HTML504 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>504 Gateway Timeout</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>504 Gateway Timeout</h1><img src=\"https://http.cat/504\" style=\"display: block;margin: auto;\" alt=\"504 Gateway Timeout\"><p>webserv</p></body></html>"

# define STATUS505 "HTTP Version Not Supported"
# define HTML505 "<html><head><meta name=\"viewport\" content=\"width=device-width, minimum-scale=0.1\"><title>505 HTTP Version Not Supported</title></head><body style=\"background: #0e0e0e; height: 100%;text-align:center;color:white;\"><h1>505 HTTP Version Not Supported</h1><img src=\"https://www.redeszone.net/app/uploads-redeszone.net/2021/10/error-505-01.jpg\" style=\"display: block;margin: auto;\" alt=\"505 HTTP Version Not Supported\"g><p>webserv</p></body></html>"

#endif
