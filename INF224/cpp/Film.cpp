#include "Film.h"
#include <iostream>
#include <string>




Film::Film() : durations(nullptr), number_chapters(0) {}

Film::Film(std::string name, std::string pathname,int duration, int *durations, int number_chapters) : Video(name, pathname,duration) {
    this->durations = new int[3];
    for (int i = 0; i < number_chapters;i++){
        this->durations[i] = durations[i];
    }
    this->number_chapters = number_chapters;
}

Film::Film(const Film& from) : Video(from) {
    durations = new int[from.number_chapters];
    for (int i = 0; i < from.number_chapters; i++) {
        durations[i] = from.durations[i];
    }
    number_chapters = from.number_chapters;
}

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

const int *Film::getDurations() const {
    return durations;
}

const int Film::getNumberChapters() const { 
    return number_chapters;
}

void Film::setDurations(const int *durations, int number_chapters) {
    delete [] this->durations;
    this->durations = new int[number_chapters];
    for (int i = 0; i < number_chapters; i++) {
        this->durations[i] = durations[i];
    }
    this->number_chapters = number_chapters;
}

void Film::setNumberChapters(int number_chapters) {
    this->number_chapters = number_chapters;
}

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

Film::~Film() {
    delete [] durations;
}



