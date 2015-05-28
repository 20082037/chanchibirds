#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

enum TAG{
    PIG,
    BIRD,
    PLATFORM,
    SLINGSHOT
};

enum PIG_STATE{

}

enum PLATFORM_STATE{

}


class System{
    public:

        list<Platform> platforms;
        Pig pig;

        map<int,map<int,GLfloat*>> textures;

        System();
        void init();

    private:
        void setup();
        void setupGL();
        void loadMedia();

};



#endif // SYSTEM_H_INCLUDED
