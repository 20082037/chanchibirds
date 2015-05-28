#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "sprite.h"

class Bird: public Sprite{
    public:
        enum STATE{
            NORMAL,
            HIT
        };

};

#endif // BIRD_H_INCLUDED
