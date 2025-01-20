#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

// Q4 : une méthode virtuelle est une méthode qui peut être redéfinie dans une classe fille
// pour la déclarer, il suffit de rajouter le mot clé "virtual" devant la déclaration de la méthode

// une classe abstraite est une classe qui contient au moins une méthode virtuelle pure
// une classe abstraite ne peut pas être instanciée, c'est donc le cqas de la classe Multimedia

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
