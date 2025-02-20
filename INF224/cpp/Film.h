#ifndef Film_h
#define Film_h

#include <iostream>
#include <string>
#include "Video.h"


class Film : public Video{

    private:

        int *durations;

        int number_chapters;

    public:

        Film();

        Film(std::string name, std::string pathname, int duration, int *durations, int number_chapters) ;
        
        Film(const Film& from);

        Film& operator=(const Film& from);

        const int *getDurations() const;

        const int getNumberChapters() const;

        void setDurations(const int *durations, int number_chapters) ;

        void setNumberChapters(int number_chapters) ;

        void print(std::ostream& s) const final ;

        ~Film();
};

#endif // Film_h
