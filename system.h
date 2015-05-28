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
