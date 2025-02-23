#include "Film.h"
#include <iostream>
#include <string>

/**
 * @brief Constructeur par défaut de la classe Film.
 * 
 * Initialise un film avec des durées à nullptr et un nombre de chapitres à 0.
 */
Film::Film() : durations(nullptr), number_chapters(0) {
    this->classname = "Film";
}

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
Film::Film(std::string name, std::string pathname, int duration, int *durations, int number_chapters) : Video(name, pathname, duration) {
    this->durations = new int[3];
    this->classname = "Film";
    for (int i = 0; i < number_chapters; i++) {
        if (durations[i] < 0) {
            throw std::invalid_argument("Error: Duration of chapter cannot be negative");
        }
        this->durations[i] = durations[i];
    }
    this->number_chapters = number_chapters;
}

/**
 * @brief Constructeur de copie pour la classe Film.
 * 
 * Crée une copie d'un autre film.
 * 
 * @param from Film à copier.
 */
Film::Film(const Film& from) : Video(from) {
    durations = new int[from.number_chapters];
    for (int i = 0; i < from.number_chapters; i++) {
        durations[i] = from.durations[i];
    }
    number_chapters = from.number_chapters;
}

/**
 * @brief Surcharge de l'opérateur d'affectation pour la classe Film.
 * 
 * Copie un autre film dans l'objet courant, en libérant d'abord la mémoire utilisée par les durées.
 * 
 * @param from Film à copier.
 * @return Film& Référence à l'objet courant.
 */
Film& Film::operator=(const Film& from) {
    if (this != &from) {
        Video::operator=(from);
        delete [] durations;
        durations = new int[from.number_chapters];
        for (int i = 0; i < from.number_chapters; i++) {
            durations[i] = from.durations[i];
        }
        number_chapters = from.number_chapters;
    }
    return *this;
}

/**
 * @brief Récupère les durées des chapitres du film.
 * 
 * @return const int* Tableau des durées des chapitres.
 */
const int* Film::getDurations() const {
    return durations;
}

/**
 * @brief Récupère le nombre de chapitres du film.
 * 
 * @return const int Nombre de chapitres.
 */
const int Film::getNumberChapters() const {
    return number_chapters;
}

/**
 * @brief Définit les durées des chapitres du film.
 * 
 * Cette fonction alloue un nouveau tableau pour les durées et met à jour le nombre de chapitres.
 * 
 * @param durations Tableau des durées des chapitres.
 * @param number_chapters Nombre de chapitres.
 */
void Film::setDurations(const int *durations, int number_chapters) {
    delete [] this->durations;
    this->durations = new int[number_chapters];
    for (int i = 0; i < number_chapters; i++) {
        this->durations[i] = durations[i];
    }
    this->number_chapters = number_chapters;
}

/**
 * @brief Définit le nombre de chapitres du film.
 * 
 * @param number_chapters Nouveau nombre de chapitres.
 */
void Film::setNumberChapters(int number_chapters) {
    this->number_chapters = number_chapters;
}

/**
 * @brief Affiche les informations du film.
 * 
 * Cette fonction affiche le nom, la durée, le chemin, le nombre de chapitres, et les durées des chapitres.
 * 
 * @param s Flux de sortie pour afficher les informations.
 */
void Film::print(std::ostream& s) const {
    s << "name = " << name ;
    s << ", Duration = " << duration ;
    s << ", Pathname = " << pathname ;;
    s << ", Number of chapters = " << number_chapters ;
    s << ", Durations of chapters = ";
    for (int i = 0; i < number_chapters; i++) {
        s << durations[i] << " ";
    }
    s << std::endl;
    printf("%p", durations);
}

/**
 * @brief Écrit les informations du film dans un flux de sortie.
 * 
 * Cette fonction écrit les informations du film dans un flux de sortie sous un format structuré.
 * 
 * @param s Flux de sortie pour écrire les informations.
 */
void Film::write(std::ostream& s) const {
    Video::write(s);
    s << number_chapters << " ";
    for (int i = 0; i < number_chapters; i++) {
        s << durations[i] << " ";
    }
}

/**
 * @brief Lit les informations du film depuis un flux d'entrée.
 * 
 * Cette fonction lit les informations du film depuis un flux d'entrée et met à jour les attributs de l'objet.
 * 
 * @param s Flux d'entrée pour lire les informations.
 */
void Film::read(std::istream& s) {
    Video::read(s);
    s >> number_chapters;
    delete [] durations;
    durations = new int[number_chapters];
    for (int i = 0; i < number_chapters; i++) {
        s >> durations[i];
    }
}

/**
 * @brief Destructeur de la classe Film.
 * 
 * Libère la mémoire allouée pour les durées des chapitres.
 */
Film::~Film() {
    delete [] durations;
}
