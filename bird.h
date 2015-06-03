#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "animateSprite.h"

class Bird: public AnimateSprite{
    public:
        enum STATE{
            NORMAL,
            NUM_STATES
        };
        void fly();//missing parameters

};

#endif // BIRD_H_INCLUDED
