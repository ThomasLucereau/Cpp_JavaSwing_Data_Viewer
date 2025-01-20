//
// main.cpp
// Created on 21/10/2018


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

#include <string>
#include <iostream>
#include "Multimedia.h"
#include "Image.h"
#include "Film.h"


using namespace std;

int main(int argc, const char* argv[])
{
    // check du polymorphisme
    //Multimedia **table = new Multimedia*[3]; // create a table of multimedia objects
    //int count = 0;
    //table[count++] = new Image("Image1", "image1.jpg", 1920, 1080);
    //table[count++] = new Video("Video1", "video1.mp4", 60);
    //table[count++] = new Image("Image2", "image2.jpg", 1920, 1080);

    //for (int i = 0; i < count; i++) { 
    //    table[i]->print(cout);      
    //    table[i]->play();           
    //}

    //delete [] table;

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
