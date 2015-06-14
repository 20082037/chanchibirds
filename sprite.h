#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <GL/gl.h>

struct SpriteCoords{
    pair<GLfloat,GLfloat> c1;
    pair<GLfloat,GLfloat> c2;
};

class Sprite{
    public:
        int state;//By now, it can mean the health

        //Coordinates
        GLfloat x;
        GLfloat y;
        GLfloat z;

        //Dimensions
        GLfloat width;
        GLfloat height;

        virtual void draw()=0;
        //A function to get the values changed by some Box2d function?
        //Every character will draw itself with its own fields, it's not likely they will need extra parameters

};

#endif // SPRITE_H_INCLUDED
