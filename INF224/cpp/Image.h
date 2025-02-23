#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include "Multimedia.h"

/**
 * @brief Classe représentant une image, dérivée de la classe Multimedia.
 * 
 * La classe `Image` hérite de la classe `Multimedia` et ajoute des fonctionnalités spécifiques
 * à la gestion des images, notamment la largeur et la hauteur de l'image. Elle permet de manipuler 
 * les dimensions d'une image, de l'afficher et de la lire/écrire depuis/vers un flux.
 */
class Image : public Multimedia {
    private:
        int width = 2048; ///< Largeur de l'image
        int height = 1024; ///< Hauteur de l'image

    public:
        /**
         * @brief Constructeur par défaut de la classe Image.
         * 
         * Initialise une image avec des dimensions par défaut (0x0).
         */
        Image(): width(0), height(0) {
            this->classname = "Image";
        };

        /**
         * @brief Constructeur de la classe Image avec des paramètres.
         * 
         * Initialise une image avec un nom, un chemin, une largeur et une hauteur.
         * 
         * @param name Nom de l'image.
         * @param pathname Chemin du fichier de l'image.
         * @param width Largeur de l'image (par défaut 2048).
         * @param height Hauteur de l'image (par défaut 1024).
         */
        Image(std::string name, std::string pathname, int width = 2048, int height = 1024) 
            : Multimedia(name, pathname), width(width), height(height) {
            this->classname = "Image";
        };

        /**
         * @brief Récupère la largeur de l'image.
         * 
         * @return int Largeur de l'image.
         */
        int getWidth() const {
            return width;
        };

        /**
         * @brief Récupère la hauteur de l'image.
         * 
         * @return int Hauteur de l'image.
         */
        int getHeight() const {
            return height;
        };

        /**
         * @brief Définit la largeur de l'image.
         * 
         * @param width Nouvelle largeur de l'image.
         */
        void setWidth(int width) {
            this->width = width;
        };

        /**
         * @brief Définit la hauteur de l'image.
         * 
         * @param height Nouvelle hauteur de l'image.
         */
        void setHeight(int height) {
            this->height = height;
        };

        /**
         * @brief Affiche les informations de l'image.
         * 
         * Affiche le nom, le chemin, la largeur et la hauteur de l'image.
         * 
         * @param s Flux de sortie pour afficher les informations.
         */
        void print(std::ostream& s) const override {
            s << "name = " << name << ", pathname = " << pathname 
              << ", width = " << width << ", height = " << height << std::endl;
        };

        /**
         * @brief Ouvre l'image avec un logiciel externe pour la visualiser.
         * 
         * Cette méthode utilise le logiciel `imagej` pour afficher l'image.
         */
        void play() const override {
            std::string command = "imagej " + pathname + " &";
            system(command.data());
        };

        /**
         * @brief Écrit les informations de l'image dans un flux de sortie.
         * 
         * Cette fonction écrit les informations spécifiques de l'image, telles que la largeur et la hauteur,
         * dans un flux de sortie.
         * 
         * @param s Flux de sortie pour écrire les informations.
         */
        void write(std::ostream& s) const override {
            Multimedia::write(s);
            s << width << " " << height << " ";
        };

        /**
         * @brief Lit les informations de l'image depuis un flux d'entrée.
         * 
         * Cette fonction lit les informations spécifiques de l'image, telles que la largeur et la hauteur,
         * depuis un flux d'entrée.
         * 
         * @param s Flux d'entrée pour lire les informations.
         */
        void read(std::istream& s) override {
            Multimedia::read(s);
            s >> width >> height;
        };

        /**
         * @brief Destructeur de la classe Image.
         * 
         * Le destructeur est vide car la gestion de la mémoire est confiée à `Multimedia` et les objets sont
         * automatiquement supprimés à la fin du cycle de vie de l'objet.
         */
        ~Image() {};
};

#endif // IMAGE_H
