#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "inanimateSprite.h"

class Platform: public InanimateSprite{
    public:
		enum PLATFORM_TAG{
		    PLATFORM_WOODEN,
		    PLATFORM_ICE,
		    PLATFORM_STONE
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
        Platform(GLfloat,GLfloat,GLfloat,InanimateSpriteSheet*);
        void draw();

};

#endif // PLATFORM_H_INCLUDED
