//
// main.cpp
// Created on 21/10/2018
//

#include <string>
#include <iostream>
#include "Multimedia.h"
#include "Image.h"
#include "Video.h"


using namespace std;

int main(int argc, const char* argv[])
{
    Multimedia **table = new Multimedia*[3]; // create a table of multimedia objects
    int count = 0;
    table[count++] = new Image("Image1", "image1.jpg", 1920, 1080);
    table[count++] = new Video("Video1", "video1.mp4", 60);
    table[count++] = new Image("Image2", "image2.jpg", 1920, 1080);

    for (int i = 0; i < count; i++) { // le polymorphisme permet de réaliser cette boucle sans prendre en compte le type des objets
        table[i]->print(cout);      // dans le cas du c++ il est nécessaire de déclarer la méthode print comme virtuelle
        table[i]->play();
    }

    delete [] table;

}
