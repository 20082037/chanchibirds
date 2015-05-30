#ifndef PIG_H_INCLUDED
#define PIG_H_INCLUDED

#include "sprite.h"

class Pig: public Sprite{
    public:
        enum STATE{
            NORMAL,
            DAMAGED1,
            DAMAGED2,
            DEAD
        };
        Pig(GLfloat xi,GLfloat yi,GLfloat zi,GLuint texID,SpriteCoords* sCoords);
};


#endif // PIG_H_INCLUDED
