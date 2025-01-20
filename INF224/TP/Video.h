#ifndef VIDEO_H
#define VIDEO_H


#include <iostream>
#include <string>
#include "Multimedia.h"

class Video : public Multimedia {
    private:
        int duration = 0;
        
    public:
        Video(): duration(0) {};
        Video(std::string name, std::string pathname, int duration = 0) : Multimedia(name, pathname), duration(duration) {};
        int getDuration(){
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

        ~Video() {};
};

#endif // VIDEO_H