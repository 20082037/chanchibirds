#include "system.h"

#define traverse(c,it) for( typeof(c.begin()) it = c.begin(); it!=c.end(); it++)

void System::initGame(){
    if(setup()){
        if(loadMedia()){
            initSprites();
            bool salir=false;
            SDL_Event e;
            while(!salir){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        salir = true;
                    }else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            case SDLK_RIGHT: pig->animate();
                            break;
                            case SDLK_LEFT: (*birds.begin())->animate();
                            break;
                            case SDLK_UP: pig->jump();
                            break;
                        }
                    }
                }
                world.Step(timeStep,velocityIteration,positionIteration);
                renderGlobal();
                SDL_GL_SwapWindow(window);
            }
            setdown();
        }
    }
}

void System::initSprites(){
    //Plataformas
    int nPlatforms=10;
    GLfloat x=0.f,y=350.f,z=50.f;//Valores iniciales:cambiar
    Platform* paux;
    for(int i=1;i<=nPlatforms;i++){
        if(i%5==4){
            x=75.f;
            y-=65.f;
        }else{
            if(i%5==1){
                x=0.f;
                y-=65.f;
            }else{
                x+=200.f;
            }
        }
        paux = new Platform(x,y,z,&iSprites[PLATFORM][Platform::PLATFORM_STONE],&world);
        platforms.push_back(paux);
        canvas[z].push_back(paux);
    }

    //Pájaros
    Bird* baux;
    x=-400.f;y=-200.f;z=30.f;
    //It then will iterate
    baux = new Bird(x,y,z,&aSprites[BIRD][Bird::BIRD_YELLOW],&world);
    birds.push_back(baux);
    canvas[z].push_back(baux);

    //Chancho
    x=0.f;y=0.f;z=15.f;
    pig = new Pig(x,y,z,&aSprites[PIG][Pig::PIG_NORMAL],&world);
    canvas[z].push_back(pig);

    //Piso
    x=0.f;y=-300.f;z=5.f;
    ground = new Ground(x,y,z,&iSprites[GROUND][Ground::GROUND_NORMAL],&world);
    canvas[z].push_back(ground);
}

bool System::setup(){
    bool success=true;

    if(SDL_Init(SDL_INIT_VIDEO)>=0){
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
        window=SDL_CreateWindow("Chanchi Birds",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

        if(window!=NULL){
            glcontext = SDL_GL_CreateContext(window);
            if(glcontext!=NULL){
                if(!setupGL()){
                    success=false;
                }
            }else{
                cout<<"System/setup - Fallo al crear contexto OpenGL: glcontext == NULL"<<endl;
            }
        }else{
            cout<<"System/setup - Fallo en crear la ventana: window == NULL"<<endl;
            success=false;
        }
    }else{
        cout<<"System/setup - Fallo en inicializacion de SDL: SDL_Init(SDL_INIT_VIDEO)<0"<<endl;
        success=false;
    }
    return success;
}

bool System::setupGL(){
    GLenum error=GL_NO_ERROR;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH/2,WINDOW_WIDTH/2,-WINDOW_HEIGHT/2,WINDOW_HEIGHT/2,-150,150);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f,0.f,0.f,1.f);
    glEnable(GL_TEXTURE_2D);


    error = glGetError();
    if( error != GL_NO_ERROR){
        cout<<"System/setupGL - Error al inicializar OpenGL"<<endl;
        return false;
    }else{
        return true;
    }
}

void System::setdown(){
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_Quit();
}

bool System::loadMedia(){
    bool success= true;
    success = aSprites[PIG][Pig::PIG_NORMAL].loadTextureFromFile("images/normalPig.png");
    success = aSprites[PIG][Pig::PIG_NORMAL].loadSpriteMap("SpriteCoordinates.txt",PIG,Pig::PIG_NORMAL);

    success = aSprites[PIG][Pig::PIG_HELMET].loadTextureFromFile("images/pig_helmet.png");
    success = aSprites[PIG][Pig::PIG_HELMET].loadSpriteMap("SpriteCoordinates.txt",PIG,Pig::PIG_HELMET);

    success = aSprites[PIG][Pig::PIG_KING].loadTextureFromFile("images/pig_crown.png");
    success = aSprites[PIG][Pig::PIG_KING].loadSpriteMap("SpriteCoordinates.txt",PIG,Pig::PIG_KING);

    success = aSprites[BIRD][Bird::BIRD_YELLOW].loadTextureFromFile("images/pajaro_amarillo.png");
    success = aSprites[BIRD][Bird::BIRD_YELLOW].loadSpriteMap("SpriteCoordinates.txt",BIRD,Bird::BIRD_YELLOW);

    success = aSprites[BIRD][Bird::BIRD_RED].loadTextureFromFile("images/redBird.png");
    success = aSprites[BIRD][Bird::BIRD_RED].loadSpriteMap("SpriteCoordinates.txt",BIRD,Bird::BIRD_RED);

    success = iSprites[PLATFORM][Platform::PLATFORM_STONE].loadTextureFromFile("images/bloqueconcreto.png");
    success = iSprites[PLATFORM][Platform::PLATFORM_STONE].loadSpriteMap("SpriteCoordinates.txt",PLATFORM,Platform::PLATFORM_STONE);

    success = iSprites[GROUND][Ground::GROUND_NORMAL].loadTextureFromFile("images/ground.jpg");
    success = iSprites[GROUND][Ground::GROUND_NORMAL].loadSpriteMap("SpriteCoordinates.txt",GROUND,Ground::GROUND_NORMAL);



    return success;
}

void System::renderGlobal(){
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    traverse(canvas,sPair){
        traverse(sPair->second,sprite){
            (*sprite)->draw();
        }
    }
}
