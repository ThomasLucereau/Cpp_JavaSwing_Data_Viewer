#include <iostream>
#include <string>
#include "multimedia.h"

class Image : public Multimedia {
    private:
        int width = 2048;
        int height = 1024;
    public:
        Image();
        Image(std::string name, std::string pathname, int width = 2048, int height = 1024);
        int getWidth();
        int getHeight();
        void setWidth(int width) {
            this->width = width;
        };
        void setHeight(int height) {
            this->height = height;
        };
        void print(std::ostream& s) const{
            Multimedia::print(s);
            s << "name: " << name << std::endl;
            s << "Width: " << width << std::endl;
            s << "Height: " << height << std::endl;
            s << "pathname: " << pathname << std::endl;
        };
        void play() const {
            std::string command = "imagej " + pathname + " &";
            system(command.data());
        };
        ~Image();
};