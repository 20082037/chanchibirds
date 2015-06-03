#ifndef PIG_H_INCLUDED
#define PIG_H_INCLUDED

#include "animateSprite.h"

class Pig: public AnimateSprite{
    public:
        enum STATE{
            NORMAL,
            DAMAGED1,
            DAMAGED2,
            NUM_STATES
        };
        void jump();
        void slideLeft();
        void slideRight();
        Pig(GLfloat xi,GLfloat yi,GLfloat zi,GLuint texID,SpriteCoords* sCoords);
};


#endif // PIG_H_INCLUDED
