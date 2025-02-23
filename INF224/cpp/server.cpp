/*
 * @file server.cpp
 * @brief TCP Server for handling multimedia requests.
 * @author Eric Lecolinet - Telecom ParisTech - 2016
 */

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "Manager.h"
#include "Serialization.h"
#include <vector>
#include <algorithm>

const int PORT = 3331;

/**
 * @brief Main function to run the TCP server.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments.
 * @return int Exit status.
 */
int main(int argc, char* argv[])
{
  Manager *manager = new Manager();

  manager->addImage("lenna", "Lenna.png", 1920, 1080);
  manager->addImage("eddy", "eddy.jpg", 1920, 1080);
  manager->addVideo("shrek", "shrek.mp4", 3);

  /**
   * @brief Creates the TCP server to handle requests.
   */
  auto* server = 
  new TCPServer( [&](std::string const& request, std::string& response) {

    std::cout << "Request: " << request << std::endl;

    std::vector<std::string> tokens;
    std::istringstream iss(request);
    std::string token;
    
    while (std::getline(iss, token, ' ')) {
      tokens.push_back(token);
    }

    if (tokens.empty()) {
      response = "Error: Empty request";
      return false;
    }

    /**
     * @brief Handles "print" command.
     */
    if (tokens[0] == "print") {
      if (tokens.size() != 2) {
        response = "Error: Usage: print <multimedia_object_name>";
        return false;
      }

      std::ostringstream result;
      manager->printMultimedia(tokens[1], result);
      response = result.str();
      response.erase(std::remove(response.begin(), response.end(), '\n'), response.end());
      response = "Printing : " + response;

      std::cout << response << std::endl;
      return true;
    }

    /**
     * @brief Handles "play" command.
     */
    if (tokens[0] == "play") {
      if (tokens.size() != 2) {
        response = "Error: Usage: play <multimedia_object_name>";
        return false;
      }

      manager->playMultimedia(tokens[1]);
      response = "Playing : " + tokens[1];
      return true;
    }

    /**
     * @brief Handles "Opening" command.
     */
    if (tokens[0] == "Opening") {
      response = manager->getMObjects();
      return true;
    }

    /**
     * @brief Handles "remove" command.
     */
    if (tokens[0] == "remove") {
      if (tokens.size() != 2) {
        response = "Error: Usage: remove <multimedia_object_name>";
        return false;
      }

      manager->removeMultimedia(tokens[1]);
      response = "Removing : " + tokens[1] + " | Remaining objects : " + manager->getMObjects();
      return true;
    }

    /**
     * @brief Handles "add" command for images and videos.
     */
    if (tokens[0] == "add") {
      if (tokens[1] == "video") {
        if (tokens.size() != 4) {
          response = "Error: Usage: add video <multimedia_object_name> <pathname> <duration>";
          return false;
        }
        manager->addVideo(tokens[2], tokens[3], std::stoi(tokens[4]));
        response = "Adding video : " + tokens[2];
        return true;
      }
      if (tokens[1] == "image") {
        if (tokens.size() != 5) {
          response = "Error: Usage: add image <multimedia_object_name> <pathname> <width> <height>";
          return false;
        }
        manager->addImage(tokens[2], tokens[3], std::stoi(tokens[4]), std::stoi(tokens[5]));
        response = "Adding image : " + tokens[2];
        return true;
      }
      response = "Error: Unknown type";
      return false;
    }

    response = "Error: Unknown command";
    return true;
  });

  /**
   * @brief Starts the server loop.
   */
  std::cout << "Starting Server on port " << PORT << std::endl;
  int status = server->run(PORT);

  /**
   * @brief Handles server startup errors.
   */
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}
