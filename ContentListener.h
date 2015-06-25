#ifndef CONTENTLISTENER_H_INCLUDED
#define CONTENTLISTENER_H_INCLUDED

#include <Box2D/Box2D.h>




class ContentListener: public b2ContactListener{
    public:
        void BeginContact(b2Contact*);
        //void EndContact(b2Contact*);
};

#endif // CONTENTLISTENER_H_INCLUDED
