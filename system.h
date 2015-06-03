#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <FreeImage.h>
#include <map>
#include "aSpriteSheet.h"

typedef struct SpriteCoords{
    pair<GLfloat,GLfloat> c1;
    pair<GLfloat,GLfloat> c2;
};

enum PIG_TAG{
    NORMAL,
    HELMET,
    KING,
    NUM_PIG_TAGS
};
enum BIRD_TAG{
    YELLOW,
    NUM_BIRD_TAGS
};
enum PLATFORM_TAG{
    WOODEN,
    ICE,
    IRON
};
enum SLINGSHOT_TAG{};

class System{

    enum TAG{//Each tag has its only spritesheet and states
        PIG,
        BIRD,
        PLATFORM,
        SLINGSHOT,
        NUM_TAGS
    };

    public:
        //Window components
        SDL_Window *window;
        const int WINDOW_WIDHT=1300;
        const int WINDOW_HEIGHT=700;
        SDL_GLContext glcontext;

        //Game components
        list<Platform*> platforms;
        list<Bird*> birds;
        Slingshot* slingshot;
        Pig* pig;

//        map<int,map<int,GLuint*> > textures;//Estara incluido en los objetos SpriteSheet
        //map<TAG,map<TAGTYPE,TEXTUREID> >
        map<int,map<int,AnimateSpriteSheet> > aSprites;
        map<int,map<int,InanimateSpriteSheet> > iPrites;
        //map<TAG,map<STATE,SpriteCoords> >

        map<GLfloat,list<Sprite*> > canvas;

        System();
        void initGame();

    private:
        bool setup();
        bool setupGL();
        void loadMedia();
        void initSprites();
        void renderGlobal();
        GLuint loadTexture(string filenameString);
};
#endif // SYSTEM_H_INCLUDED
