#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Multimedia.h"
#include "Image.h"
#include "Video.h"
#include "Film.h"

using MultimediaPtr = std::shared_ptr<Multimedia>;

/**
 * @brief Factory function to create Multimedia objects based on class name.
 * 
 * @param classname The name of the multimedia class to create.
 * @return MultimediaPtr A shared pointer to the created multimedia object.
 */
MultimediaPtr MultimediaFactory(const std::string& classname) {
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

/**
 * @brief Serializes multimedia objects to a file.
 * 
 * @param filename The name of the file to save the serialized data.
 * @param multimedia_objects A map containing multimedia objects to serialize.
 * @return true If serialization is successful.
 * @return false If an error occurs during file operations.
 */
bool serialize(const std::string& filename, const std::map<std::string, MultimediaPtr>& multimedia_objects) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }
    for (const auto& multimedia : multimedia_objects) {
        file << multimedia.second->getClassName() << " ";
        multimedia.second->write(file);
        if (file.fail()) {
            std::cerr << "Error: could not write to file " << filename << std::endl;
            return false;
        }
    }
    
    file.close();
    return true;
}

/**
 * @brief Deserializes multimedia objects from a file.
 * 
 * @param filename The name of the file containing serialized data.
 * @param multimedia_objects A vector to store the deserialized multimedia objects.
 * @return true If deserialization is successful.
 * @return false If an error occurs during file operations or object creation.
 */
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
        MultimediaPtr multimedia = MultimediaFactory(classname);
        if (multimedia == nullptr) {
            std::cerr << "Error: could not create object of class " << classname << std::endl;
            return false;
        }
        multimedia->read(file);
        multimedia_objects.push_back(multimedia);
    }

    file.close();
    return true;
}

/**
 * @brief Overloaded output stream operator for MultimediaPtr serialization.
 * 
 * @param s The output stream.
 * @param multimedia The multimedia object to serialize.
 * @return std::ostream& The updated output stream.
 */
std::ostream& operator<<(std::ostream& s, const MultimediaPtr& multimedia) {
    multimedia->write(s);
    return s;
}

/**
 * @brief Overloaded input stream operator for MultimediaPtr deserialization.
 * 
 * @param s The input stream.
 * @param multimedia The multimedia object to deserialize.
 * @return std::istream& The updated input stream.
 */
std::istream& operator>>(std::istream& s, MultimediaPtr& multimedia) {
    multimedia->read(s);
    return s;
}

#endif // SERIALIZATION_H
