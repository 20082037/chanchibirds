#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "animateSprite.h"

class Bird: public AnimateSprite{
    public:
    	enum BIRD_TAG{
		    BIRD_YELLOW,
		    BIRD_RED,
		    NUM_BIRD_TAGS
		};
		enum BIRD_HEALTH{
		    BIRD_HEALTHY,
		    NUM_BIRD_HEALTH
		};

        int currentAnim;
        Bird(GLfloat,GLfloat,GLfloat,AnimateSpriteSheet*);
        void draw();
        void animate();
        //void fly();//missing parameters

};

#endif // BIRD_H_INCLUDED
