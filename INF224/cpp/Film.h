#ifndef Film_h
#define Film_h

#include <iostream>
#include <string>
#include "Video.h"

/**
 * @brief Classe représentant un film, dérivée de la classe Video.
 * 
 * La classe Film hérite de la classe Video et ajoute des fonctionnalités spécifiques
 * à la gestion des chapitres et de leurs durées. Elle permet de manipuler les durées des chapitres
 * et de gérer l'affichage et la lecture des informations associées à un film.
 */
class Film : public Video {

    private:
        int *durations; ///< Tableau des durées des chapitres du film
        int number_chapters; ///< Nombre de chapitres dans le film

    public:
        /**
         * @brief Constructeur par défaut de la classe Film.
         * 
         * Initialise un film avec des durées à nullptr et un nombre de chapitres à 0.
         */
        Film();

        /**
         * @brief Constructeur de la classe Film avec des paramètres.
         * 
         * Initialise un film avec un nom, un chemin, une durée, des durées de chapitres et un nombre de chapitres.
         * 
         * @param name Nom du film.
         * @param pathname Chemin du fichier du film.
         * @param duration Durée totale du film.
         * @param durations Tableau des durées des chapitres du film.
         * @param number_chapters Nombre de chapitres dans le film.
         * @throws std::invalid_argument Si une durée de chapitre est négative.
         */
        Film(std::string name, std::string pathname, int duration, int *durations, int number_chapters);

        /**
         * @brief Constructeur de copie pour la classe Film.
         * 
         * Crée une copie d'un autre film.
         * 
         * @param from Film à copier.
         */
        Film(const Film& from);

        /**
         * @brief Surcharge de l'opérateur d'affectation pour la classe Film.
         * 
         * Copie un autre film dans l'objet courant, en libérant d'abord la mémoire utilisée par les durées.
         * 
         * @param from Film à copier.
         * @return Film& Référence à l'objet courant.
         */
        Film& operator=(const Film& from);

        /**
         * @brief Récupère les durées des chapitres du film.
         * 
         * @return const int* Tableau des durées des chapitres.
         */
        const int* getDurations() const;

        /**
         * @brief Récupère le nombre de chapitres du film.
         * 
         * @return const int Nombre de chapitres.
         */
        const int getNumberChapters() const;

        /**
         * @brief Définit les durées des chapitres du film.
         * 
         * Cette fonction alloue un nouveau tableau pour les durées et met à jour le nombre de chapitres.
         * 
         * @param durations Tableau des durées des chapitres.
         * @param number_chapters Nombre de chapitres.
         */
        void setDurations(const int *durations, int number_chapters);

        /**
         * @brief Définit le nombre de chapitres du film.
         * 
         * @param number_chapters Nouveau nombre de chapitres.
         */
        void setNumberChapters(int number_chapters);

        /**
         * @brief Affiche les informations du film.
         * 
         * Cette fonction affiche le nom, la durée, le chemin, le nombre de chapitres, et les durées des chapitres.
         * 
         * @param s Flux de sortie pour afficher les informations.
         */
        void print(std::ostream& s) const final;

        /**
         * @brief Écrit les informations du film dans un flux de sortie.
         * 
         * Cette fonction écrit les informations du film dans un flux de sortie sous un format structuré.
         * 
         * @param s Flux de sortie pour écrire les informations.
         */
        void write(std::ostream& s) const final;

        /**
         * @brief Lit les informations du film depuis un flux d'entrée.
         * 
         * Cette fonction lit les informations du film depuis un flux d'entrée et met à jour les attributs de l'objet.
         * 
         * @param s Flux d'entrée pour lire les informations.
         */
        void read(std::istream& s) final;

        /**
         * @brief Destructeur de la classe Film.
         * 
         * Libère la mémoire allouée pour les durées des chapitres.
         */
        ~Film();
};

#endif // Film_h
