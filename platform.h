#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "inanimateSprite.h"

class Platform: public InanimateSprite{
    public:
        enum STATE{
            NORMAL,
        }
        bool direction;
        float speed;
        Platform(GLfloat,GLfloat,GLfloat,InanimateSpriteSheet*);
        void draw();
        //Provisional, se debería proveer direction y speed

};

#endif // PLATFORM_H_INCLUDED
