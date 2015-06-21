#ifndef ANIMATESPRITE_H_INCLUDED
#define ANIMATESPRITE_H_INCLUDED

#include "sprite.h"
#include "aSpriteSheet.h"

class AnimateSprite: public Sprite{
    public:
        AnimateSpriteSheet* sprites;
        list<SpriteCoords>::iterator currentAnim;
        clock_t dt;
        clock_t ti;

        AnimateSprite(){

        };
};

#endif // ANIMATESPRITE_H_INCLUDED

