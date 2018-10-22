#include "constante.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "objets/barre.h"
#include "SDLevent.h"
#include "objets/brique.h"
#include "objets/joueur.h"
#include "objets/bonus.h"
#include "objets/balle.h"




void iniVitesse(Ball* ball, int player){
  srand(time(NULL));
  int direction = rand() % 2;
  if (player == 1){ 
    ball->vitX = 5.0;
    if(direction == 0){
      ball->vitY = 5.0;
    }
    else {
      ball->vitY = -5.0;
    }
  }
  else{
    ball->vitX = -5.0;
    if(direction == 0){
      ball->vitY = 5.0;
    }
    else {
      ball->vitY = -5.0;
    }
  }
}

Ball *iniBall (int last_player) {
  Ball* ball = malloc(sizeof(Ball));
  if (ball == NULL){
    fprintf(stderr, "Echec de l'allocation de la balle.\n");
    exit(EXIT_FAILURE);
  }
  if (last_player == 1){ 
    ball->posX = 1.0*WINDOW_HEIGHT/8;
    ball->posY = 1.0*WINDOW_WIDTH/2;
    ball-> radius = 10;
    ball->last_player = last_player;
  }
  
  else{
    ball->posX = 1.0*WINDOW_HEIGHT-1.0*WINDOW_HEIGHT/8;
    ball->posY = 1.0*WINDOW_WIDTH/2;;
    ball->vitX = 0;
    ball->vitY = 0;
    ball-> radius = 10;
    ball->last_player = last_player;
  }
  return ball;
}
    

void drawingBall(Ball ball) {
  int nbDivisionCircle = 50;
  int i;
  float x, y;
  glBegin(GL_POLYGON);
  for(i=0; i < nbDivisionCircle; i++) {
    x = ball.radius*cos(i*2*M_PI/nbDivisionCircle);
    y = ball.radius*sin(i*2*M_PI/nbDivisionCircle);
    /*glTexCoord2f(x, y);*/
    glVertex2f(ball.posY+y,ball.posX+x);
  }
  glEnd();
}

void collision2(Ball *ball1, Ball *ball2, Son* son, int sonOn){
  float distance = sqrt((ball1->posX-ball2->posX)*(ball1->posX-ball2->posX) + (ball1->posY-ball2->posY)*(ball1->posY-ball2->posY));
  if (distance<=2*ball1->radius +3.0 && distance>=2*ball1->radius - 3.0){
    ball1->vitX = -ball1->vitX;
    ball2->vitX = -ball2->vitX;
    if (sonOn == 1){
      Mix_PlayChannel(-1, son->rebond, 0);
    }
  }
}



void collision1(Ball *ball, Barre barre1, Barre barre2, PlayerTab* Joueurs, TabBrique* tab, BonusTab* bonustab, Son* son, int sonOn){
  srand(time(NULL));
  int i;
  int indBrique;
  float x, y;
  int nbDivisionCircle = 50;
  for(i=0; i < nbDivisionCircle; i++) {
      x = ball->radius*cos(i*2*M_PI/nbDivisionCircle);
      y = ball->radius*sin(i*2*M_PI/nbDivisionCircle);
      if((ball->posY+y<5.0 && ball->vitY<0) || (ball->posY+y > WINDOW_WIDTH-5.0 && ball->vitY>0)){ /*Contact avec les bords*/
        ball->vitY = -ball->vitY;
        if (sonOn == 1){
          Mix_PlayChannel(-1, son->rebond, 0);
        }
      }

      /*Collision avec les briques*/
      indBrique = presenceBrique(ball->posX+x, ball->posY+y, *tab);
      if(indBrique != -1){

        /*gestion de l'endroit avec lequel la balle rentre en contact*/
        
        if ((ball->posX+x >= tab->briqueTab[indBrique]->posX-5.0 && ball->posX+x <= tab->briqueTab[indBrique]->posX+5.0 && ball->vitX > 0) ||  (ball->posX+x >= tab->briqueTab[indBrique]->posX + tab->briqueTab[indBrique]->haut - 5.0 && ball->posX+x <= tab->briqueTab[indBrique]->posX+tab->briqueTab[indBrique]->haut+5.0 && ball->vitX < 0)){
          ball->vitX = -ball->vitX;
        }
        else if ((ball->posY+y >= tab->briqueTab[indBrique]->posY-5.0 && ball->posY+y <= tab->briqueTab[indBrique]->posY+5.0 && ball->vitY > 0) ||  (ball->posY+y >= tab->briqueTab[indBrique]->posY + tab->briqueTab[indBrique]->larg - 5.0 && ball->posY+y <= tab->briqueTab[indBrique]->posY+tab->briqueTab[indBrique]->larg+5.0 && ball->vitY < 0)){
          ball->vitY = -ball->vitY;
        }
        if (sonOn == 1){
          Mix_PlayChannel(-1, son->rebond, 0);
        }


        /*Gestion du type de la brique*/
        if(tab->briqueTab[indBrique]->type != 1){
          tab->briqueTab[indBrique]->etat -= 1;
        }
        if(tab->briqueTab[indBrique]->type == 2){
          int bonus = rand() % 2;
          if(bonus == 0){
            aujoutBonusTab(bonustab, iniBonus(tab->briqueTab[indBrique]->posX+(tab->briqueTab[indBrique]->haut)/2.0, tab->briqueTab[indBrique]->posY + (tab->briqueTab[indBrique]->larg)/2.0, 1, ball->last_player));
          }
          else{
            aujoutBonusTab(bonustab, iniBonus(tab->briqueTab[indBrique]->posX+(tab->briqueTab[indBrique]->haut)/2.0, tab->briqueTab[indBrique]->posY + (tab->briqueTab[indBrique]->larg)/2.0, 2, 3-ball->last_player));
          }
        }
        if(tab->briqueTab[indBrique]->type == 3){
          int bonus = rand() % 2;
          if(bonus == 0){
            aujoutBonusTab(bonustab, iniBonus(tab->briqueTab[indBrique]->posX+(tab->briqueTab[indBrique]->haut)/2.0, tab->briqueTab[indBrique]->posY + (tab->briqueTab[indBrique]->larg)/2.0, 3, ball->last_player));
          }
          else{
            aujoutBonusTab(bonustab, iniBonus(tab->briqueTab[indBrique]->posX+(tab->briqueTab[indBrique]->haut)/2.0, tab->briqueTab[indBrique]->posY + (tab->briqueTab[indBrique]->larg)/2.0, 4, 3-ball->last_player));
          }
        }
      }

      /*Sortie du terrain*/
      if((ball->posX+x<0.0 && ball->vitX<0)){
        modifPV(Joueurs, 0, 0);
        ball->posX = 1.0*WINDOW_HEIGHT/8;
        ball->posY = 1.0*WINDOW_WIDTH/2;
        iniVitesse(ball, 1);
        if (sonOn == 1){
          Mix_PlayChannel(-1, son->tombe, 0);
        }
        
      }
      if((ball->posX+x > WINDOW_HEIGHT*1.0 && ball->vitX>0)){
        modifPV(Joueurs, 1, 0);
        ball->posX = 1.0*WINDOW_HEIGHT-1.0*WINDOW_HEIGHT/8;
        ball->posY = 1.0*WINDOW_WIDTH/2;;
        iniVitesse(ball, 2);
        if (sonOn == 1){
          Mix_PlayChannel(-1, son->tombe, 0);
        }
      }

      /*Contact avec les barres*/
      if((ball->posX+x<barre1.posX+2.0 && ball->posX+x>barre1.posX-2.0 && ball->posY+y<barre1.posY+barre1.rayon+2.0 && ball->posY+y>barre1.posY-barre1.rayon-2.0 && ball->vitX<0)){
        ball->vitX = -ball->vitX;
        ball->last_player = 1;
        if (sonOn == 1){
          Mix_PlayChannel(-1, son->rebond, 0);
        }
      }
      if((ball->posX+x<barre2.posX+2.0 && ball->posX+x>barre2.posX-2.0 && ball->posY+y<barre2.posY+barre2.rayon+2.0 && ball->posY+y>barre2.posY-barre2.rayon-2.0 && ball->vitX>0)){
        ball->vitX = -ball->vitX;
        ball->last_player = 2;
        if (sonOn == 1){
          Mix_PlayChannel(-1, son->rebond, 0);
        }
      }
    }
}

void moveBall(Ball *balle, Barre barre1, Barre barre2, PlayerTab* Joueurs, TabBrique* tab, BonusTab *bonustab, Son* son, int sonOn){
  collision1(balle, barre1, barre2, Joueurs, tab, bonustab, son, sonOn);
  balle->posX = balle->posX + balle->vitX;
  balle->posY = balle->posY + balle->vitY;
}

void moveBalls(Ball *ball1, Ball *ball2, Barre barre1, Barre barre2, PlayerTab* Joueurs, TabBrique* tab, BonusTab *bonustab, Son* son, int sonOn){
  collision1(ball1, barre1, barre2, Joueurs, tab, bonustab, son, sonOn);
  collision1(ball2, barre1, barre2, Joueurs, tab, bonustab, son, sonOn);
  collision2(ball1, ball2, son, sonOn);
  ball1->posX = ball1->posX + ball1->vitX;
  ball1->posY = ball1->posY + ball1->vitY;
  ball2->posX = ball2->posX + ball2->vitX;
  ball2->posY = ball2->posY + ball2->vitY;
}
