#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include "Multimedia.h"

class Image : public Multimedia {
    private:
        int width = 2048;
        int height = 1024;
    public:
        Image(): width(0),height(0) {};
        Image(std::string name, std::string pathname, int width = 2048, int height = 1024) : Multimedia(name, pathname), width(width), height(height) {};
        int getWidth(){
            return width;
        };
        int getHeight(){
            return height;
        };
        void setWidth(int width) {
            this->width = width;
        };
        void setHeight(int height) {
            this->height = height;
        };
        void print(std::ostream& s) const override {
            
            s << "name: " << name << std::endl;
            s << "Width: " << width << std::endl;
            s << "Height: " << height << std::endl;
            s << "pathname: " << pathname << std::endl;
        };

        void play() const override {
            std::string command = "imagej " + pathname + " &";
            system(command.data());
        };

        ~Image() {};
};

#endif // IMAGE_H