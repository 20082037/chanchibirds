#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <iostream>
#include <map>
#include <list>

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <FreeImage.h>

#include "bird.h"
#include "pig.h"
#include "platform.h"
//#include "slingshot.h"

using namespace std;

typedef struct SpriteCoords{
    pair<GLfloat,GLfloat> c1;
    pair<GLfloat,GLfloat> c2;
};

enum TAG{
    PIG,
    BIRD,
    PLATFORM,
    SLINGSHOT,
    NUM_TAGS
};

enum PIG_TAG{
    PIG_NORMAL,
    PIG_HELMET,
    PIG_KING,
    NUM_PIG_TAGS
};

enum PIG_HEALTH{
    PIG_HEALTHY,
    PIG_DAMAGED1,
    PIG_DAMAGED2,
    PIG_NUM_HEALTH
};

enum BIRD_TAG{
    BIRD_YELLOW,
    BIRD_RED,
    NUM_BIRD_TAGS
};

enum BIRD_HEALTH{
    BIRD_HEALTHY,
    NUM_BIRD_HEALTH
};

enum PLATFORM_TAG{
    PLATFORM_WOODEN,
    PLATFORM_ICE,
    PLATFORM_STONE
};

enum PLATFORM_HEALTH{
    PLATFORM_HEALTHY,
    PLATFORM_DAMAGED1,
    PLATFORM_DAMAGED2,
    PLATFORM_DAMAGED3,
    NUM_PLATFORM_HEALTH
};

enum SLINGSHOT_TAG{};

class System{
    public:
        //Window components
        SDL_Window *window;
        const int WINDOW_WIDTH=1300;
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
};
#endif // SYSTEM_H_INCLUDED
