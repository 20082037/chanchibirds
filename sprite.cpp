#include "sprite.h"
#define .x .first
#define .y .second
void Sprite::draw(){
    glPushMatrix();
    glTranslated(this->x,this->y,this->z);
    glBegin(GL_QUADS);
        glTexCoord2f(sprites[state].c1.x,sprites[state].c2.y);
        glVertex3f(-width/2,height/2,layer);
        glTexCoord2f(sprites[state].c1.x,sprites[state].c1.y);
        glVertex3f(-width/2,-height/2,layer);
        glTexCoord2f(sprites[state].c2.x,sprites[state].c1.y);
        glVertex3f(width/2,-height/2,layer);
        glTexCoord2f(sprites[state].c2.x,sprites[state].c2.y);
        glVertex3f(width/2,height/2,layer);
    glEnd();
    glPopMatrix();
}
