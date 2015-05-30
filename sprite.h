#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "system.h"
#include <GL.h>

class Sprite{
    public:
        //Tag deleted because Sprite only needs a textureID and its sprite coordinates to be drawn.
        //They, as well, will be modified and have to get values from some external parameters

        //Events, power states?
        GLint textureID;
        SpriteCoordinates sprites*;
        int state;//By now, it can mean the health

        //Coordinates
        GLfloat x;
        GLfloat y;
        GLfloat z;

        //Dimensions
        GLfloat width;
        GLfloat height;

        virtual void draw() = 0;
        //A function to get the values changed by some Box2d function?
    private:
};

#endif // SPRITE_H_INCLUDED
