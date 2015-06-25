#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <iostream>
#include <map>
#include <list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <Box2D/Box2D.h>

#include "bird.h"
#include "pig.h"
#include "platform.h"
#include "ground.h"
#include "background.h"
#include "ContentListener.h"
//#include "slingshot.h"

using namespace std;

enum TAG{
    PIG,
    BIRD,
    PLATFORM,
    SLINGSHOT,
    GROUND,
    BACKGROUND,
    NUM_TAGS
};


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

        b2BodyDef limits;
        b2Body* windowLimits;
        b2EdgeShape positionsLimits;
        b2FixtureDef fixtureLimits;

        float32 timeStep;
        int32 velocityIteration;
        int32 positionIteration;

        ContentListener contactL;


       //Game components
        list<Platform*> platforms;
        list<Bird*> birds;
//        Slingshot* slingshot;
        Pig* pig;
        Ground* ground;
        Background* background;



        clock_t dtBird;
        clock_t tiBird;


        map<int,map<int,AnimateSpriteSheet> > aSprites;
        map<int,map<int,InanimateSpriteSheet> > iSprites;

        map<GLfloat,list<Sprite*> > canvas;

        System(): gravity(0.f,-10.f), world(gravity)
        {
            WINDOW_WIDTH=1300;
            WINDOW_HEIGHT=700;

            timeStep = 1.f/60.f;
            velocityIteration=8;
            positionIteration=3;

            dtBird = 0;
            tiBird = clock();

            limits.position.Set(-WINDOW_WIDTH/2,-WINDOW_HEIGHT/2);
            windowLimits = world.CreateBody(&limits);
            fixtureLimits.shape = &positionsLimits;
            positionsLimits.Set(b2Vec2(0.f,0.f),b2Vec2((float)WINDOW_WIDTH,0.f));
            windowLimits->CreateFixture(&fixtureLimits);
            positionsLimits.Set(b2Vec2((float)WINDOW_WIDTH,0.f),b2Vec2((float)WINDOW_WIDTH,(float)WINDOW_HEIGHT));
            windowLimits->CreateFixture(&fixtureLimits);
            positionsLimits.Set(b2Vec2((float)WINDOW_WIDTH,(float)WINDOW_HEIGHT),b2Vec2(0.f,(float)WINDOW_HEIGHT));
            windowLimits->CreateFixture(&fixtureLimits);
            positionsLimits.Set(b2Vec2(0.f,(float)WINDOW_HEIGHT),b2Vec2(0.f,0.f));
            windowLimits->CreateFixture(&fixtureLimits);

            world.SetContactListener(&contactL);

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
