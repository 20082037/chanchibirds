#ifndef PIG_H_INCLUDED
#define PIG_H_INCLUDED

#include "animateSprite.h"

class Pig: public AnimateSprite{
    public:
        int currentAnim;


        void jump();
        void slideLeft();
        void slideRight();
        void animate();
        Pig(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* sCoords);

};


#endif // PIG_H_INCLUDED
