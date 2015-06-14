#include "pig.h"

Pig::Pig(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet){//Provisional, se debería proveer direction y speed
    this->x=xi;
    this->y=yi;
    this->z=zi;
    this->sprites = ssheet;
    this->width=ssheet->states[PIG_HEALTHY].begin()->c2.second - ssheet->states[PIG_HEALTHY].begin()->c1.second;
    this->height=ssheet->states[PIG_HEALTHY].begin()->c2.first - ssheet->states[PIG_HEALTHY].begin()->c1.first;
    this->state=PIG_HEALTHY;
    this->currentAnim=sprites->states[state].begin();
}

void Pig::animate(){
    if(currentAnim==--sprites->states[state].end()){
        currentAnim=sprites->states[state].begin();
    }else{
        currentAnim++;
    }
}

void Pig::draw(){
    cout<<"I'm drawing a pig!"<<endl;
    glPushMatrix();
    glTranslatef(this->x,this->y,this->z);
    cout<<"X: "<<this->x<<" Y: "<<this->y<<" Z: "<<this->z<<endl;
    cout<<"W: "<<this->width<<" - H: "<<this->height<<endl;
    glBindTexture(GL_TEXTURE_2D,sprites->texID);
    glBegin(GL_QUADS);
        glTexCoord2f(currentAnim->c1.first / sprites->imageWidth,currentAnim->c2.second / sprites->imageHeight);
        //glColor3f(1.f,0.f,1.f);
        glVertex3f(-width/2,height/2,0);
        glTexCoord2f(currentAnim->c1.first / sprites->imageWidth,currentAnim->c1.second / sprites->imageHeight);
        //glColor3f(1.f,0.f,1.f);
        glVertex3f(-width/2,-height/2,0);
        glTexCoord2f(currentAnim->c2.first / sprites->imageWidth,currentAnim->c1.second / sprites->imageHeight);
        //glColor3f(1.f,0.f,1.f);
        glVertex3f(width/2,-height/2,0);
        glTexCoord2f(currentAnim->c2.first / sprites->imageWidth,currentAnim->c2.second / sprites->imageHeight);
        //glColor3f(1.f,0.f,1.f);
        glVertex3f(width/2,height/2,0);
    glEnd();
    glPopMatrix();
}
