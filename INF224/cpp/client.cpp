//
// Client C++ pour communiquer avec un serveur TCP
// eric lecolinet - telecom paristech - 2016/2020
//

#include <iostream>
#include <string> 
#include <algorithm>
#include "ccsocket.h"

static const std::string HOST = "127.0.0.1"; ///< Adresse du serveur
static const int PORT = 3331; ///< Port du serveur

/**
 * @brief Lit une requête depuis le Terminal, envoie cette requête au serveur,
 *        récupère sa réponse et l'affiche sur le Terminal.
 * 
 * Cette fonction bloque si le serveur ne répond pas. L'utilisateur peut entrer
 * des requêtes dans le terminal et recevoir des réponses du serveur.
 * La communication se fait en envoyant une chaîne de caractères et en
 * recevant la réponse du serveur. Le programme termine lorsque l'utilisateur
 * entre "quit".
 * 
 * @return int Retourne 0 en cas de succès, 1 en cas d'échec de connexion,
 *             2 en cas d'échec d'envoi ou de réception de message.
 */
int main() {
  Socket sock; ///< Objet Socket pour la communication réseau
  SocketBuffer sockbuf(sock); ///< Tampon de lecture/écriture pour la communication

  int status = sock.connect(HOST, PORT); ///< Tentative de connexion au serveur

  if (status < 0) {
    switch (status) {
      case Socket::Failed:
        std::cerr << "Client: Couldn't reach host " << HOST << ":" << PORT << std::endl;
        return 1; ///< Retourne 1 en cas d'échec de connexion
      case Socket::UnknownHost:
        std::cerr << "Client: Couldn't find host " << HOST << ":" << PORT << std::endl;
        return 1; ///< Retourne 1 en cas d'erreur de résolution du nom d'hôte
      default:
        std::cerr << "Client: Couldn't connect host " << HOST << ":" << PORT << std::endl;
        return 1; ///< Retourne 1 en cas d'échec général de connexion
    }
  }

  std::cout << "Client connected to " << HOST << ":" << PORT << std::endl;

  while (std::cin) {
    std::cout << "Request: "; ///< Affiche une invite pour la requête de l'utilisateur
    std::string request, response; ///< Variables pour la requête et la réponse

    std::getline(std::cin, request); ///< Lit la requête de l'utilisateur
    if (request == "quit") return 0; ///< Quitte si la requête est "quit"

    // Envoyer la requête au serveur
    if (sockbuf.writeLine(request) < 0) {
      std::cerr << "Client: Couldn't send message" << std::endl;
      return 2; ///< Retourne 2 en cas d'échec d'envoi du message
    }

    // Récupérer le résultat envoyé par le serveur
    if (sockbuf.readLine(response) < 0) {
      std::cerr << "Client: Couldn't receive message" << std::endl;
      return 2; ///< Retourne 2 en cas d'échec de réception du message
    }

    // Le serveur remplace les '\n' par des ';' car '\n' sert à indiquer la
    // fin d'un message entre le client et le serveur.
    // On fait ici la transformation inverse.
    std::replace(response.begin(), response.end(), ';', '\n');

    std::cout << "Response: " << response << std::endl; ///< Affiche la réponse du serveur
  }
}
