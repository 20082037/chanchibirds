#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "system.h"

class Sprite{
    public:
        int tag;
        GLint textureID;
        int state;

        //Coordinates
        GLfloat x;
        GLfloat y;
        GLfloat z;

        //Dimensions
        GLfloat width;
        GLfloat height;

        virtual void draw() = 0;

    private:


};

#endif // SPRITE_H_INCLUDED
