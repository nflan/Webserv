how to config my config file to accepte multiple servers with different hostname 

***************

To configure your web server to accept multiple servers with different hostnames, you need to edit the server configuration file for your web server. Here are the general steps for Apache and Nginx:

Apache:

Open the Apache configuration file, usually located at /etc/httpd/conf/httpd.conf.

Look for the VirtualHost section in the file. This section defines the configuration for each virtual host.

Add a new VirtualHost block for each hostname you want to serve. Here's an example:

php
Copy code
<VirtualHost *:80>
    ServerName example.com
    DocumentRoot /var/www/example.com
</VirtualHost>

<VirtualHost *:80>
    ServerName example2.com
    DocumentRoot /var/www/example2.com
</VirtualHost>
This example sets up two virtual hosts, one for example.com and one for example2.com, each with its own document root directory.

Save the configuration file and restart Apache to apply the changes.

Nginx:

Open the Nginx configuration file, usually located at /etc/nginx/nginx.conf.

Look for the http section in the file. This section defines the main configuration for the web server.

Add a new server block for each hostname you want to serve. Here's an example:

server {
    listen 80;
    server_name example.com;
    root /var/www/example.com;
}

server {
    listen 80;
    server_name example2.com;
    root /var/www/example2.com;
}

This example sets up two server blocks, one for example.com and one for example2.com, each with its own root directory.

Save the configuration file and reload Nginx to apply the changes.

Once you've set up the configuration, you can test it by using curl with the --resolve option to specify the hostname and IP address. For example:

javascript
Copy code
curl --resolve example.com:80:127.0.0.1 http://example.com/
This should return the content of the index.html file in the document root directory for the example.com virtual host. Repeat the command with the other hostname to test the other virtual host.