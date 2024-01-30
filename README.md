**Webserv - 42 school project**
---
The goal of this project is to implement a webserver using C++.

```Usage
make && ./webserv [+ configuration file path]
```

Example:

- make && ./webserv conf/default.conf
- access website (in the "site" directory) by going on localhost:8083.
- you can try to upload files / download them
- use Python CGI
- use PHP CGI
- use get / post CGI
- you can also kick this sheep by clicking on it


---
**Implemented configuration file directives (follows the nginx standard):**
-
listen: address:port
-> ex: " 127.0.0.1:8080; "

server_name
-> ex: " server_name default; "

index
-> ex: " index path.html path_two.html path_three.html "

autoindex
-> ex: " autoindex on; "

root
-> ex: " root ./www/default; "

client_body_buffer_size
-> ex: "client_body_buffer_size 200M;"

rewrite (redirection for temporary or permanent for permanent redirection)
-> ex: " rewrite /path_to_rewrite redirection; " or " rewrite /path_to_rewrite permanent; "

upload_pass
-> ex: " upload_pass /tmp/path_to_upload; "

location
-> ex: " location /form {
root ./www/form;
index index.php;
cgi .php /usr/lib/cgi-bin/php;
} "

---
**Other implemented directives:**
-
error_page: set a page returned on given error response from server
-> ex: " error_page 404 ./404_template.html 403 ./403_template.html; "

allow_method: allow only the stated method for http requests
-> ex: "allow_method GET POST;"

cgi [cgi + extension + path]: set path to cgi depending on chosen extensions
-> ex: " cgi .php /usr/lib/cgi-bin/php .py /usr/lib/cgi-bin/flask; "

limit_upload: limit uploads on server
-> ex: " limit_upload; "

---
**Inheritance:**
-
All directives in the configuration files use inheritance, meaning that the directive will also apply to the sublocations of the configuration file

An example can be found in conf/default.conf

---
**Theory**
-
- From the select, poll and epoll functions allowed, epoll has been implemented as it uses a kernel queue for the sockets, making it more performant

- The documentation used for the project: rfc 9110 (update of rfc 7230, 7231, 7232, 7233, 7234 and 7235), nginx configuration guidelines

- Telnet, curl, siege and vegeta were used for testing the server
