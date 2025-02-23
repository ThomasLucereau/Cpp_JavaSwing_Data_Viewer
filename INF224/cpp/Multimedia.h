#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

/**
 * @file Multimedia.h
 * @brief Déclaration de la classe Multimedia.
 * 
 * Ce fichier contient la déclaration de la classe abstraite `Multimedia`, qui sert de base pour 
 * d'autres objets multimédia comme les images, vidéos, et films. Cette classe gère les propriétés 
 * communes de ces objets, telles que le nom, le chemin d'accès et permet de jouer ou d'afficher 
 * des objets multimédia de manière polymorphique.
 * 
 * @note Ce fichier définit également des méthodes virtuelles qui peuvent être redéfinies dans 
 *       les classes dérivées.
 */

#include <iostream>
#include <string>

/**
 * @class Multimedia
 * @brief Classe de base abstraite pour les objets multimédia.
 * 
 * La classe Multimedia fournit des méthodes communes pour gérer des objets multimédia 
 * comme les images, vidéos, ou films. Les classes dérivées doivent implémenter des comportements
 * spécifiques, notamment pour la lecture et l'affichage des objets multimédia.
 * 
 * @note Une classe abstraite, contenant des méthodes virtuelles pures, ne peut pas être instanciée.
 */
class Multimedia
{
protected:
    std::string name; /**< Nom de l'objet multimédia */
    std::string pathname; /**< Chemin d'accès de l'objet multimédia */
    std::string classname = "Multimedia"; /**< Nom de la classe */

public:
    /**
     * @brief Constructeur par défaut de la classe Multimedia.
     * 
     * Initialise les attributs `name` et `pathname` à des chaînes vides.
     */
    Multimedia();

    /**
     * @brief Constructeur de la classe Multimedia.
     * 
     * Initialise un objet `Multimedia` avec un nom et un chemin spécifiés.
     * 
     * @param name Le nom de l'objet multimédia.
     * @param pathname Le chemin d'accès de l'objet multimédia.
     */
    Multimedia(std::string name, std::string pathname);

    /**
     * @brief Récupère le nom de l'objet multimédia.
     * 
     * @return Le nom de l'objet multimédia.
     */
    std::string getName() const;

    /**
     * @brief Récupère le chemin de l'objet multimédia.
     * 
     * @return Le chemin d'accès de l'objet multimédia.
     */
    std::string getPathname() const;

    /**
     * @brief Définit le nom de l'objet multimédia.
     * 
     * @param name Le nouveau nom de l'objet multimédia.
     */
    void setName(std::string name);

    /**
     * @brief Définit le chemin de l'objet multimédia.
     * 
     * @param pathname Le nouveau chemin d'accès de l'objet multimédia.
     */
    void setPathname(std::string pathname);

    /**
     * @brief Affiche les informations de l'objet multimédia.
     * 
     * Cette méthode est virtuelle et peut être redéfinie dans les classes dérivées pour une gestion spécifique.
     * Elle affiche les informations de l'objet multimédia sur un flux de sortie.
     * 
     * @param s Le flux de sortie où afficher les informations de l'objet.
     */
    virtual void print(std::ostream& s) const;

    /**
     * @brief Joue l'objet multimédia.
     * 
     * Affiche un message par défaut "Playing multimedia object". Cette méthode peut être redéfinie
     * dans les classes dérivées pour implémenter un comportement spécifique.
     */
    virtual void play() const; /**< Comportement par défaut pour jouer un objet multimédia. */

    /**
     * @brief Récupère le nom de la classe de l'objet.
     * 
     * @return Le nom de la classe de l'objet (toujours "Multimedia" pour la classe de base).
     */
    const std::string getClassName() const;

    /**
     * @brief Sérialise les informations de l'objet multimédia.
     * 
     * Écrit les attributs `name` et `pathname` de l'objet dans un flux de sortie.
     * 
     * @param s Le flux de sortie où écrire les informations de l'objet.
     */
    virtual void write(std::ostream& s) const;

    /**
     * @brief Désérialise les informations de l'objet multimédia.
     * 
     * Lit les attributs `name` et `pathname` de l'objet à partir d'un flux d'entrée.
     * 
     * @param s Le flux d'entrée depuis lequel lire les informations de l'objet.
     */
    virtual void read(std::istream& s);

    /**
     * @brief Surcharge de l'opérateur << pour sérialiser un objet Multimedia.
     * 
     * Permet d'écrire un objet `Multimedia` dans un fichier de sortie.
     * 
     * @param s Le flux de sortie dans lequel l'objet est écrit.
     * @return Le flux de sortie avec l'objet écrit.
     */
    std::ofstream& operator<<(std::ofstream& s);

    /**
     * @brief Surcharge de l'opérateur >> pour désérialiser un objet Multimedia.
     * 
     * Permet de lire un objet `Multimedia` depuis un fichier d'entrée.
     * 
     * @param s Le flux d'entrée à partir duquel l'objet est lu.
     * @return Le flux d'entrée avec l'objet lu.
     */
    std::ifstream& operator>>(std::ifstream& s);

    /**
     * @brief Destructeur de la classe Multimedia.
     * 
     * Libère toutes les ressources associées à l'objet multimédia.
     */
    virtual ~Multimedia();

};

#endif // MULTIMEDIA_H
