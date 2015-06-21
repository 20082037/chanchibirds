/*
#include<iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

using namespace std;

const int ancho_ventana = 1600;//ancho de la pantalla
const int largo_ventana = 700;//largo de la pantalla

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool cargarArchivo( string recorrido );

		//Deallocates texture
		void liberar();

		//Set blending
		void setBlendMode( SDL_BlendMode mezcla );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mAncho;
		int mLargo;
};

bool init();
bool cargar();
void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

LTexture gPromptTexture;

//Musica a recorrer
Mix_Music *gEverybody = NULL;

//Efectos
Mix_Chunk *gMenea = NULL;//pedazo de musica
Mix_Chunk *gMedium = NULL;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mAncho = 0;
	mLargo = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	liberar();
}

bool LTexture::cargarArchivo( string recorrido )
{
	//Get rid of preexisting texture
	liberar();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( recorrido.c_str() );
	if( loadedSurface == NULL )
	{
		cout<<"ERROR!!! \n"<<recorrido.c_str()<<IMG_GetError() ;
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			cout<<"Error!!! \n"<<recorrido.c_str()<<SDL_GetError();
		}
		else
		{
			//Get image dimensions
			mAncho = loadedSurface->w;
			mLargo = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::liberar()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mAncho = 0;
		mLargo = 0;
	}
}

void LTexture::setBlendMode( SDL_BlendMode mezcla )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, mezcla );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mAncho, mLargo };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mAncho;
}

int LTexture::getHeight()
{
	return mLargo;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		cout<<"ERROR!!! SDL no inicializa \n"<<SDL_GetError();
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			cout<<"ERROR!!!";
		}

		//Create window
		gWindow = SDL_CreateWindow( "WILSON VOLTEA A JAFETH IDA Y VUELTA 360Â°", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho_ventana, largo_ventana, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			cout<<"ERROR!!! NO SE CREO LA VENTANA"<<SDL_GetError();
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				cout<<"ERROR!!!"<<SDL_GetError() ;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					cout<<"ERROR!!! LA IMAGEN NO SE INICIALIZO"<<IMG_GetError();
					success = false;
				}

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					cout<<"ERROR!!! no se inicializo la musica"<<Mix_GetError();
					success = false;
				}
			}
		}
	}

	return success;
}

bool cargar()
{
	//Loading success flag
	bool success = true;

	//Load prompt texture
	if( !gPromptTexture.cargarArchivo( "Efectos_Musica/chanchy2.png" ) )
	{
		cout<<"ERROR fallo la carga de imagen";
		success = false;
	}

	//Load music
	gEverybody = Mix_LoadMUS( "Efectos_Musica/EVERYBODY.wav" );
	if( gEverybody == NULL )
	{
		cout<<"ERROR!! fallo la musica"<<Mix_GetError() ;
		success = false;
	}

	//Load sound effects
	gMenea = Mix_LoadWAV( "Efectos_Musica/MENEA.wav" );
	if( gMenea == NULL )
	{
		cout<<"ERROR!! fallo la musica"<<Mix_GetError() ;
		success = false;
	}

	gMedium = Mix_LoadWAV( "Efectos_Musica/medium.wav" );
	if( gMedium == NULL )
	{
		cout<<"ERROR!! fallo la musica"<<Mix_GetError() ;
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gPromptTexture.liberar();

	//Free the sound effects
	Mix_FreeChunk( gMenea );
	Mix_FreeChunk( gMedium );
	gMenea = NULL;
	gMedium = NULL;

	//Free the music
	Mix_FreeMusic( gEverybody);
	gEverybody = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		cout<<"Error al inicializar";
	}
	else
	{
		//Load media
		if( !cargar() )
		{
			cout<<"ERROR al cargar";
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Handle key press
					else if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
							//Play high sound effect
							case SDLK_1:
							Mix_PlayChannel( -1, gMenea, 0 );
							break;

							//Play medium sound effect
							case SDLK_2:
							Mix_PlayChannel( -1, gMedium, 0 );
							break;

							case SDLK_9:
							//If there is no music playing
							if( Mix_PlayingMusic() == 0 )
							{
								//Play the music
								Mix_PlayMusic( gEverybody, -1 );
							}
							//If music is being played
							else
							{
								//If the music is paused
								if( Mix_PausedMusic() == 1 )
								{
									//Resume the music
									Mix_ResumeMusic();
								}
								//If the music is playing
								else
								{
									//Pause the music
									Mix_PauseMusic();
								}
							}
							break;

							case SDLK_0:
							//Stop the music
							Mix_HaltMusic();
							break;
						}
					}
				}

				//Clear screen
				SDL_RenderClear( gRenderer );

				//Render prompt
				gPromptTexture.render( 0, 0 );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
*/




































//SOMBREAR Y (Alt+N)
//Para cambiar las variables

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Box2D/Box2D.h>
<<<<<<< HEAD
#include <stdio.h>
#include <string>
#include <stdlib.h>

#define DEGTORAD 0.0174532925199432957f

using namespace std;

bool iniciar();
bool iniciarGL();
void cerrar();
void render(b2World &world,float32 timeSte, int32 velocityIteracion, int32 positionIteracion,b2Body* Cuerpo1_pajaro,b2Body* Cuerpo2_chanchy,b2Body* Suelo,b2Body* Plataforma1);

SDL_Window *ventana = NULL; //Creamos la ventana
SDL_GLContext glcontext;//Crea el contexto dentro de sdl

int deteccion = 0;


int main(int argc, char*argv[]){
    int i=0;
    if(iniciar()){
        //------CREACION DEL MUNDO--------
        b2Vec2 gravity(0.0f,-10.0f);//Definir la gravedad
        b2World world(gravity); //Crear el mundo con parametro de la gravedad

//---------------------------------CREACION DEL PAJARO----------------------------------------------------------
        b2BodyDef Caja1;//Creamos el objeto

        Caja1.position.Set(-550.0f,-249.0f);//Colocando la posicion del cuerpo dinamico -249
        Caja1.type=b2_dynamicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* pajaro=world.CreateBody(&Caja1);//Coloca al cuerpo dinamico en el Mundo

        b2PolygonShape Poligono1; //Creacion de un poligono
        Poligono1.SetAsBox(30.0f,30.f); //TAMAÃ‘OS
=======
#include<stdio.h>

using namespace std;

bool iniciar();
bool iniciarGL();
void cerrar();
void render(b2World &world,float32 timeSte, int32 velocityIteracion, int32 positionIteracion,b2Body* Cuerpo1,b2Body* Cuerpo2,/*b2Body* Cuerpo3,*/b2Body* Suelo);

SDL_Window *w = NULL; //Creamos la ventana
SDL_GLContext glcontext;//Crea el oontexto dentro de sdl


int main(int argc, char*argv[]){
    if(iniciar()){
        //------CREACION DEL MUNDO--------
        b2Vec2 gravity(0.0f,-10.0f);//Definir la gravedad
        b2World world(gravity); //Crear el mundo con parametro de la gravedad


//--------------------------------------CREACION DEL CUADRADO----------------------------------------------------------
        b2BodyDef Caja1;//Creamos el objeto
        Caja1.position.Set(-400.0f,-200.0f);//Colocando la posicion del cuerpo dinamico -249
        Caja1.type=b2_dynamicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* Cuerpo1=world.CreateBody(&Caja1);//Coloca al cuerpo dinamico en el Mundo

        b2PolygonShape Poligono1; //Creacion de un poligono
        Poligono1.SetAsBox(50.0f,50.f); //TAMAÑOS
>>>>>>> c369de4e46f00d1ffd117f4cbed9e7569d3230f4

        b2FixtureDef Accesorios1;
        Accesorios1.filter.groupIndex=-8;
        Accesorios1.shape=&Poligono1;
<<<<<<< HEAD
        Accesorios1.density=3.0f;
        Accesorios1.restitution=1.0f;
        Accesorios1.friction=3.0f;
        pajaro->CreateFixture(&Accesorios1);

        b2MassData masa;
        masa.mass=30.0f;
        pajaro->SetMassData(&masa);

        pajaro->ApplyLinearImpulse(b2Vec2 (999999999.0f,999999999.0f),pajaro->GetWorldCenter(),true);

//------------------------------CREACION DEL CHANCHYS--------------------------------------------------------

        b2BodyDef Caja2;//Creamos el objeto
        Caja2.position.Set(105.0f,6.0f);//Colocando la posicion del cuerpo dinamico -249.0f
        Caja2.type=b2_dynamicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* chanchy=world.CreateBody(&Caja2);//Coloca al cuerpo dinamico en el Mundo

        b2PolygonShape Poligono2; //Creacion de un poligono
        Poligono2.SetAsBox(50.0f,50.0f); //creacion de un poligono en el sueloe
        Accesorios1.isSensor = true;

        b2FixtureDef Accesorio2;
        Accesorio2.shape=&Poligono2;
        Accesorio2.density=0.0f;
        //Accesorio2.restitution=1.0f;
        Accesorio2.friction=2.5f;
        b2Fixture* sensor1 = chanchy->CreateFixture(&Accesorio2);
        sensor1->SetUserData( (void*)3 );
/*
        b2ContactListener contacto1;
        b2Contact contacto2;
        fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              numFootContacts++;
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              numFootContacts++;
      }

      void EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              numFootContacts--;
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              numFootContacts--;
      }*/
        //fixtureUserData = contacto->GetFixtureA()->GetUserData();

        //chanchy->CreateFixture(&Accesorio2);

        b2MassData masa2;
        masa2.mass=3.0f;
        chanchy->SetMassData(&masa2);

//----------------------CREACION PLATAFORMAS----------------------------------------------------------------
        b2BodyDef Tabla1;//Creamos el objeto

        Tabla1.position.Set(90.0,0.0f);//Colocando la posicion del cuerpo dinamico
        Tabla1.type=b2_kinematicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* Plataforma1=world.CreateBody(&Tabla1);//Coloca al cuerpo dinamico en el Mundo

        b2PolygonShape Poli1;
        Poli1.SetAsBox(50.0f,6.0f);

        b2FixtureDef AcceP1;
        AcceP1.filter.groupIndex=-8;
        AcceP1.shape=&Poli1;
        AcceP1.density=0.0f;
        AcceP1.friction=2.0f;
        //AcceP1.restitution=34.0f;
        Plataforma1->CreateFixture(&AcceP1);

        Plataforma1->SetLinearVelocity( b2Vec2( 0, 15 ) ); //move right 1 unit per second


//---------------------------------------CUERPO SUELO --------------------------------------------------------------
        b2BodyDef Rectangulo;//Creamos el objeto
        Rectangulo.type=b2_staticBody;//Volvemos el  objeto estatico en obetejo dinamico
        Rectangulo.position.Set(0.0f,-300.0f);//Colocando la posicion del cuerpo dinamico
=======
        Accesorios1.density=10.0f;
        Accesorios1.restitution=0.6f;

        b2MassData masaa;
        masaa.mass=30.0f;

        Cuerpo1->SetMassData(&masaa);
        Cuerpo1->CreateFixture(&Accesorios1); //CUERPO1 B2BODY




        //float impulse=Cuerpo1->GetMass()*10;
        //Cuerpo1->ApplyLinearImpulse(b2Vec2(0,impulse),Cuerpo1->GetWorldCenter(),true);

//------------------------------CREACION DEL SEGUNDO CUADRADO--------------------------------------------------------

        b2BodyDef Caja2;//Creamos el objeto
        Caja2.position.Set(200.0f,-200.0f);//Colocando la posicion del cuerpo dinamico -249.0f
        Caja2.type=b2_dynamicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* Cuerpo2=world.CreateBody(&Caja2);//Coloca al cuerpo dinamico en el Mundo

        b2PolygonShape Poligono2; //Creacion de un poligono
        Poligono2.SetAsBox(50.0f,50.0f); //creacion de un poligono en el sueloe

        b2FixtureDef Accesorios2;
        Accesorios2.shape=&Poligono2;
        Accesorios2.density=999999999999.0f;
        Accesorios2.restitution=0.6f;

        Cuerpo2->CreateFixture(&Accesorios2);


//-----------------------------CREACION DEL TERCER CUERPO----------------------------------------------------------------
       /* b2BodyDef Caja3;//Creamos el objeto
        Caja3.position.Set(90.0,0.0f);//Colocando la posicion del cuerpo dinamico
        Caja3.type=b2_dynamicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* Cuerpo3=world.CreateBody(&Caja3);//Coloca al cuerpo dinamico en el Mundo

        b2CircleShape Circulo;


        Cuerpo2->CreateFixture(&Poligono3,0.0f);
        b2FixtureDef Accesorios3;
        Accesorios2.shape=&Poligono3;
        Accesorios2.density=0.0f;
        Accesorios2.restitution=0.0f;

*/
//---------------------------------------CUERPO ESTATICO--------------------------------------------------------------
        b2BodyDef Rectangulo;//Creamos el objeto
        Rectangulo.type=b2_staticBody;//Volvemos el  objeto estatico en obetejo dinamico
        Rectangulo.position.Set(0.0f,-300.0f);//Colocando la posicion del cuerpo dinamico
>>>>>>> c369de4e46f00d1ffd117f4cbed9e7569d3230f4
        b2Body* Suelo=world.CreateBody(&Rectangulo);//Coloca al cuerpo dinamico en el Mundo

        b2PolygonShape Terreno; //Creacion de un poligono
        Terreno.SetAsBox(800.0f,1.0f); //creacion de un poligono en el suelo

        Suelo->CreateFixture(&Terreno ,0.0f);

<<<<<<< HEAD
//-----------------------------------LIMITES DE LA VENTANA-------------------------------------------------------
        b2BodyDef limites;
        limites.position.Set(-650, -350);
        b2Body *limites_ventana = world.CreateBody(&limites);

        b2EdgeShape posiciones;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &posiciones;
        posiciones.Set(b2Vec2(0.0f, 0.0f),b2Vec2(1300.0f, 0.0f ));
        limites_ventana->CreateFixture(&fixtureDef);
        posiciones.Set(b2Vec2(1300.0f , 0.0f),b2Vec2(1300.0f, 700.0f ));
        limites_ventana->CreateFixture(&fixtureDef);
        posiciones.Set(b2Vec2(1300.0f, 700.0f),b2Vec2(0.0f, 700.0f));
        limites_ventana->CreateFixture(&fixtureDef);
        posiciones.Set(b2Vec2(0.0f, 700.0f),b2Vec2(0.0f, 0.0f));
        limites_ventana->CreateFixture(&fixtureDef);



//---------------------------------------------ITERACIONES---------------------------------------------------------
        float32 timeSte = 1.0f/60.0f;

        int32 velocityIteracion=18;
        int32 positionIteracion=3;
//------------------------------------------------------------------------------------------------------
        bool salir=false;
        SDL_Event jordan;
        while(!salir){
            while(SDL_PollEvent(&jordan) != 0){//el prÃ³ximo evento se elimina de la cola y se almacena en el SDL_Event.
                if(jordan.type == SDL_QUIT){//DEVUELVE EL TIPO DE DATO
                    salir = true;
                }
                else if( jordan.type == SDL_KEYDOWN ){
                    switch( jordan.key.keysym.sym )
						{
							case SDLK_RIGHT://DERECHO
                            chanchy->ApplyLinearImpulse(b2Vec2 (999999999.0f,99999),chanchy->GetWorldCenter(),true);
							break;
							case SDLK_LEFT://IZQUIERDA
							chanchy->ApplyLinearImpulse(b2Vec2 (-99999999.0f,999999.0f),chanchy->GetWorldCenter(),true);
							break;
							case SDLK_UP://ARRIBA
							if (chanchy != Plataforma1){
                            chanchy->ApplyLinearImpulse(b2Vec2 (9999.0f,99999.0f),chanchy->GetWorldCenter(),true);}
							break;
							case SDLK_DOWN://ABAJO
							chanchy->ApplyLinearImpulse(b2Vec2 (-99999.0f,-9999999.0f),chanchy->GetWorldCenter(),true);
							break;
							default:
							chanchy->ApplyLinearImpulse(b2Vec2 (-99999.0f,-9999999.0f),chanchy->GetWorldCenter(),false);
							break;
						}
                }
            }
            render(world,timeSte,velocityIteracion,positionIteracion,pajaro,chanchy,Suelo,Plataforma1);
            SDL_GL_SwapWindow(ventana);//CAMBIO DE VENTANA
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
        ventana = SDL_CreateWindow("CHANCHY BIRDS",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1300,700,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
        if(ventana == NULL){
            cout<<"Error!!!"<<endl;
            return false;
        }
        glcontext = SDL_GL_CreateContext(ventana);
        if(glcontext == NULL){
            cout<<"ERROR!!!"<<endl;
            return false;
        }
        if(!iniciarGL()){
            cout<<"ERROR!!!"<<endl;
            return false;
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            cout<<"ERROR!!! no se inicializo la musica"<<endl;
            return false;
        }
    }
    return true;
}

bool iniciarGL(){
    GLenum error = GL_NO_ERROR;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-650,650,-350,350,-150,150);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//CARGA LA mATRIZ iDENTIDAD
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    glClearColor(0.f,0.f,0.f,1.f);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    return true;
}

void cerrar(){
    SDL_DestroyWindow(ventana);//DESTRUYE LA VENTANA
    ventana = NULL;
    SDL_Quit();
}

void render(b2World &world,float32 timeSte, int32 velocityIteracion, int32 positionIteracion,b2Body* Cuerpo1_pajaro, b2Body* Cuerpo2_chanchy, b2Body* Suelo,b2Body* Plataforma1)
{

    world.Step(timeSte,velocityIteracion, positionIteracion);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-2.0);

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(Suelo->GetPosition().x-650.f,Suelo->GetPosition().y+1.f,0.f);
        glVertex3f(Suelo->GetPosition().x-650.f,Suelo->GetPosition().y-1.f,0.f);
        glVertex3f(Suelo->GetPosition().x+650.f,Suelo->GetPosition().y-1.f,0.f);
        glVertex3f(Suelo->GetPosition().x+650.f,Suelo->GetPosition().y+1.f,0.f);
=======
//---------------------------------------------ITERACIONES---------------------------------------------------------
        float32 timeSte = 1.0f/60.0f;

        int32 velocityIteracion=8;
        int32 positionIteracion=3;
//------------------------------------------------------------------------------------------------------
        bool salir=false;
        SDL_Event jordan;
        while(!salir){
            while(SDL_PollEvent(&jordan) != 0){//el próximo evento se elimina de la cola y se almacena en el SDL_Event.
                if(jordan.type == SDL_QUIT){//DEVUELVE EL TIPO DE DATO
                    salir = true;
                }
            }
            render(world,timeSte,velocityIteracion,positionIteracion,Cuerpo1,Cuerpo2,Suelo);

            SDL_GL_SwapWindow(w);//CAMBIO DE VENTANA
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
        w = SDL_CreateWindow("CHANCHY BIRDS",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1300,700,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
        if(w == NULL){
            cout<<"Error."<<endl;
            return false;
        }
        glcontext = SDL_GL_CreateContext(w);
        if(glcontext == NULL){
            cout<<"ERROR!!!"<<endl;
            return false;
        }
        if(!iniciarGL()){
            cout<<"ERROR!!!"<<endl;
            return false;
        }
    }
    return true;
}

bool iniciarGL(){
    GLenum error = GL_NO_ERROR;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-650,650,-350,350,-150,150);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//CARGA LA mATRIZ iDENTIDAD
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    glClearColor(0.f,0.f,0.f,1.f);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    return true;
}

void cerrar(){
    SDL_DestroyWindow(w);//DESTRUYE LA VENTANA
    w = NULL;
    SDL_Quit();
}

void render(b2World &world,float32 timeSte, int32 velocityIteracion, int32 positionIteracion,b2Body* CUERPO, b2Body* CUERPO_CUADRADO, b2Body* body)
{

    world.Step(timeSte,velocityIteracion, positionIteracion);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-2.0);

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(body->GetPosition().x-650.f,body->GetPosition().y+1.f,0.f);
        glVertex3f(body->GetPosition().x-650.f,body->GetPosition().y-1.f,0.f);
        glVertex3f(body->GetPosition().x+650.f,body->GetPosition().y-1.f,0.f);
        glVertex3f(body->GetPosition().x+650.f,body->GetPosition().y+1.f,0.f);
>>>>>>> c369de4e46f00d1ffd117f4cbed9e7569d3230f4
    glEnd();



     glBegin(GL_QUADS);
        glColor3f(1.0,0.0,1.0);
        glVertex3f(Cuerpo1_pajaro->GetPosition().x-30.f,Cuerpo1_pajaro->GetPosition().y+30.f,0.f);
        glVertex3f(Cuerpo1_pajaro->GetPosition().x-30.f,Cuerpo1_pajaro->GetPosition().y-30.f,0.f);
        glVertex3f(Cuerpo1_pajaro->GetPosition().x+30.f,Cuerpo1_pajaro->GetPosition().y-30.f,0.f);
        glVertex3f(Cuerpo1_pajaro->GetPosition().x+30.f,Cuerpo1_pajaro->GetPosition().y+30.f,0.f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,0.0);
        glVertex3f(Cuerpo2_chanchy->GetPosition().x-50.f,Cuerpo2_chanchy->GetPosition().y+50.f,0.f);
        glVertex3f(Cuerpo2_chanchy->GetPosition().x-50.f,Cuerpo2_chanchy->GetPosition().y-50.f,0.f);
        glVertex3f(Cuerpo2_chanchy->GetPosition().x+50.f,Cuerpo2_chanchy->GetPosition().y-50.f,0.f);
        glVertex3f(Cuerpo2_chanchy->GetPosition().x+50.f,Cuerpo2_chanchy->GetPosition().y+50.f,0.f);
    glEnd();

    glBegin(GL_QUADS);
        glColor4f(0.0,1.0,0.0,1.0);
        glVertex3f(Plataforma1->GetPosition().x-50.f,Plataforma1->GetPosition().y+6.f,0.f);
        glVertex3f(Plataforma1->GetPosition().x-50.f,Plataforma1->GetPosition().y-6.f,0.f);
        glVertex3f(Plataforma1->GetPosition().x+50.f,Plataforma1->GetPosition().y-6.f,0.f);
        glVertex3f(Plataforma1->GetPosition().x+50.f,Plataforma1->GetPosition().y+6.f,0.f);
    glEnd();

}

