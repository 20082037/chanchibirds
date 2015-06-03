#ifndef SPRITESHEET_H_INCLUDED
#define SPRITESHEET_H_INCLUDED

#include <GL.h>

class SpriteSheet{
    public:
        int numStates;//The number of animation frames can vary, but the number of states shouldnt.
        GLuint texID;
        bool loadTextureFromFile(string filenameString);

};


#endif // SPRITESHEET_H_INCLUDED
