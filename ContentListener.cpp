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
            if(B->tag == 1){
                B->alive = false;
                if(A->state < 3){
                    A->state++;
                    A->currentAnim = A->sprites->states[A->state].begin();
                }else{
                    A->alive = false;
                }
            }
        }else if(B->tag == 0){
            if(A->tag == 1){
                A->alive = false;
                if(B->state < 3){
                    B->state++;
                    B->currentAnim = B->sprites->states[B->state].begin();
                }else{
                    B->alive=false;
                }
            }
        }
    }else{
        cout<<"AY :("<<std::endl;
    }


}
