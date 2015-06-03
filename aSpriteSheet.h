#ifndef ASPRITESHEET_H_INCLUDED
#define ASPRITESHEET_H_INCLUDED

#include "spriteSheet.h"

class AnimateSpriteSheet: public SpriteSheet{
    public:
        map<int,list<SpriteCoords> > states;
        bool loadSpriteMap(string filenameString,int TAG,int TAG_TYPE, int numStates);
};

#endif // ASPRITESHEET_H_INCLUDED
