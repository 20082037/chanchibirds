#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <FreeImage.h>
#include <map>

enum TAG{//Each tag has its only spritesheet and states
    PIG,
    BIRD,
    PLATFORM,
    SLINGSHOT,
};

struct SpriteCoords{
    pair<GLfloat,GLfloat> c1;
    pair<GLfloat,GLfloat> c2;
};


class System{
    public:

        //Window components
        SDL_Window *window;
        const int WINDOW_WIDHT=1300;
        const int WINDOW_HEIGHT=700;
        SDL_GLContext glcontext;


        //Game components
        list<Platform> platforms;
        list<Bird> birds;
        Slingshot* slingshot;
        Pig* pig;
        Background* background;


        map<int,GLuint*> textures;
        //map<TAG,TEXTUREID>
        map<int,map<int,SpriteCoords> > sprites;
        //map<TAG,map<STATE,SpriteCoords> >

        System();
        void init();

    private:
        bool setup();
        bool setupGL();
        void loadMedia();
        GLuint loadTexture(string filenameString);
};



#endif // SYSTEM_H_INCLUDED
