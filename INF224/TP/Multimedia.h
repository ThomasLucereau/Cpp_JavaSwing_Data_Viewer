#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <iostream>
#include <string>

class Multimedia
{
protected:
    std::string name;
    std::string pathname;
public:
    Multimedia();

    Multimedia(std::string name, std::string pathname);

    std::string getName();

    std::string getPathname();

    void setName(std::string name);

    void setPathname(std::string pathname);

    virtual void print(std::ostream& s) const;

    virtual void play() const; // play the multimedia object
    
    virtual ~Multimedia();

};



#endif // MULTIMEDIA_H
