#ifndef ANIMATESPRITE_H_INCLUDED
#define ANIMATESPRITE_H_INCLUDED

#include "sprite.h"
#include "aSpriteSheet.h"

class AnimateSprite: public Sprite{
    public:
        AnimateSpriteSheet* sprites;
};

#endif // ANIMATESPRITE_H_INCLUDED

