//
// main.cpp
// Created on 21/10/2018
#define VERSION_5

// Q5 : le polymorphisme permet de réaliser cette boucle sans prendre en compte le type des objets

// dans le cas du c++ il est nécessaire de déclarer les méthodes print et play comme virtuelles

// le type des éléments du tableau est Multimedia* et non pas Image* ou Video*, c'est à dire des pointeurs 
//vers des objets de type Multimedia. 

// Q7 les classes ou il faut éviter la fuite de mémoire sont les classes qui manipulent des pointeurs.
// dans notre cas, les classes qui manipulent des pointeurs est la classe Film car elle contient des attributs de type pointeur.

// la copie d'objet peut également poser des problèmes si les pointeurs pointent vers le même objet.
// la solution pour cela est de redéfinir le constructeur de copie et l'opérateur d'affectation pour les classes qui manipulent des pointeurs.
// Ainsi la copie est désormais dite "profonde"
// c'est ce que j'ai fait dans la classe Film

// Q8 : le groupe ne doit pas détruire les objets qu'il contient car il ne les a pas créé. Sinon cela
// transgresserai le principe de responsabilité unique. La liste est faite de pointeurs d'objets et non d'objets car cela permet de supprimer les objets
// en appliquant les principes de polymorphisme. On utilise donc des les pointeurs + delete. En Java ce sont 
// les références qui sont utilisées et le garbage collector qui se charge de la suppression des objets.

//Q10 pour éviter qu'autre chose que la classe manager puisse créer des objets de type Multimedia, on peut faire de la classe Multimedia un type incomplet

#include <string>
#include <iostream>
#include <memory>
#include "Manager.h"
#include "Serialization.h"

class Mulimedia;
class Image;
class Video;
class Film;
class Group;

#ifdef VERSION_1
using namespace std;

int main(int argc, const char* argv[])
{
    // check du polymorphisme
    
    Multimedia **table = new Multimedia*[3]; // create a table of multimedia objects
    int count = 0;
    table[count++] = new Image("Image1", "Lenna.png", 1920, 1080);
    table[count++] = new Video("Video1", "video1.mp4", 60);
    table[count++] = new Image("Image2", "Lenna.png", 1920, 1080);

    for (int i = 0; i < count; i++) { 
        table[i]->print(cout);      
        table[i]->play();           
    }


    delete [] table;

}
    
#endif

#ifdef VERSION_2

int main(int argc, const char* argv[]){
    // check de la classe Film

    
    int *durations = new int[3];
    durations[0] = 5;
    durations[1] = 20;
    durations[2] = 30;
    Film *film = new Film("Film1", "film1.mp4", 60, durations, 3);
    film->print(cout);
    printf("\n%p\n", durations);

    delete [] durations;

    film-> print(cout);
}

#endif

#ifdef VERSION_3

int main(int argc, const char* argv[]){
    
    // check de la classe Group

    
    MultimediaPtr Image1(new Image("Image1", "image1.jpg", 1920, 1080));
    MultimediaPtr Video1(new Video("Video1", "video1.mp4", 60));
    MultimediaPtr Image2(new Image("Image2", "image2.jpg", 1920, 1080));
    MultimediaPtr Film1(new Film("Film1", "film1.mp4", 60, new int[3]{5, 20, 30}, 3));
    MultimediaPtr Film2(new Film("Film2", "film2.mp4", 60, new int[3]{5, 20, 30}, 3));
    MultimediaPtr Video2(new Video("Video2", "video2.mp4", 60));

    Group *group1 = new Group("group1");
    Group *group2 = new Group("group2");
    Group *group3 = new Group("group3");
    Group *group4 = new Group("group4");

    group1->push_back(Image1);
    group1->push_back(Video1);
    group1->push_back(Film1);

    group2->push_back(Image2);
    group2->push_back(Video2);
    group2->push_back(Film2);

    group3->push_back(Image1);
    group3->push_back(Film1);
    group3->push_back(Video2);

    group4->push_back(Video1);
    group4->push_back(Image2);
    group4->push_back(Film2);
    
    group1->print(cout);
    group2->print(cout);
    group3->print(cout);
    group4->print(cout);

    

}
#endif

#ifdef VERSION_4

int main(int argc, const char* argv[]){
    // check de la classe Manager

    Manager *manager = new Manager();
    manager->addImage("lenna", "Lenna.png", 1920, 1080);
    manager->addImage("eddy2", "eddy.jpg", 1920, 1080);
    manager->addVideo("video1", "video1.mp4", 60);
    manager->addVideo("video2", "video2.mp4", 60);
    manager->addFilm("film1", "film1.mp4", 60, new int[3]{5, 20, 30}, 3);
    manager->addFilm("film2", "film2.mp4", 60, new int[3]{5, 20, 30}, 3);

    manager->printMultimedia("lenna", cout);
    manager->printMultimedia("video1", cout);
    manager->printMultimedia("film1", cout);

    manager->playMultimedia("lenna");
    manager->playMultimedia("video1");
    manager->playMultimedia("film1");

    std::shared_ptr<Group> group1(new Group("group1"));
    group1->push_back(manager->getMultimedia("lenna"));
    group1->push_back(manager->getMultimedia("video1"));
    group1->push_back(manager->getMultimedia("film1"));

    manager->addGroup(group1);

    manager->printGroup("group1");

    manager->removeMultimedia("lenna");
    manager->removeGroup("group1");

    manager->printMultimedia("lenna", cout);
    manager->printGroup("group1");

    delete manager;
}

#endif

#ifdef VERSION_5

// check de la sérialisation

int main(int argc, const char* argv[]){
    
}

#endif