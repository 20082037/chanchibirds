#ifndef PIG_H_INCLUDED
#define PIG_H_INCLUDED

#include "animateSprite.h"

class Pig: public AnimateSprite{
    public:
    	enum PIG_TAG{
		    PIG_NORMAL,
		    PIG_HELMET,
		    PIG_KING,
		    NUM_PIG_TAGS
		};

		enum PIG_HEALTH{
		    PIG_HEALTHY,
		    PIG_DAMAGED1,
		    PIG_DAMAGED2,
		    NUM_PIG_HEALTH
		};

        //int currentAnim;

        b2CircleShape shape;
        b2FixtureDef fixture;
        b2MassData massDa;

        void jump();
        void slideLeft();
        void slideRight();
        void down();
        void animate();
        void draw();
        Pig(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet*,b2World*);
};


#endif // PIG_H_INCLUDED
