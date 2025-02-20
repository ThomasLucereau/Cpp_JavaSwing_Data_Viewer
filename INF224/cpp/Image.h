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
        
        int getWidth() const {
            return width;
        };
        int getHeight() const{
            return height;
        };
        void setWidth(int width) {
            this->width = width;
        };
        void setHeight(int height) {
            this->height = height;
        };
        void print(std::ostream& s) const override {
            
            s << "name = " << name << ", pathname = " << pathname << ", width = " << width << ", height = " << height << std::endl;
        };

        void play() const override {
            std::string command = "imagej " + pathname + " &";
            system(command.data());
        };

        ~Image() {};
};

#endif // IMAGE_H