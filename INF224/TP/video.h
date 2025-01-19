#include <iostream>
#include <string>
#include "multimedia.h"

class Video : public Multimedia {
    private:
        int duration = 0;
        
    public:
        Video();
        Video(std::string name, std::string pathname, int duration = 0) : Multimedia(name, pathname), duration(duration) {};
        int getDuration();
        void setDuration(int duration) {
            this->duration = duration;
        };
        void print(std::ostream& s) const{
            Multimedia::print(s);
            s << "name: " << name << std::endl;
            s << "Duration: " << duration << std::endl;
            s << "pathname: " << pathname << std::endl;
        };

        void play() const {
            std::string command = "mpv " + pathname + " &";
            system(command.data());
        };

        ~Video();
};