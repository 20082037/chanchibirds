#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <map>

enum TAG{
    PIG,
    BIRD,
    PLATFORM,
    SLINGSHOT
};

class System{
    public:

        //Window components
        SDL_Window *window;
        const int WINDOW_WIDHT=1300;
        const int WINDOW_HEIGHT=700;
        SDL_GLContext glcontext;



        list<Platform> platforms;
        list<Bird> birds;
        Slingshot slingshot;
        Pig pig;
        Background background;

        map<int,map<int,GLfloat*>> textures;

        System();
        void init();

    private:
        bool setup();
        bool setupGL();
        bool loadMedia();
};



#endif // SYSTEM_H_INCLUDED
