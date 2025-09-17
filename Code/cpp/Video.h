#ifndef VIDEO_H
#define VIDEO_H


#include <iostream>
#include <string>
#include "Multimedia.h"

class Video : public Multimedia {

    protected:
        int duration = 0;
        
    public:
        Video(): duration(0) {
            this->classname = "Video";
        };

        Video(std::string name, std::string pathname, int duration = 0) : Multimedia(name, pathname), duration(duration) {
            this->classname = "Video";
        };
        
        int getDuration() const {
            return duration;
        };
        void setDuration(int duration) {
            this->duration = duration;
        };
        void print(std::ostream& s) const override { 
            s << "name: " << name << std::endl;
            s << "Duration: " << duration << std::endl;
            s << "pathname: " << pathname << std::endl;
        };

        void play() const override {
            std::string command = "mpv " + pathname + " &";
            system(command.data());
        };

        void write(std::ostream& s) const override {
            Multimedia::write(s);
            s << duration << " ";
        };

        void read(std::istream& s) override {
            Multimedia::read(s);
            s >> duration;
        };

        ~Video() {};
};

#endif // VIDEO_H