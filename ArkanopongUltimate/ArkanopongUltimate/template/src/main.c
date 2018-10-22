#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_mixer.h>


#include "constante.h"
#include "objets/barre.h"
#include "SDLevent.h"
#include "objets/joueur.h"
#include "objets/brique.h"
#include "objets/bonus.h"
#include "objets/balle.h"
#include "jeu.h"
#include "menu.h"



/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;



int main(int argc, char** argv) {

  initialisationFen();

  int BonusPris[3]={1,1,0};
  GLuint indMenu[5];
  GLuint indStory[3];
  GLuint indDefi[3];
  GLuint indDefiIA[10];
  GLuint indDefi2J[10];
  GLuint indOption[16];

  loadTextureMenuP(indMenu);
  loadTextureStory(indStory);
  loadTextureDefi(indDefi);
  loadTextureDefiIA(indDefiIA);
  loadTextureDefi2J(indDefi2J);
  loadTextureOption(indOption);

  /*Son*/
  if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)==-1){
    fprintf(stderr, Mix_GetError());
    exit(EXIT_FAILURE);
  }
  Mix_AllocateChannels(6);

  Mix_Music *MenuP = Mix_LoadMUS("musiques/musiqueMenu.mp3");


  float x,y;
  int musiqueOn = 1;
  int sonOn = 1;

  MenuType menu=MENU;

  


  int loop = 1;
  while(loop) {
    if(Mix_PlayingMusic() == 0){
      if(musiqueOn == 1){
        Mix_PlayMusic(MenuP, -1);
        Mix_VolumeMusic(MIX_MAX_VOLUME/4);
      }
    }

    Uint32 startTime = SDL_GetTicks();

    /* Dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    /*if(contG1 == 1){
      moveBarreLeft(barreJ1);
    }
    if(contD1 == 1){
      moveBarreRight(barreJ1);
    }*/
   
    glColor3ub(255,255,255);
    if(menu == MENU){
      loadMenuP(indMenu);
    }
    if(menu == STORYMODE){
      loadStoryMode(indStory);
    }
    if(menu == DEFIMODE){
      loadDefi(indDefi);
    }
    if(menu == DEFIIA){
      loadDefiIA(indDefiIA);
    }
    if(menu == DEFI2J){
      loadDefi2J(indDefi2J);
    }
    if(menu == OPTION){
      loadOption(indOption, musiqueOn, sonOn, BonusPris);
    }

    SDL_GL_SwapBuffers();

   
    /* ****** */    

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
      
      x=0;
      y=0;

      switch(e.type) {  

        case SDL_MOUSEBUTTONUP:
          y= e.button.x;
          x= e.button.y;
          if(menu == MENU){
            if(120 < x && x < 300 && 100 < y && y < 900){
              menu = STORYMODE;
            }
            if(320 < x && x < 500 && 100 < y && y < 900){
              menu = DEFIMODE;
            }
            if(520 < x && x < 700 && 100 < y && y < 900){
              menu = OPTION;
            }
            if(720 < x && x < 780 && 800 < y && y < 950){
              loop = 0;
            }
          }
          else if(menu == STORYMODE){
            if(50 < x && x < 700 && 75 < y && y < 475){
              Mix_Music *fond = Mix_LoadMUS("musiques/musique.mp3");
              Son* son = iniSon(son);
              Texture* TEXTURE = iniTex("textures/modeKnight");
              StoryModeKnight(fond, son, TEXTURE, musiqueOn, sonOn, BonusPris);
            }
            if(50 < x && x < 700 && 550 < y && y < 950){
              Mix_Music *fond = Mix_LoadMUS("musiques/musiquePresident.mp3");
              Son* son = iniSon(son);
              Texture* TEXTURE = iniTex("textures/modePrez");
              StoryModePrez(fond, son, TEXTURE, musiqueOn, sonOn, BonusPris);
            }
            if(720 < x && x < 780 && 800 < y && y < 950){
              menu = MENU;
            }
          }
          else if(menu == DEFIMODE){
            if(50 < x && x < 700 && 75 < y && y < 475){
              menu = DEFIIA;
            }
            if(50 < x && x < 700 && 550 < y && y < 950){
              menu = DEFI2J;
            }
            if(720 < x && x < 780 && 800 < y && y < 950){
              menu = MENU;
            }
          }
          else if(menu == DEFIIA){
            Mix_Music *fond = Mix_LoadMUS("musiques/musiqueDefiIA.mp3");
            Son* son = iniSon(son);
            Texture* TEXTURE = iniTex("textures/modeDefiIA");
            if(50 < x && x < 230 && 75 < y && y < 275){
              Game("niveaux/defiIA/1.txt", fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(50 < x && x < 230 && 300 < y && y < 500){
              Game("niveaux/defiIA/2.txt", fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(50 < x && x < 230 && 525 < y && y < 725){
              Game("niveaux/defiIA/3.txt", fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(50 < x && x < 230 && 750 < y && y < 950){
              Game("niveaux/defiIA/4.txt", fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(275 < x && x < 275+180 && 75 < y && y < 275){
              Game("niveaux/defiIA/5.txt", fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(275 < x && x < 275+180 && 300 < y && y < 500){
              Game("niveaux/defiIA/6.txt", fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(275 < x && x < 275+180 && 525 < y && y < 725){
              Game("niveaux/defiIA/7.txt", fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(275 < x && x < 275+180 && 750 < y && y < 950){
              Game("niveaux/defiIA/8.txt", fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(500 < x && x < 700 && 300 < y && y < 700){
              char cheminIA[80]={};
              printf("Indiquez le chemin du mode à essayer. \n");
              scanf("%s\n", cheminIA);
              Game(cheminIA, fond, son, TEXTURE, 1, musiqueOn, sonOn, BonusPris);
            }
            if(720 < x && x < 780 && 800 < y && y < 950){
              menu = DEFIMODE;
            }
        
          }
          else if(menu == DEFI2J){
            Mix_Music *fond = Mix_LoadMUS("musiques/musiqueDefi2J.mp3");
            Son* son = iniSon(son);
            Texture* TEXTURE = iniTex("textures/modeDefi2J");
            if(50 < x && x < 230 && 75 < y && y < 275){
              Game("niveaux/defi2J/1.txt", fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(50 < x && x < 230 && 300 < y && y < 500){
              Game("niveaux/defi2J/2.txt", fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(50 < x && x < 230 && 525 < y && y < 725){
              Game("niveaux/defi2J/3.txt", fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(50 < x && x < 230 && 750 < y && y < 950){
              Game("niveaux/defi2J/4.txt", fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(275 < x && x < 275+180 && 75 < y && y < 275){
              Game("niveaux/defi2J/5.txt", fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(275 < x && x < 275+180 && 300 < y && y < 500){
              Game("niveaux/defi2J/6.txt", fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(275 < x && x < 275+180 && 525 < y && y < 725){
              Game("niveaux/defi2J/7.txt", fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(275 < x && x < 275+180 && 750 < y && y < 950){
              Game("niveaux/defi2J/8.txt", fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(500 < x && x < 700 && 300 < y && y < 700){
              char chemin2J[80]={};
              printf("Indiquez le chemin du mode à essayer. \n");
              scanf("%s\n", chemin2J);
              Game(chemin2J, fond, son, TEXTURE, 0, musiqueOn, sonOn, BonusPris);
            }
            if(720 < x && x < 780 && 800 < y && y < 950){
              menu = DEFIMODE;
            }
          }
          else if(menu == OPTION){
            if(50 < x && x < 150 && 600 < y && y < 700){
              if(Mix_PausedMusic() == 1){
                Mix_ResumeMusic();
              }
              musiqueOn = 1;
            }
            if(50 < x && x < 150 && 750 < y && y < 850){
              musiqueOn = 0;
              if(Mix_PlayingMusic() == 1){
                Mix_PauseMusic();
              }
            }
            if(200 < x && x < 300 && 600 < y && y < 700){
              sonOn = 1;
            }
            if(200 < x && x < 300 && 750 < y && y < 850){
              sonOn = 0;
            }
            if(500 < x && x < 600 && 300 < y && y < 400){
              if(BonusPris[1] == 1 && BonusPris[2] == 1){
                BonusPris[2] = 0;
              }
              BonusPris[0] = 1;
            }
            if(500 < x && x < 600 && 450 < y && y < 550){
              if(BonusPris[0] == 1 && BonusPris[2] == 1){
                BonusPris[0] = 0;
              }
              BonusPris[1] = 1;
            }
            if(500 < x && x < 600 && 600 < y && y < 700){
              if(BonusPris[0] == 1 && BonusPris[1] == 1){
                BonusPris[1] = 0;
              }
              BonusPris[2] = 1;
            }
            if(720 < x && x < 780 && 800 < y && y < 950){
              menu = MENU;
            }
          }
          break;            
          
        default:
          break;
      }
    }
    
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  Mix_FreeMusic(MenuP);
  freeTextureMenuP(indMenu);
  freeTextureStory(indStory);
  freeTextureDefi(indDefi);
  freeTextureDefiIA(indDefiIA);
  freeTextureDefi2J(indDefi2J);
  freeTextureOption(indOption);

  Mix_CloseAudio();
  SDL_Quit();

  return EXIT_SUCCESS;
}