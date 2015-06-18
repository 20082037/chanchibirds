#include "pig.h"

Pig::Pig(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet, b2World* world){//Provisional, se debería proveer direction y speed

    this->defBody.type = b2_dynamicBody;
    this->defBody.position.Set(xi,yi);
    this->body = world -> CreateBody(& this->defBody);

    this->shape.m_p.Set(0.f,0.f);
    this->shape.m_radius=20.0f;
    this->fixture.shape =  & this->shape;
    this->fixture.restitution = 0.6f;
    this->fixture.friction = 0.3f;

    this->body->CreateFixture(& this->fixture);

    this->mass.mass=300.f;
    this->body->SetMassData(&this->mass);

    // this->x= & this->body->GetPosition().x;
    // this->y= & this->body->GetPosition().y;
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
    glPushMatrix();
    glTranslatef(this->body->GetPosition().x,this->body->GetPosition().y,this->z);
    // glTranslatef(this->x,this->y,this->z);
    glBindTexture(GL_TEXTURE_2D,sprites->texID);
    glBegin(GL_QUADS);
        glTexCoord2f(currentAnim->c1.first / sprites->imageWidth,currentAnim->c2.second / sprites->imageHeight);
        glVertex3f(-width/2,height/2,0);
        glTexCoord2f(currentAnim->c1.first / sprites->imageWidth,currentAnim->c1.second / sprites->imageHeight);
        glVertex3f(-width/2,-height/2,0);
        glTexCoord2f(currentAnim->c2.first / sprites->imageWidth,currentAnim->c1.second / sprites->imageHeight);
        glVertex3f(width/2,-height/2,0);
        glTexCoord2f(currentAnim->c2.first / sprites->imageWidth,currentAnim->c2.second / sprites->imageHeight);
        glVertex3f(width/2,height/2,0);
    glEnd();
    glPopMatrix();
}

void Pig::jump(){

    this->body->ApplyForce(b2Vec2(0.0f,999999999.0f),this->body->GetWorldCenter(),true);

}
