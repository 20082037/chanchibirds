#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "inanimateSprite.h"


class Background: public InanimateSprite{
public:
    enum BACKGROUND_TAG{
        GAME_BACKGROUND,
        MENU_BACKGROUND,
        NUM_BACKGROUND_TAGS
    };

    enum BACKGROUND_HEALTH{
        BACKGROUND_NORMAL,
        NUM_BACKGROUND_HEALTH
    };
    GLfloat x;
    GLfloat y;
    Background(GLfloat,GLfloat,GLfloat,InanimateSpriteSheet*,int);
    void draw();

};

#endif // BACKGROUND_H_INCLUDED
