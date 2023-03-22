/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_response.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:09:26 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/22 12:30:55 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP

#include <iostream>
#include <string>
#include <sstream>

class server_response
{
	private:
	std::string	_ServerResponse;
	std::string	_body;
	int			_status_code;
	
	public:
	server_response();
	server_response(const std::string& body, int status_code);
	server_response(server_response const &obj);
	~server_response();
	server_response &operator=(server_response const &obj);

  // Définition de la méthode pour générer une réponse GET
	void generate_get_response(const std::string& request_uri) {
		// Code ici pour traiter la requête GET
	}

	// Définition de la méthode pour générer une réponse POST
	void generate_post_response(const std::string& request_uri, const std::string& data) {
		// Code ici pour traiter la requête POST
	}

	// Définition de la méthode pour générer une réponse DELETE
	void generate_delete_response(const std::string& request_uri) {
		// Code ici pour traiter la requête DELETE
	}

	// Définition de la méthode pour obtenir la réponse _ServerResponse
	std::string get_body() const { return _body; }

	// Définition de la méthode pour obtenir le corps de la réponse
	std::string get_body() const { return _body; }

	// Définition de la méthode pour obtenir le code d'état de la réponse
	int get_status_code() const { return _status_code; }

	// Fonction pour envoyer la réponse au client
    void send_response_to_client(const std::string& response) {
        // Code ici pour envoyer la réponse au client
    }
};

#endif

/*
class server_answer {
public:
	// Constructeurs, destructeur et autres fonctions membres ici
		
	// Définition de la méthode pour générer une réponse POST
	void generate_post_response(const std::string& request_uri, const std::string& data) {
		// Code ici pour traiter la requête POST
		
		// Par exemple, on pourrait simplement renvoyer un message de confirmation avec les données reçues
		std::string response_body = "Données reçues : " + data;
		
		// Ensuite, on prépare et envoie la réponse
		std::ostringstream response_stream;
		response_stream << "HTTP/1.1 200 OK\r\n"
						<< "Content-Type: text/plain\r\n"
						<< "Content-Length: " << response_body.length() << "\r\n"
						<< "\r\n"
						<< response_body;
		std::string response = response_stream.str();
		send_response_to_client(response);
	}

private:
	// Fonction pour envoyer la réponse au client (implémentation non fournie dans cet exemple)
    void send_response_to_client(const std::string& response) {
        // Code ici pour envoyer la réponse au client
    }
};

#include <iostream>
#include <string>

class server_answer {
public:
    // Constructeur par défaut
    server_answer() {}

    // Destructeur par défaut
    ~server_answer() {}

    // Définition de la méthode pour générer une réponse POST
    void generate_post_response(const std::string& request_uri, const std::string& data) {
        // Code ici pour traiter la requête POST
        // ...
        // exemple : renvoie une réponse 201 Created avec le contenu envoyé
        response_code = "201 Created";
        response_body = data;
        content_type = "text/plain";
    }

    // Autres méthodes pour générer des réponses pour GET, DELETE, etc.

    // Méthode pour envoyer la réponse au client
    void send_response_to_client() {
        // Envoi de la ligne de statut
        std::cout << "HTTP/1.1 " << response_code << "\r\n";

        // Envoi des en-têtes de réponse
        std::cout << "Content-Type: " << content_type << "\r\n";
        std::cout << "Content-Length: " << response_body.length() << "\r\n";

        // Envoi de la ligne vide pour séparer les en-têtes et le corps de la réponse
        std::cout << "\r\n";

        // Envoi du corps de la réponse
        std::cout << response_body;
    }

private:
    std::string response_code;
    std::string response_body;
    std::string content_type;
};

int main() {
    // Exemple d'utilisation
    server_answer answer;
    answer.generate_post_response("uri", "Contenu envoyé dans la requête POST");
    answer.send_response_to_client();

    return 0;
}
*/
