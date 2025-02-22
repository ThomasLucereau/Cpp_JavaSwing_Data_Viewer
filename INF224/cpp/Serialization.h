#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Multimedia.h"
#include "Image.h"
#include "Video.h"
#include "Film.h"

using MultimediaPtr = std::shared_ptr<Multimedia>;

bool serialize(const std::string& filename, const std::vector<MultimediaPtr>& multimedia_objects) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }
    for (const auto& multimedia : multimedia_objects) {
        file << multimedia->getClassName() << " ";
        multimedia->write(file);
        if (file.fail()) {
            std::cerr << "Error: could not write to file " << filename << std::endl;
            return false;
        }
    }
    return true;
}

bool deserialize(const std::string& filename, std::vector<MultimediaPtr>& multimedia_objects) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }

    while (file) {
        std::string classname;
        getline(file, classname, ' ');
        if (classname.empty()) {
            break;
        }
        MultimediaPtr multimedia = MultimediaFactoy(classname);
        if (multimedia == nullptr) {
            std::cerr << "Error: could not create object of class " << classname << std::endl;
            return false;
        }
        multimedia->read(file);
        multimedia_objects.push_back(multimedia);

    }
    return true;
}

MultimediaPtr MultimediaFactoy(const std::string& classname) {
    if (classname == "Image") {
        return std::shared_ptr<Image>(new Image());
    } else if (classname == "Video") {
        return std::shared_ptr<Video>(new Video());
    } else if (classname == "Film") {
        return std::shared_ptr<Film>(new Film());
    } else {
        std::cerr << "Error: unknown class " << classname << std::endl;
        return nullptr;
    }
}

// création d'opérateurs de sérialisation/désérialisation pour les MultimediaPtr

std::ostream& operator<<(std::ostream& s, const MultimediaPtr& multimedia) {
    multimedia->write(s);
    return s;
}

std::istream& operator>>(std::istream& s, MultimediaPtr& multimedia) {
    multimedia->read(s);
    return s;
}

#endif // SERIALIZATION_H