#ifndef Manager_h
#define Manager_h

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "Multimedia.h"
#include "Group.h"
#include "Video.h"
#include "Image.h"
#include "Film.h"

class Manager {
    private:
        std::map<std::string, std::shared_ptr<Multimedia>> multimedia_objects;
        std::map<std::string, std::shared_ptr<Group>> groups;

    public:
    
        Manager(){};

        std::string getMObjects() const {
            std::string multimedia_str;
            for (auto const& multiMO : multimedia_objects){
                multimedia_str.append(multiMO.first + " ,");
            }
            return multimedia_str;
        };

        std::string getGroups() const {
            std::string groups_str;
            for (auto const& group : groups){
                groups_str.append(group.first + " ,");
            }
            return groups_str;
        };

        std::shared_ptr<Multimedia> getMultimedia(std::string name){
            if (multimedia_objects.find(name) == multimedia_objects.end()){
                std::cerr << "Error: Object with name " << name << " does not exist" << std::endl;
                return nullptr;
            }
            return multimedia_objects[name];
        };
        

        void addVideo(std::string name, std::string pathname, int duration){
            if (multimedia_objects.find(name) != multimedia_objects.end()){
                std::cerr << "Error: Object with name " << name << " already exists" << std::endl;
                return;
            }
            multimedia_objects[name] = std::shared_ptr<Video>(new Video(name, pathname, duration));
        };

        void addImage(std::string name, std::string pathname, int width, int height){
            if (multimedia_objects.find(name) != multimedia_objects.end()){
                std::cerr << "Error: Object with name " << name << " already exists" << std::endl;
                return;
            }
            multimedia_objects[name] = std::shared_ptr<Image>(new Image(name, pathname, width, height));
        };

        void addFilm(std::string name, std::string pathname, int duration, int *durations, int number_chapters){
            if (multimedia_objects.find(name) != multimedia_objects.end()){
                std::cerr << "Error: Object with name " << name << " already exists" << std::endl;
                return;
            }
            std::shared_ptr<Film> film(new Film(name, pathname, duration, durations, number_chapters));
            multimedia_objects[name] = film;
        };

        void removeMultimedia(std::string name){
            
            for (auto group : groups){
                group.second->removeMultimedia(name);
            }
            multimedia_objects.erase(name);
            groups.erase(name); // raises no error if name is not in groups
        };

        void playMultimedia(std::string name){
            if (multimedia_objects.find(name) == multimedia_objects.end()){
                std::cerr << "Error: Object with name " << name << " does not exist" << std::endl;
                return;
            }
            multimedia_objects[name]->play();
        };
        void printMultimedia(std::string name, std::ostream& s){
            if (multimedia_objects.find(name) == multimedia_objects.end()){
                std::cerr << "Error: Object with name " << name << " does not exist" << std::endl;
                return;
            }
            multimedia_objects[name]->print(s);
        };

        void addGroup(std::shared_ptr<Group> group){
            if (groups.find(group->getGroupName()) != groups.end()){
                std::cerr << "Error: Group with name " << group->getGroupName() << " already exists" << std::endl;
                return;
            }
            groups[group->getGroupName()] = group;
        };

        void removeGroup(std::string name){
            groups.erase(name);
        };

        void printGroup(std::string name){
            if (groups.find(name) == groups.end()){
                std::cerr << "Error: Group with name " << name << " does not exist" << std::endl;
                return;
            }
            groups[name]->print(std::cout);
        };
        
        ~Manager();
};


#endif // Manager_h