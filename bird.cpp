#include "bird.h"

Bird::Bird(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet, b2World* world){

    this->defBody.type = b2_dynamicBody;
    this->defBody.position.Set(xi,yi);
    this->body = world -> CreateBody(& this->defBody);
    this->shape.m_p.Set(0.f,0.f);
    this->shape.m_radius = 20.0f;
    this->fixture.shape =  & this->shape;
    this->fixture.restitution = 0.6f;
    this->fixture.filter.groupIndex = -8;

    this->body->CreateFixture(& this->fixture);

    this->mass.mass=300.f;
    this->body->SetMassData(&this->mass);


    // this->x= & this->body->GetPosition().x;
    // this->y= & this->body->GetPosition().y;
    this->z= zi;
    this->sprites = ssheet;
    this->width=ssheet->states[BIRD_HEALTHY].begin()->c2.second - ssheet->states[BIRD_HEALTHY].begin()->c1.second;
    this->height=ssheet->states[BIRD_HEALTHY].begin()->c2.first - ssheet->states[BIRD_HEALTHY].begin()->c1.first;
    this->state=BIRD_HEALTHY;
    this->currentAnim=sprites->states[state].begin();
}

void Bird::animate(){
    if(currentAnim==--sprites->states[state].end()){
        currentAnim=sprites->states[state].begin();
    }else{
        currentAnim++;
    }
}

void Bird::draw(){
    // cout<<"I'm a pig : pos: "<<this->body->GetPosition().x<<" "<<this->body->GetPosition().y<<endl;
    glPushMatrix();
    glTranslatef(this->body->GetPosition().x,this->body->GetPosition().y,this->z);
    glBindTexture(GL_TEXTURE_2D,sprites->texID);
    glBegin(GL_QUADS);
        glTexCoord2f( currentAnim->c1.first / sprites->imageWidth, currentAnim->c2.second / sprites->imageHeight);
        glVertex3f(-width/2,height/2,0);
        glTexCoord2f( currentAnim->c1.first / sprites->imageWidth, currentAnim->c1.second / sprites->imageHeight);
        glVertex3f(-width/2,-height/2,0);
        glTexCoord2f( currentAnim->c2.first / sprites->imageWidth, currentAnim->c1.second / sprites->imageHeight);
        glVertex3f(width/2,-height/2,0);
        glTexCoord2f( currentAnim->c2.first / sprites->imageWidth, currentAnim->c2.second / sprites->imageHeight);
        glVertex3f(width/2,height/2,0);
    glEnd();
    glPopMatrix();
}
