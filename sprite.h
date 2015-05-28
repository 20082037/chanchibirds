#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "system.h"

class Sprite{
    public:
        TAG tag;
        GLint textureID;
        STATE state;

        //Coordinates
        GLfloat x;
        GLfloat y;
        GLfloat z;

        //Dimensions
        GLfloat width;
        GLfloat height;

        Sprite(GLfloat x,GLfloat y,GLfloat z,GLfloat width,GLfloat height);
        virtual void draw() = 0;

    private:


};

#endif // SPRITE_H_INCLUDED
