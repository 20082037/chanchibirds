#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "system.h"
#include <GL.h>

class Sprite{
    public:
        //Tag deleted because Sprite only needs a textureID and its sprite coordinates to be drawn.
        //They, as well, will be modified and have to get values from some external parameters

        //Events, power states?
//        GLuint textureID;


//        SpriteCoordinates sprites*; Pig is a sprite having an animation.
        int state;//By now, it can mean the health

        //Coordinates
        GLfloat x;
        GLfloat y;
        GLfloat layer;

        //Dimensions
        GLfloat width;
        GLfloat height;

        void draw();
        //A function to get the values changed by some Box2d function?
        //Every character will draw itself with its own fields, it's not likely they will need extra parameters

    private:
};

#endif // SPRITE_H_INCLUDED
