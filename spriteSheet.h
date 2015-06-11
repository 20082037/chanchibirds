#ifndef SPRITESHEET_H_INCLUDED
#define SPRITESHEET_H_INCLUDED

#include <GL/gl.h>

class SpriteSheet{
    public:
        // int numStates;//The number of animation frames can vary, but the number of states shouldnt.
        int imageWidth;
        int imageHeight;
        GLuint texID;
        bool loadTextureFromFile(string filenameString);
        float stof(string);

};


#endif // SPRITESHEET_H_INCLUDED
