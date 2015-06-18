#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "inanimateSprite.h"

class Platform: public InanimateSprite{
    public:
		enum PLATFORM_TAG{
		    PLATFORM_WOODEN,
		    PLATFORM_ICE,
		    PLATFORM_STONE,
		    NUM_PLATFORM_TAGS
		};

		enum PLATFORM_HEALTH{
		    PLATFORM_HEALTHY,
		    PLATFORM_DAMAGED1,
		    PLATFORM_DAMAGED2,
		    PLATFORM_DAMAGED3,
		    NUM_PLATFORM_HEALTH
		};
        //bool direction;
        //float speed;
        b2PolygonShape shape;
        b2FixtureDef fixture;
        b2MassData mass;
        Platform(GLfloat,GLfloat,GLfloat,InanimateSpriteSheet*,b2World*);
        void draw();

};

#endif // PLATFORM_H_INCLUDED
