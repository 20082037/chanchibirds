#ifndef SPRITESHEET_H_INCLUDED
#define SPRITESHEET_H_INCLUDED

#include <GL/gl.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>//atoi
#include <math.h>//pow
#include <FreeImage.h>
using namespace std;

class SpriteSheet{
    public:
        int imageWidth;
        int imageHeight;
        GLuint texID;

        SpriteSheet(){};
        bool loadTextureFromFile(string);
        float stof(string);
};

#endif // SPRITESHEET_H_INCLUDED
