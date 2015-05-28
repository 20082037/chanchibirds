#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <map>

enum TAG{//Each tag has its only spritesheet and states
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

        map<int,GLuint> textures;
        //map<TAG,TEXTUREID>

        map<int,map<int,pair<GLfloat,GLfloat>* > > sprites;
        //map<TAG,map<STATE,COORDENADAS<GLfloat,GLfloat>* > >

        System();
        void init();

    private:
        bool setup();
        bool setupGL();
        bool loadMedia();
        GLuint loadTexture(string filenameString);
};



#endif // SYSTEM_H_INCLUDED
