#include "bird.h"

Bird::Bird(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet, b2World* world){

    z= zi;
    sprites = ssheet;
    width=ssheet->states[BIRD_HEALTHY].begin()->c2.second - ssheet->states[BIRD_HEALTHY].begin()->c1.second;
    height=ssheet->states[BIRD_HEALTHY].begin()->c2.first - ssheet->states[BIRD_HEALTHY].begin()->c1.first;
    state=BIRD_HEALTHY;
    currentAnim=sprites->states[state].begin();

    defBody.position.Set(xi,yi);
    defBody.type = b2_dynamicBody;
    body = world -> CreateBody(&defBody);

    shape.m_p.Set(0.f,0.f);
    shape.m_radius = height/2;

    fixture.shape =  &shape;
    fixture.restitution = 0.6f;
    fixture.filter.groupIndex = -8;
    fixture.density=0.3f;

    body->CreateFixture(&fixture);

    shape.ComputeMass(&massDa, fixture.density);
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
    glTranslatef(body->GetPosition().x,body->GetPosition().y,z);
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
