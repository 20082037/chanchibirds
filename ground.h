#ifndef GROUND_H_INCLUDED
#define GROUND_H_INCLUDED

#include "inanimateSprite.h"

class Ground: public InanimateSprite{
    public:
        enum GROUND_TAG{
            GROUND_NORMAL,
            NUM_GROUND_TAGS
        }
        enum GROUND_HEALTH{
        	GROUND_HEALTHY,
        	NUM_GROUND_HEALTH
        }
        b2PolygonShape shape;
        Ground(float,float,float,InanimateSpriteSheet*,b2World*);
};

#endif // GROUND_H_INCLUDED
