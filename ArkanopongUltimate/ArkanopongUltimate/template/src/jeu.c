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

void IABarre(Barre* barre, Ball* balle1, Ball* balle2){
  Ball* nearestBall;
  nearestBall=balle1;
  if(sqrt((barre->posX-balle2->posX)*(barre->posX-balle2->posX)+(barre->posY-balle2->posY)*(barre->posX-balle2->posY)) < sqrt((barre->posX-balle2->posX)*(barre->posX-balle2->posX)+(barre->posY-balle2->posY)*(barre->posX-balle2->posY))){
    nearestBall=balle2;
  }
  if(nearestBall->posY<barre->posY){
    moveBarreLeft(barre);
  }
  else if(nearestBall->posY>barre->posY){
    moveBarreRight(barre);
  }
}



int victoire(PlayerTab* Joueurs, int IA, Son* son){
  /*IA = 1 si le joueur affronte l'IA*/
  GLuint ind;
  int victoire;
  if (Joueurs->players[0]->PDV == 0){
    if(IA == 1){
      ind=loadTexture("./textures/j1win.png");
      Mix_PlayChannel(-1, son->victoire, 0);
      victoire = 0;
    }
    else{
      ind=loadTexture("./textures/j2win.png");
      Mix_PlayChannel(-1, son->victoire, 0);
      victoire = 0;
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ind);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(200, 300);
      glTexCoord2f(0, 1);
      glVertex2f(200, 500);
      glTexCoord2f(1, 1);
      glVertex2f(800, 500);
      glTexCoord2f(1, 0);
      glVertex2f(800, 300);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_GL_SwapBuffers();
    SDL_Delay(1000);
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &ind);
    return 0;
  }
  else if (Joueurs->players[1]->PDV == 0){
    if(IA ==1){
      ind=loadTexture("./textures/iawin.png");
      Mix_PlayChannel(-1, son->victoire, 0);
      victoire = 2;
    }
    else{
      ind=loadTexture("./textures/j1win.png");
      Mix_PlayChannel(-1, son->victoire, 0);
      victoire = 0;
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ind);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(200, 300);
      glTexCoord2f(0, 1);
      glVertex2f(200, 500);
      glTexCoord2f(1, 1);
      glVertex2f(800, 500);
      glTexCoord2f(1, 0);
      glVertex2f(800, 300);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_GL_SwapBuffers();
    SDL_Delay(1000);
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &ind);
    return victoire;
  }
  else{
    return 1;
  }
}






int Game(const char *path, Mix_Music* fond, Son* son, Texture* texture, int IA, int musiqueOn, int sonOn, int BonusPris[3]){
  /*Si IA = 0, il y a deux joueurs, sinon une IA*/
  TabBrique * tab = iniTabBrique(path, *texture);
  BonusTab * tabBonus = iniBonusTab();
  int vict=0;
  int start = 0;

  PlayerTab* Joueurs = iniPlayerTab(2);

  int contG1=0, contD1=0, contG2=0, contD2=0;
  Barre * barreJ1 = iniBarre(1);
  Barre * barreJ2 = iniBarre(2);
  Ball * balleJ1 = iniBall (1);
  Ball * balleJ2 = iniBall (2);
  iniVitesse(balleJ1, 1);
  iniVitesse(balleJ2, 2);

  if(musiqueOn == 1){
    Mix_PlayMusic(fond, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME/4);
  }

  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /* Dessin */
    glClear(GL_COLOR_BUFFER_BIT);
    if(IA==0){
      if(contG1 == 1){
        moveBarreLeft(barreJ1);
      }
      if(contD1 == 1){
        moveBarreRight(barreJ1);
      }
    }
    else{
      IABarre(barreJ1, balleJ1, balleJ2);
    }
    if(contG2 == 1){
      moveBarreLeft(barreJ2);
    }
    if(contD2 == 1){
      moveBarreRight(barreJ2);
    }
    moveBalls(balleJ1, balleJ2, *barreJ1, *barreJ2, Joueurs, tab, tabBonus, son, sonOn);

    
    glColor3ub(255,255,255);
    drawBriqueTab(*tab);

    
    drawBarre(*barreJ1);
    drawBarre(*barreJ2);
    stopBonus(barreJ1);
    stopBonus(barreJ2);
    drawingBall(*balleJ1);
    drawingBall(*balleJ2);


    drawPDV(*(Joueurs->players[0]), *texture);
    drawPDV(*(Joueurs->players[1]), *texture);
    
    vict = victoire(Joueurs, IA, son);
    if(vict != 1){
      loop = 0;
    }


    gestionBonus(tabBonus,barreJ1, barreJ2, Joueurs, son, BonusPris);

    SDL_GL_SwapBuffers();

    if(start ==0){
      Start();
      start =1;
    }

   
    /* ****** */    

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        vict = 2;
        break;
      }
      
      switch(e.type) {          
        case SDL_KEYDOWN:
          if(e.key.keysym.sym == SDLK_a){ /*A pour gauche*/
            contG1=1;
          }
          if(e.key.keysym.sym == SDLK_z){ /*z pour droite*/
            contD1=1;
          }
          if(e.key.keysym.sym == SDLK_LEFT){ /*Flèche gaucge pour gauche*/
            contG2=1;
          }
          if(e.key.keysym.sym == SDLK_RIGHT){ /*Flèche droite pour droite*/
            contD2=1;
          }
          break;

        case SDL_KEYUP:
          if(e.key.keysym.sym == SDLK_a){ /*A pour gauche*/
            contG1=0;
          }
          if(e.key.keysym.sym == SDLK_z){ /*z pour droite*/
            contD1=0;
          }
          if(e.key.keysym.sym == SDLK_LEFT){ /*Flèche gaucge pour gauche*/
            contG2=0;
          }
          if(e.key.keysym.sym == SDLK_RIGHT){ /*Flèche droite pour droite*/
            contD2=0;
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
  

  Mix_FreeMusic(fond);
  freeTabBrique(tab);
  freePlayerTab(Joueurs);
  free(barreJ1);
  free(barreJ2);
  free(balleJ1);
  free(balleJ2);
  freeBonus(tabBonus);

  return vict;
}


int StoryModeKnight(Mix_Music* fond, Son* son, Texture* texture, int musiqueOn, int sonOn, int BonusPris[3]){
  int i;
  GLuint intro = loadTexture("textures/StoryModeKnight/intro.png");
  GLuint fin = loadTexture("textures/StoryModeKnight/fin.png");
  GLuint ennemi[5];
  ennemi[0] = loadTexture("textures/StoryModeKnight/ennemi1.png");
  ennemi[1] = loadTexture("textures/StoryModeKnight/ennemi2.png");
  ennemi[2] = loadTexture("textures/StoryModeKnight/ennemi3.png");
  ennemi[3] = loadTexture("textures/StoryModeKnight/ennemi4.png");
  ennemi[4] = loadTexture("textures/StoryModeKnight/ennemi5.png");
  GLuint texte[5];
  texte[0] = loadTexture("textures/StoryModeKnight/texte1.png");
  texte[1] = loadTexture("textures/StoryModeKnight/texte2.png");
  texte[2] = loadTexture("textures/StoryModeKnight/texte3.png");
  texte[3] = loadTexture("textures/StoryModeKnight/texte4.png");
  texte[4] = loadTexture("textures/StoryModeKnight/texte5.png");
  char* s[5];
  s[0]= "niveaux/knight/1.txt";
  s[1]= "niveaux/knight/2.txt";
  s[2]= "niveaux/knight/3.txt";
  s[3]= "niveaux/knight/4.txt";
  s[4]= "niveaux/knight/5.txt";
  glClear(GL_COLOR_BUFFER_BIT);
  drawSquare(100, 300, 600, 400, intro);
  SDL_GL_SwapBuffers();
  SDL_Delay(10000);
  glDeleteTextures(1, &intro);
  for(i=0; i<5; ++i){
    fond = Mix_LoadMUS("musiques/musique.mp3");
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(255,255,255);
    drawSquare(100, 400, 200, 200, ennemi[i]);
    drawSquare(400, 300, 300, 400, texte[i]);
    SDL_GL_SwapBuffers();
    SDL_Delay(10000);
    if(Game(s[i], fond, son, texture, 1, musiqueOn, sonOn, BonusPris)==2){
      return 0;
    }
  }
  glClear(GL_COLOR_BUFFER_BIT);
  drawSquare(100, 400, 600, 400, fin);
  SDL_GL_SwapBuffers();
  SDL_Delay(10000);
  glDeleteTextures(1, &(ennemi[0]));
  glDeleteTextures(1, &(ennemi[1]));
  glDeleteTextures(1, &(ennemi[2]));
  glDeleteTextures(1, &(ennemi[3]));
  glDeleteTextures(1, &(ennemi[4]));
  glDeleteTextures(1, &(texte[0]));
  glDeleteTextures(1, &(texte[1]));
  glDeleteTextures(1, &(texte[2]));
  glDeleteTextures(1, &(texte[3]));
  glDeleteTextures(1, &(texte[4]));
  glDeleteTextures(1, &fin);
  return 1;
}


int StoryModePrez(Mix_Music* fond, Son* son, Texture* texture, int musiqueOn, int sonOn, int BonusPris[3]){
  int i;
  GLuint intro = loadTexture("textures/StoryModePrez/intro.png");
  GLuint fin = loadTexture("textures/StoryModePrez/fin.png");
  GLuint ennemi[5];
  ennemi[0] = loadTexture("textures/StoryModePrez/ennemi1.png");
  ennemi[1] = loadTexture("textures/StoryModePrez/ennemi2.png");
  ennemi[2] = loadTexture("textures/StoryModePrez/ennemi3.png");
  ennemi[3] = loadTexture("textures/StoryModePrez/ennemi4.png");
  ennemi[4] = loadTexture("textures/StoryModePrez/ennemi5.png");
  GLuint texte[5];
  texte[0] = loadTexture("textures/StoryModePrez/texte1.png");
  texte[1] = loadTexture("textures/StoryModePrez/texte2.png");
  texte[2] = loadTexture("textures/StoryModePrez/texte3.png");
  texte[3] = loadTexture("textures/StoryModePrez/texte4.png");
  texte[4] = loadTexture("textures/StoryModePrez/texte5.png");
  char* s[5];
  s[0]= "niveaux/Prez/1.txt";
  s[1]= "niveaux/Prez/2.txt";
  s[2]= "niveaux/Prez/3.txt";
  s[3]= "niveaux/Prez/4.txt";
  s[4]= "niveaux/Prez/5.txt";
  glClear(GL_COLOR_BUFFER_BIT);
  drawSquare(100, 300, 600, 400, intro);
  SDL_GL_SwapBuffers();
  SDL_Delay(10000);
  glDeleteTextures(1, &intro);
  for(i=0; i<5; ++i){
    fond = Mix_LoadMUS("musiques/musiquePresident.mp3");
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(255,255,255);
    drawSquare(100, 400, 200, 200, ennemi[i]);
    drawSquare(400, 300, 300, 400, texte[i]);
    SDL_GL_SwapBuffers();
    SDL_Delay(10000);
    if(Game(s[i], fond, son, texture, 1, musiqueOn, sonOn, BonusPris)==2){
      return 0;
    }
  }
  glClear(GL_COLOR_BUFFER_BIT);
  drawSquare(100, 400, 600, 400, fin);
  SDL_GL_SwapBuffers();
  SDL_Delay(10000);
  glDeleteTextures(1, &(ennemi[0]));
  glDeleteTextures(1, &(ennemi[1]));
  glDeleteTextures(1, &(ennemi[2]));
  glDeleteTextures(1, &(ennemi[3]));
  glDeleteTextures(1, &(ennemi[4]));
  glDeleteTextures(1, &(texte[0]));
  glDeleteTextures(1, &(texte[1]));
  glDeleteTextures(1, &(texte[2]));
  glDeleteTextures(1, &(texte[3]));
  glDeleteTextures(1, &(texte[4]));
  glDeleteTextures(1, &fin);
  return 1;
}