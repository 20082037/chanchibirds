#include "bird.h"

Bird::Bird(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet){
    this->x=xi;
    this->y=yi;
    this->z=zi;
    this->sprites = ssheet;
    this->width=ssheet->states[0].begin()->c2.y - ssheet->states[0].begin()->c1.y;
    this->width=ssheet->states[0].begin()->c2.x - ssheet->states[0].begin()->c1.x;
    this->state=BIRD_HEALTHY;
}


void Bird::draw(){
    glPushMatrix();
    glTranslatef(this->x,this->y,this->z);
    glBindTexture(GL_TEXTURE_2D,sprites->texID;);
    glBegin(GL_QUADS);
        glTexCoord2f(sprites->states[state].c1.first,sprites->states[state].c2.second);
        glVertex3f(-width/2,height/2,0);
        glTexCoord2f(sprites->states[state].c1.first,sprites->states[state].c1.second);
        glVertex3f(-width/2,-height/2,0);
        glTexCoord2f(sprites->states[state].c2.first,sprites->states[state].c1.second);
        glVertex3f(width/2,-height/2,0);
        glTexCoord2f(sprites->states[state].c2.first,sprites->states[state].c2.second);
        glVertex3f(width/2,height/2,0);
    glEnd();
    glPopMatrix();
}
