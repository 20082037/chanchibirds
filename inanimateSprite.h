#ifndef INANIMATESPRITE_H_INCLUDED
#define INANIMATESPRITE_H_INCLUDED

#include "sprite.h"

class InanimateSprite: public Sprite{
    public:
        SpriteCoordinates sprites*;//It is supposed to be here and static since all their child classes
                                   //will have a vector of SpriteCoordinates and, for instance,
                                   //all the platforms will render from the same texture...

};


#endif // INANIMATESPRITE_H_INCLUDED
