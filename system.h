#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <iostream>
#include <map>
#include <list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <Box2D/Box2D.h>
//#include <FreeImage.h>

#include "bird.h"
#include "pig.h"
#include "platform.h"
#include "ground.h"
//#include "slingshot.h"

using namespace std;

enum TAG{
    PIG,
    BIRD,
    PLATFORM,
    SLINGSHOT,
    GROUND,
    NUM_TAGS
};

// enum SLINGSHOT_TAG{};

class System{
    public:
        //Window components
        SDL_Window *window;
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;
        SDL_GLContext glcontext;

        //Box2D components
        b2Vec2 gravity;
        b2World world;
        float32 timeStep;
        int32 velocityIteration;
        int32 positionIteration;

        //Game components
        list<Platform*> platforms;
        list<Bird*> birds;
//        Slingshot* slingshot;
        Pig* pig;
        Ground* ground;


        map<int,map<int,AnimateSpriteSheet> > aSprites;
        map<int,map<int,InanimateSpriteSheet> > iSprites;

        map<GLfloat,list<Sprite*> > canvas;

        System(): gravity(0.f,-10.f), world(gravity)
        {
            WINDOW_WIDTH=1300;
            WINDOW_HEIGHT=700;
            timeStep=1.0f/60.0f;
            velocityIteration=8;
            positionIteration=3;
        };

        void initGame();

    private:
        bool setup();
        void setdown();
        bool setupGL();
        bool loadMedia();
        void initSprites();
        void renderGlobal();
};
#endif // SYSTEM_H_INCLUDED
