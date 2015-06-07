#include "pig.h"

Pig::Pig(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet){//Provisional, se debería proveer direction y speed
    this->x=xi;
    this->y=yi;
    this->z=zi;
    this->sprites = ssheet;
    this->width=ssheet->states[0].begin()->c2.y - ssheet->states[0].begin()->c1.y;
    this->width=ssheet->states[0].begin()->c2.x - ssheet->states[0].begin()->c1.x;
    this->state=PIG_HEALTHY;
    this->currentAnim=0;
}

void Pig::animate(){
    if(currentAnim==2){
        currentAnim=0;
    }else{
        currentAnim++;
    }
}

void Pig::draw(){
    glPushMatrix();
    glTranslatef(this->x,this->y,this->z);
    glBindTexture(GL_TEXTURE_2D,sprites->texID;);
    glBegin(GL_QUADS);
        glTexCoord2f((sprites->states[state].begin()+currentAnim)->c1.first,(sprites->states[state].begin()+currentAnim)->c2.second);
        glVertex3f(-width/2,height/2,0);
        glTexCoord2f((sprites->states[state].begin()+currentAnim)->c1.first,(sprites->states[state].begin()+currentAnim)->c1.second);
        glVertex3f(-width/2,-height/2,0);
        glTexCoord2f((sprites->states[state].begin()+currentAnim)->c2.first,(sprites->states[state].begin()+currentAnim)->c1.second);
        glVertex3f(width/2,-height/2,0);
        glTexCoord2f((sprites->states[state].begin()+currentAnim)->c2.first,(sprites->states[state].begin()+currentAnim)->c2.second);
        glVertex3f(width/2,height/2,0);
    glEnd();
    glPopMatrix();
}
