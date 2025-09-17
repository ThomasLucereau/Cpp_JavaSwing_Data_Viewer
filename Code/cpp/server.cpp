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
#include <algorithm>


const int PORT = 3331;



int main(int argc, char* argv[])
{
  Manager *manager = new Manager();

  manager->addImage("lenna", "Lenna.png", 1920, 1080);
  manager->addImage("eddy", "eddy.jpg", 1920, 1080);
  manager->addVideo("shrek", "shrek.mp4", 3);

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
      response = result.str();
      //remove all \n form the string
      response.erase(std::remove(response.begin(), response.end(), '\n'), response.end());
      response = "Printing : " + response;

      std::cout << response << std::endl;
      return true;
    }

    if (tokens[0] == "play") {
      if (tokens.size() != 2) {
        response = "Error: Usage: play <multimedia_object_name>";
        return false;
      }

      manager->playMultimedia(tokens[1]);
      response = "Playing : " + tokens[1] ;
      
      return true;
    }

    if (tokens[0] == "Opening") {
      response = manager->getMObjects();
      return true;
    }

    if (tokens[0] == "remove") {
      if (tokens.size() != 2) {
        response = "Error: Usage: remove <multimedia_object_name>";
        return false;
      }

      manager->removeMultimedia(tokens[1]);
      response = "Removing : " + tokens[1] + " | Remaining objects : " + manager->getMObjects();
      
      return true;
    }

    if (tokens[0] == "add") {


      if (tokens[1] == "video") {
        if (tokens.size() != 4) {
          response = "Error: Usage: add video <multimedia_object_name> <pathname> <duration>";
          return false;
        }

        manager->addVideo(tokens[2], tokens[3], std::stoi(tokens[4]));
        response = "Adding video : " + tokens[2] ;
        return true;
      }

      if (tokens[1] == "image") {
        if (tokens.size() != 5) {
          response = "Error: Usage: add image <multimedia_object_name> <pathname> <width> <height>";
          return false;
        }

        manager->addImage(tokens[2], tokens[3], std::stoi(tokens[4]), std::stoi(tokens[5]));
        response = "Adding image : " + tokens[2] ;
        return true;
      }

      response = "Error: Unknown type";
      return false;
    }


    response = "Error: Unknown command";
    
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


