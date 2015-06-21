#ifndef INANIMATESPRITE_H_INCLUDED
#define INANIMATESPRITE_H_INCLUDED

#include "sprite.h"
#include "iSpriteSheet.h"

class InanimateSprite: public Sprite{
    public:
		InanimateSpriteSheet* sprites;
		InanimateSprite(){
            sprites = NULL;
		};
};


#endif // INANIMATESPRITE_H_INCLUDED
