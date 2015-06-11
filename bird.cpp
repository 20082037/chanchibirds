#include "bird.h"

Bird::Bird(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet){
    this->x=xi;
    this->y=yi;
    this->z=zi;
    this->sprites = ssheet;
    this->width=ssheet->states[BIRD_HEALTHY].begin()->c2.y - ssheet->states[BIRD_HEALTHY].begin()->c1.y;
    this->width=ssheet->states[BIRD_HEALTHY].begin()->c2.x - ssheet->states[BIRD_HEALTHY].begin()->c1.x;
    this->state=BIRD_HEALTHY;
    this->currentAnim=0;
}

void Bird::animate(){
    if(currentAnim==4){
        currentAnim=0;
    }else{
        currentAnim++;
    }
}

void Bird::draw(){
    glPushMatrix();
    glTranslatef(this->x,this->y,this->z);
    glBindTexture(GL_TEXTURE_2D,sprites->texID;);
    glBegin(GL_QUADS);
        glTexCoord2f( (sprites->states[state].begin()+currentAnim)->c1.first / sprites->imageWidth,(sprites->states[state].begin()+currentAnim)->c2.second / sprites->imageHeight);
        glVertex3f(-width/2,height/2,0);
        glTexCoord2f( (sprites->states[state].begin()+currentAnim)->c1.first / sprites->imageWidth,(sprites->states[state].begin()+currentAnim)->c1.second / sprites->imageHeight);
        glVertex3f(-width/2,-height/2,0);
        glTexCoord2f( (sprites->states[state].begin()+currentAnim)->c2.first / sprites->imageWidth,(sprites->states[state].begin()+currentAnim)->c1.second / sprites->imageHeight);
        glVertex3f(width/2,-height/2,0);
        glTexCoord2f( (sprites->states[state].begin()+currentAnim)->c2.first / sprites->imageWidth,(sprites->states[state].begin()+currentAnim)->c2.second / sprites->imageHeight);
        glVertex3f(width/2,height/2,0);
    glEnd();
    glPopMatrix();
}
