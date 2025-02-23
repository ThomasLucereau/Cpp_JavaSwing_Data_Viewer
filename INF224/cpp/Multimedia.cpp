#include "Multimedia.h"
#include <iostream>
#include <string>

/**
 * @brief Constructeur par défaut de la classe Multimedia.
 * Initialise les attributs `name` et `pathname` à des valeurs vides.
 */
Multimedia::Multimedia() : name(""), pathname("") {}

/**
 * @brief Constructeur de la classe Multimedia.
 * Initialise les attributs `name` et `pathname` avec les valeurs spécifiées.
 * 
 * @param name Le nom du fichier multimédia.
 * @param pathname Le chemin du fichier multimédia.
 */
Multimedia::Multimedia(std::string name, std::string pathname) : name(name), pathname(pathname) {}

/**
 * @brief Récupère le nom du fichier multimédia.
 * 
 * @return Le nom du fichier multimédia.
 */
std::string Multimedia::getName() const {
    return name;
}

/**
 * @brief Récupère le chemin du fichier multimédia.
 * 
 * @return Le chemin du fichier multimédia.
 */
std::string Multimedia::getPathname() const {
    return pathname;
}

/**
 * @brief Modifie le nom du fichier multimédia.
 * 
 * @param name Le nouveau nom du fichier multimédia.
 */
void Multimedia::setName(std::string name)  {
    this->name = name;
}

/**
 * @brief Modifie le chemin du fichier multimédia.
 * 
 * @param pathname Le nouveau chemin du fichier multimédia.
 */
void Multimedia::setPathname(std::string pathname) {
    this->pathname = pathname;
}

/**
 * @brief Affiche les informations du fichier multimédia.
 * Affiche le nom et le chemin du fichier multimédia sur le flux de sortie.
 * 
 * @param s Le flux de sortie sur lequel afficher les informations.
 */
void Multimedia::print(std::ostream& s) const {
    s << "Name: " << name << std::endl;
    s << "Pathname: " << pathname << std::endl;
}

/**
 * @brief Joue l'objet multimédia.
 * Affiche un message indiquant que l'objet multimédia est en train de jouer.
 */
void Multimedia::play() const {
    std::cout << "Playing multimedia object" << std::endl;
}

/**
 * @brief Récupère le nom de la classe de l'objet.
 * 
 * @return Le nom de la classe de l'objet.
 */
const std::string Multimedia::getClassName() const {
    return classname;
}

/**
 * @brief Sérialise les informations de l'objet multimédia.
 * Écrit le nom et le chemin du fichier multimédia sur le flux de sortie.
 * 
 * @param s Le flux de sortie où écrire les informations.
 */
void Multimedia::write(std::ostream& s) const {
    s << name << " " << pathname << " ";
}

/**
 * @brief Désérialise les informations de l'objet multimédia.
 * Lit le nom et le chemin du fichier multimédia à partir du flux d'entrée.
 * 
 * @param s Le flux d'entrée à partir duquel lire les informations.
 */
void Multimedia::read(std::istream& s) {
    s >> name >> pathname;
}

/**
 * @brief Destructeur de la classe Multimedia.
 * Libère les ressources associées à l'objet (aucune ressource dynamique dans ce cas).
 */
Multimedia::~Multimedia() {}
