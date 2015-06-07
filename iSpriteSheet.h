#ifndef ISPRITESHEET_H_INCLUDED
#define ISPRITESHEET_H_INCLUDED

class InanimateSpriteSheet: public SpriteSheet{
    public:
        map<int,SpriteCoords > states;
        bool loadSpriteMap(ifstream& file,int TAG,int TAG_TYPE);
};


#endif // ISPRITESHEET_H_INCLUDED
