#include "bird.h"

//Este es un comentario

Bird::Bird(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet, b2World* world,int ta){
    tag = ta;
    alive = true;
    z= zi;
    sprites = ssheet;
    state=BIRD_HEALTHY;
    currentAnim=sprites->states[state].begin();
    width=currentAnim->c2.second - currentAnim->c1.second;
    height=currentAnim->c2.first - currentAnim->c1.first;
    dt = 0,ti = clock();


    defBody.position.Set(xi,yi);
    defBody.type = b2_dynamicBody;
    body = world -> CreateBody(&defBody);
    body->SetUserData(this);

    shape.m_p.Set(0.f,0.f);
    shape.m_radius = height/2;

    fixture.shape =  &shape;
    fixture.restitution = 0.6f;
    fixture.filter.groupIndex = -8;
    fixture.density=0.3f;


    body->CreateFixture(&fixture);
    body->ApplyForce(b2Vec2 (839999999999999.0f,999999999999999.0f),body->GetWorldCenter(),true);


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
    dt += clock()-ti;
    ti = clock();//No habra pasado mucho tiempo
    if(dt>6000){
        animate();
        dt = 0;
    }
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

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
    glDisable(GL_BLEND);
    glPopMatrix();
}
