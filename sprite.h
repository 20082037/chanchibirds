#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED


enum{
    PIG,
    BIRD,
    PLATFORM,
    CANON,
}

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

<<<<<<< HEAD

        //
        void mover(GLfloat x, GLfloat y);

=======
        void draw();
>>>>>>> da533b499e1cf9bccb0ddc04df4c2052d4955c13

    private:


};

#endif // SPRITE_H_INCLUDED
