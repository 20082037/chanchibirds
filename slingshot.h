#ifndef SLINGSHOT_H_INCLUDED
#define SLINGSHOT_H_INCLUDED

#include "animateSprite.h"
#include "bird.h"
class Slingshot: public AnimateSprite{
    public:
        enum STATE{
            ANGLE1,
            ANGLE2,
            ANGLE3,
            ANGLE4,
            ANGLE5,
            NUM_STATES
        }
        list<Bird*> birds;
        void throwBird();


};

#endif // SLINGSHOT_H_INCLUDED
