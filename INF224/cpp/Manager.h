#ifndef Manager_h
#define Manager_h

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <stdexcept>  // pour les exceptions
#include "Multimedia.h"
#include "Group.h"
#include "Video.h"
#include "Image.h"
#include "Film.h"

/**
 * @class Manager
 * @brief Gestionnaire de médias multimédia et de groupes.
 * 
 * La classe Manager permet de gérer les objets multimédia et les groupes. Elle fournit des fonctions pour
 * ajouter, supprimer et manipuler ces objets. Elle traite les erreurs critiques via des exceptions et 
 * les erreurs moins graves avec des messages d'erreur.
 */
class Manager {
    private:
        std::map<std::string, std::shared_ptr<Multimedia>> multimedia_objects;  /**< Liste des objets multimédia */
        std::map<std::string, std::shared_ptr<Group>> groups;  /**< Liste des groupes */

    public:
    
        Manager(){};

        /**
         * @brief Récupère tous les objets multimédia enregistrés sous forme de chaîne de caractères.
         * @return Une chaîne de caractères représentant les noms des objets multimédia.
         */
        std::string getMObjects() const {
            std::string multimedia_str;
            for (auto const& multiMO : multimedia_objects){
                multimedia_str.append(multiMO.first + " ,");
            }
            return multimedia_str;
        };

        /**
         * @brief Récupère tous les groupes enregistrés sous forme de chaîne de caractères.
         * @return Une chaîne de caractères représentant les noms des groupes.
         */
        std::string getGroups() const {
            std::string groups_str;
            for (auto const& group : groups){
                groups_str.append(group.first + " ,");
            }
            return groups_str;
        };

        /**
         * @brief Récupère un objet multimédia par son nom.
         * @param name Le nom de l'objet multimédia.
         * @return Un pointeur partagé vers l'objet multimédia, ou lance une exception si non trouvé.
         * @throws std::runtime_error Si l'objet n'existe pas.
         */
        std::shared_ptr<Multimedia> getMultimedia(std::string name){
            if (multimedia_objects.find(name) == multimedia_objects.end()){
                throw std::runtime_error("Error: Object with name " + name + " does not exist");
            }
            return multimedia_objects[name];
        };
        

        /**
         * @brief Ajoute un objet Video.
         * @param name Le nom de la vidéo.
         * @param pathname Le chemin d'accès à la vidéo.
         * @param duration La durée de la vidéo.
         * @throws std::runtime_error Si un objet avec le même nom existe déjà.
         */
        void addVideo(std::string name, std::string pathname, int duration){
            if (multimedia_objects.find(name) != multimedia_objects.end()){
                throw std::runtime_error("Error: Object with name " + name + " already exists");
            }
            multimedia_objects[name] = std::shared_ptr<Video>(new Video(name, pathname, duration));
        };

        /**
         * @brief Ajoute un objet Image.
         * @param name Le nom de l'image.
         * @param pathname Le chemin d'accès à l'image.
         * @param width La largeur de l'image.
         * @param height La hauteur de l'image.
         * @throws std::runtime_error Si un objet avec le même nom existe déjà.
         */
        void addImage(std::string name, std::string pathname, int width, int height){
            if (multimedia_objects.find(name) != multimedia_objects.end()){
                throw std::runtime_error("Error: Object with name " + name + " already exists");
            }
            multimedia_objects[name] = std::shared_ptr<Image>(new Image(name, pathname, width, height));
        };

        /**
         * @brief Ajoute un objet Film.
         * @param name Le nom du film.
         * @param pathname Le chemin d'accès au film.
         * @param duration La durée du film.
         * @param durations Tableau des durées des chapitres du film.
         * @param number_chapters Le nombre de chapitres.
         * @throws std::runtime_error Si un objet avec le même nom existe déjà ou si la taille du tableau de durées est invalide.
         */
        void addFilm(std::string name, std::string pathname, int duration, int *durations, int number_chapters){
            if (multimedia_objects.find(name) != multimedia_objects.end()){
                throw std::runtime_error("Error: Object with name " + name + " already exists");
            }
            if (number_chapters <= 0 || durations == nullptr) {
                throw std::runtime_error("Error: Invalid durations array or number of chapters");
            }
            std::shared_ptr<Film> film(new Film(name, pathname, duration, durations, number_chapters));
            multimedia_objects[name] = film;
        };

        /**
         * @brief Supprime un objet multimédia par son nom.
         * @param name Le nom de l'objet multimédia à supprimer.
         * @throws std::runtime_error Si l'objet n'existe pas.
         */
        void removeMultimedia(std::string name){
            if (multimedia_objects.find(name) == multimedia_objects.end()){
                throw std::runtime_error("Error: Object with name " + name + " does not exist");
            }

            for (auto group : groups){
                group.second->removeMultimedia(name);
            }
            multimedia_objects.erase(name);
            groups.erase(name); // raises no error if name is not in groups
        };

        /**
         * @brief Joue un objet multimédia.
         * @param name Le nom de l'objet multimédia à jouer.
         * @throws std::runtime_error Si l'objet n'existe pas.
         */
        void playMultimedia(std::string name){
            if (multimedia_objects.find(name) == multimedia_objects.end()){
                throw std::runtime_error("Error: Object with name " + name + " does not exist");
            }
            multimedia_objects[name]->play();
        };

        /**
         * @brief Imprime un objet multimédia.
         * @param name Le nom de l'objet multimédia à imprimer.
         * @param s Le flux de sortie.
         * @throws std::runtime_error Si l'objet n'existe pas.
         */
        void printMultimedia(std::string name, std::ostream& s){
            if (multimedia_objects.find(name) == multimedia_objects.end()){
                throw std::runtime_error("Error: Object with name " + name + " does not exist");
            }
            multimedia_objects[name]->print(s);
        };

        /**
         * @brief Ajoute un groupe.
         * @param group Le groupe à ajouter.
         * @throws std::runtime_error Si un groupe avec le même nom existe déjà.
         */
        void addGroup(std::shared_ptr<Group> group){
            if (groups.find(group->getGroupName()) != groups.end()){
                throw std::runtime_error("Error: Group with name " + group->getGroupName() + " already exists");
            }
            groups[group->getGroupName()] = group;
        };

        /**
         * @brief Supprime un groupe.
         * @param name Le nom du groupe à supprimer.
         * @throws std::runtime_error Si le groupe n'existe pas.
         */
        void removeGroup(std::string name){
            if (groups.find(name) == groups.end()){
                throw std::runtime_error("Error: Group with name " + name + " does not exist");
            }
            groups.erase(name);
        };

        /**
         * @brief Imprime un groupe.
         * @param name Le nom du groupe à imprimer.
         * @throws std::runtime_error Si le groupe n'existe pas.
         */
        void printGroup(std::string name){
            if (groups.find(name) == groups.end()){
                throw std::runtime_error("Error: Group with name " + name + " does not exist");
            }
            groups[name]->print(std::cout);
        };
        
        ~Manager();
};

#endif // Manager_h
