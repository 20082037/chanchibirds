#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "sprite.h"

class Platform: public Sprite{
    public:
        enum STATE{
            NORMAL,
        }
        bool direction;
        float speed;


};

#endif // PLATFORM_H_INCLUDED
