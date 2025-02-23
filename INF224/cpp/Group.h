#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <string>
#include "Multimedia.h"
#include <list>
#include <memory>

using MultimediaPtr = std::shared_ptr<Multimedia>;

/**
 * @brief Classe représentant un groupe de médias multimédia.
 * 
 * La classe Group hérite de `std::list<MultimediaPtr>` et permet de gérer un groupe de médias
 * (de type `Multimedia`). Elle permet d'ajouter, de supprimer des éléments, et d'afficher les informations
 * relatives au groupe et à ses éléments.
 */
class Group : public std::list<MultimediaPtr> {

    private:
        std::string name; ///< Nom du groupe de médias

    public:
        /**
         * @brief Constructeur de la classe Group.
         * 
         * Initialise un groupe avec un nom.
         * 
         * @param name Nom du groupe.
         */
        Group(std::string name) : name(name) {};

        /**
         * @brief Récupère le nom du groupe.
         * 
         * @return std::string Nom du groupe.
         */
        std::string getGroupName() {
            return name;
        };

        /**
         * @brief Affiche les informations du groupe et de ses éléments multimédia.
         * 
         * Affiche le nom du groupe et appelle la méthode `print` sur chaque élément du groupe.
         * 
         * @param s Flux de sortie pour afficher les informations.
         */
        void print(std::ostream& s) const { 
            s << " \n Group name: " << name << std::endl;
            for (MultimediaPtr multimedia : *this) {
                multimedia->print(s);
            }
            s << "\n" << std::endl;
        };

        /**
         * @brief Ajoute un élément multimédia au groupe.
         * 
         * Cette méthode ajoute un élément de type `MultimediaPtr` au groupe.
         * 
         * @param multimedia L'élément multimédia à ajouter.
         */
        void addMultimedia(MultimediaPtr multimedia) {
            push_back(multimedia);
        };

        /**
         * @brief Supprime un élément multimédia du groupe par son nom.
         * 
         * Cette méthode parcourt le groupe et supprime l'élément dont le nom correspond à celui passé en argument.
         * 
         * @param name Nom de l'élément multimédia à supprimer.
         */
        void removeMultimedia(std::string name) {
            for (MultimediaPtr multimedia : *this) {
                if (multimedia->getName() == name) {
                    remove(multimedia);
                    break;
                }
            }
        };

        /**
         * @brief Destructeur de la classe Group.
         * 
         * Libère la mémoire utilisée par les éléments multimédia du groupe. Affiche également un message indiquant
         * que chaque élément a été supprimé.
         */
        ~Group() {
            print(std::cout << "Group and its multimedia items are deleted" << std::endl);
            
        };
};

#endif // Group_h
