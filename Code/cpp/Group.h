#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <string>
#include "Multimedia.h"
#include <list>
#include <memory>

using MultimediaPtr = std::shared_ptr<Multimedia>;


class Group : public std::list<MultimediaPtr> {

    private:

        std::string name;

    public:

        Group(std::string name) : name(name) {};

        std::string getGroupName() {
            return name;
        };

        void print(std::ostream& s) const { 
            s << " \n Group name: " << name << std::endl;
            for (MultimediaPtr multimedia : *this) {
                multimedia->print(s);
            }
            s << "\n" << std::endl;
        };

        void addMultimedia(MultimediaPtr multimedia) {
            push_back(multimedia);
        };

        void removeMultimedia(std::string name) {
            for (MultimediaPtr multimedia : *this) {
                if (multimedia->getName() == name) {
                    remove(multimedia);
                    break;
                }
            }
        };

        ~Group() {
            for (MultimediaPtr multimedia : *this) {
                delete &multimedia;
                print(std::cout << "Multimedia deleted" << std::endl);
            }
        };
};


#endif // Group_h