//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//



#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "Manager.h"
#include <vector>


const int PORT = 3331;



/* Les commandes envoyées par le client sont différentes entre le c++ et le java.
En l'état actuel des choses il est en effet impossible d'envoyer de mots avec 
une requête en Java. C'est pourquoi deux main sont proposés.
*/
int main(int argc, char* argv[])
{
  Manager *manager = new Manager();

  manager->addImage("lenna", "Lenna.png", 1920, 1080);
  manager->addImage("eddy2", "eddy.jpg", 1920, 1080);

  // cree le TCPServer
  auto* server = 
  new TCPServer( [&](std::string const& request, std::string& response) {

    std::cout << "Request: " << request << std::endl;

    std::vector<std::string> tokens;
    std::istringstream iss(request);
    std::string token;

    while (std::getline(iss, token, ' ')) {
      tokens.push_back(token);
    }

    if (tokens.size() == 0) {
      response = "Error: Empty request";
      return false;
    }

    if (tokens[0] == "print") {
      if (tokens.size() != 2) {
        response = "Error: Usage: print <multimedia_object_name>";
        return false;
      }

      std::ostringstream result;
      manager->printMultimedia(tokens[1], result);
      response = "Printing : " + tokens[1] + " : " + result.str();
      return true;
    }

    if (tokens[0] == "play") {
      if (tokens.size() != 2) {
        response = "Error: Usage: play <multimedia_object_name>";
        return false;
      }

      manager->playMultimedia(tokens[1]);
      response = "Playing : " + tokens[1];
      return true;
    }

    if (tokens[0] == "Opening") {
      response = manager->getMObjects();
      return true;
    }

    return true;
  });


  // lance la boucle infinie du serveur
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}


