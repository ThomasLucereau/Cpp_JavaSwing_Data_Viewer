#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <string>
#include "Multimedia.h"
#include <list>


class Group : public std::list<Multimedia*> {

    private:
        std::string name;

    public:

        Group(std::string name) : name(name) {};

        std::string getGroupName() {
            return name;
        };

        void print(std::ostream& s) const {
            s << "Group name: " << name << std::endl;
            for (Multimedia* multimedia : *this) {
                multimedia->print(s);
            }
        };

        ~Group() {
            for (Multimedia* multimedia : *this) {
                delete multimedia;
            }
        };
};


#endif // Group_h