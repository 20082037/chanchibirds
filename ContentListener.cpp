#include "sprite.h"
#include "ContentListener.h"
#include <iostream>

using namespace std;
void ContentListener::BeginContact(b2Contact* contact){
    Sprite *A,*B;
    A = (Sprite*)contact->GetFixtureA()->GetBody()->GetUserData();
    B = (Sprite*)contact->GetFixtureB()->GetBody()->GetUserData();

    if(A != NULL && B != NULL){
        if(A->tag == 0){
            cout<<"A es un chancho"<<endl;
            if(B->tag == 1){
                cout<<"B es un pajaro"<<endl;
                //A->state --;
                //if(A->state == -1){
                //    A->alive = false;
                //}
                //Delete pig ///////////////////

                B->alive = false;

                cout<<"Se murio :("<<B<<endl;
//                B->body->GetWorld()->DestroyBody(B->body);
            }
        }else if(B->tag == 0){
            cout<<"B es un chancho"<<endl;
            if(A->tag == 1){
                cout<<"A es un pajaro"<<endl;
                //B->state --;
                //if(B->state == -1){
                //    B->alive = false;
                //}
                //Delete pig ///////////////////

                A->alive = false;
                cout<<"Se murio :("<<A<<endl;
//                A->body->GetWorld()->DestroyBody(A->body);
            }
        }
    }else{
        std::cout<<"AY :("<<std::endl;
    }


}
