#include "Multimedia.h"
#include <iostream>
#include <string>

Multimedia::Multimedia() : name(""), pathname("") {}

Multimedia::Multimedia(std::string name, std::string pathname) : name(name), pathname(pathname) {}

std::string Multimedia::getName() {
    return name;
}

std::string Multimedia::getPathname() {
    return pathname;
}   

void Multimedia::setName(std::string name) {
    this->name = name;
}

void Multimedia::setPathname(std::string pathname) {
    this->pathname = pathname;
}

void Multimedia::print(std::ostream& s) const {
    s << "Name: " << name << std::endl;
    s << "Pathname: " << pathname << std::endl;
}

void Multimedia::play() const {
    std::cout << "Playing multimedia object" << std::endl;
}


Multimedia::~Multimedia() {}



