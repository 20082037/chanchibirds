#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

enum{
    PIG,
    BIRD,
    PLATFORM,
}


class System{
    public:
        list<Platform> platforms;
        Pig pig;

        map<int,map<int,GLfloat*>> textures;

        void init();
        void setup();
        void setupGL();
        void loadMedia();

};



#endif // SYSTEM_H_INCLUDED
