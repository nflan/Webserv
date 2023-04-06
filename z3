valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./webserv sources/server.conf2
Can't open file error.html using default error page
Can't open file e using default error page
Server 0:
Server name : webserv.com;
Root : ./site/
Port : 8083
Cliend Body Limit : 2097152
CGI (first = extension, second = root):

ERROR_PAGES (first = status, second = root):
- first = '404' && second = '<html><head><meta name="viewport" content="width=device-width, minimum-scale=0.1"><title>400 Bad Request</title></head><body style="background: #0e0e0e; height: 100%;text-align:center;color:white;"><h1>400 Bad Request</h1><img src="https://http.cat/400" style="display: block;margin: auto;" alt="400 Bad Request"><p>webserv</p></body></html>
'

Server 1:
Server name : webserv2.com;
Root : ./test
Port : 8080
Cliend Body Limit : 1048576
CGI (first = extension, second = root):

ERROR_PAGES (first = status, second = root):

Server 2:
Server name : webserv2;
Root : ./test
Port : 8086
Cliend Body Limit : 1048576
CGI (first = extension, second = root):
- first = '.php' && second = '/usr/bin/php-cgi'
- first = '.py' && second = '/usr/bin/python3'

ERROR_PAGES (first = status, second = root):

Server 3:
Server name : webserv3;
Root : ../
Port : 8084
Cliend Body Limit : 1048576
CGI (first = extension, second = root):

ERROR_PAGES (first = status, second = root):

Request :
DELETE /test HTTP/1.1
Host: localhost:8083
User-Agent: insomnia/2022.7.0
Accept: */*



Méthode : DELETE
Chemin : /test
Type : html
Version : HTTP/1.1
Host : localhost:8083
Connection : 
MIME : */*
Content Type : 
Content Length : 

Body : TE /test HTTP/1.1
Host: localhost:8083
User-Agent: insomnia/2022.7.0
Accept: */*



server_response Default Constructor called

C0 = './site//test'

File deleted successfully: 
server_request Destructor called
server_response Destructor called
