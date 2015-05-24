#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <FreeImage.h>
#include <iostream>

using namespace std;

bool iniciar();
bool iniciarGL();
void cerrar();
void render();
SDL_Window *w = NULL;
SDL_GLContext glcontext;
bool moverx,movery;
GLfloat despx,despy;
//GLfloat equis[]={0.0f,-0.07f,0.07f};
GLfloat equisw[]={(-600.f / 1300.f)*1.857f,(-600.f / 1300.f)*1.857f,(-550.f / 1300.f)*1.857f,(-550.f / 1300.f)*1.857f};
GLfloat ye[]={1.f,-1.f,-1.f};
GLfloat ie = (-334.f / 384.f);
int main(int argc, char*argv[]){
    if(iniciar()){
        bool salir=false;
        SDL_Event jordan;
        while(!salir){
            while(SDL_PollEvent(&jordan) != 0){
                if(jordan.type == SDL_QUIT){
                    salir = true;
                }else if(jordan.type == SDL_KEYDOWN){
                    if(jordan.key.keysym.sym == SDLK_LEFT){
                        moverx = true;
                        despx = -0.005f;
                    }else if(jordan.key.keysym.sym == SDLK_RIGHT){
                        moverx = true;
                        despx = 0.005f;
                    }else if(jordan.key.keysym.sym == SDLK_DOWN){
                        movery = true;
                        despy = -0.005f;
                    }else if(jordan.key.keysym.sym == SDLK_UP){
                        movery = true;
                        despy = 0.005f;
                    }
                }
            }
            render();
            SDL_GL_SwapWindow(w);
        }
        cerrar();
    }
    return 0;
}


bool iniciar(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        cout<<"Error"<<endl;
        return false;
    }else{
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
        w = SDL_CreateWindow("WILSON TE VOLTEA 360 IDA Y VUELTA",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1300,700,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
        if(w == NULL){
            cout<<"Error."<<endl;
            return false;
        }
        glcontext = SDL_GL_CreateContext(w);
        if(glcontext == NULL){
            cout<<"Ay :("<<endl;
            return false;
        }
        if(!iniciarGL()){
            cout<<"¡Ay, no! :("<<endl;
            return false;
        }
    }
    return true;
}

bool iniciarGL(){
    GLenum error = GL_NO_ERROR;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-100,100,-100,100,-150,150);
    gluPerspective(60.0,1366/768,0.0,-0.05);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"Ay! :("<<endl;
        return false;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"Ay! :("<<endl;
        return false;
    }
    glClearColor(0.f,0.f,0.f,1.f);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"Ay! nooooo :("<<endl;
        return false;
    }
    return true;
}

void cerrar(){
    SDL_DestroyWindow(w);
    w = NULL;
    SDL_Quit();
}

void render(){
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-2.0);
    glBegin(GL_QUADS);
        GLfloat h = 40.f / 768.f  ,aux;
        if(movery){
            ie+=despy;
            movery=false;
        }
        aux = ie;
        for(int i=0;i<10;i++){
            if(i%2==0){
                glColor3f(1.0,0.0,0.0);
                glVertex3f((0.f / 683.f)*1.857f,ie,-0.5f);
                glVertex3f((0.f / 683.f)*1.857f,ie+h,-0.5f);
                glVertex3f((100.f / 683.f)*1.857f,ie+h,-0.5f);
                glVertex3f((100.f / 683.f)*1.857f,ie,-0.5f);

                glVertex3f((300.f / 683.f)*1.857f,ie,-0.5f);
                glVertex3f((300.f / 683.f)*1.857f,ie+h,-0.5f);
                glVertex3f((400.f / 683.f)*1.857f,ie+h,-0.5f);
                glVertex3f((400.f / 683.f)*1.857f,ie,-0.5f);

            }else{
                glVertex3f((150.f / 683.f)*1.857f,ie,-0.5f);
                glVertex3f((150.f / 683.f)*1.857f,ie+h,-0.5f);
                glVertex3f((250.f / 683.f)*1.857f,ie+h,-0.5f);
                glVertex3f((250.f / 683.f)*1.857f,ie,-0.5f);

            }
            ie += 100.f/768.f + h ;
        }
        ie=aux;

        if(moverx){
            equisw[0]+=despx;
            equisw[1]+=despx;
            equisw[2]+=despx;
            equisw[3]+=despx;
            moverx=false;
        }
        glColor3f(1.0,1.0,1.0);
        glVertex3f(equisw[0],-50.f/683.f,0.0f);
        glVertex3f(equisw[1],50.f/683.f,0.0f);
        glVertex3f(equisw[2],50.f/683.f,0.0f);
        glVertex3f(equisw[3],-50.f/683.f,0.0f);

    glEnd();
//    if(moverx){
//        equis[0] += despx;
//        equis[1] += despx;
//        equis[2] += despx;
//        moverx = false;
//    }
//    if(movery){
//        ye[0] += despy;
//        ye[1] += despy;
//        ye[2] += despy;
//        movery=false;
//     }
//    glBegin(GL_TRIANGLES);
//        glColor3f(1.0,1.0,0.0);
//        glVertex3f(equis[0],ye[0],0.0f);
//
//        glVertex3f(equis[1],ye[1],0.0f);
//        glVertex3f(equis[2],ye[2],0.0f);
//    glEnd();

}
