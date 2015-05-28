#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED



class Sprite{
    public:
        int tag;
        GLint textureID;
        int state;

        //Coordinates
        GLfloat x;
        GLfloat y;
        GLfloat z;

        //Dimensions
        GLfloat width;
        GLfloat height;

        void draw();

    private:


};

#endif // SPRITE_H_INCLUDED
