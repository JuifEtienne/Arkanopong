#include "constante.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "objets/barre.h"
#include "SDLevent.h"
#include "objets/joueur.h"
#include "objets/bonus.h"

Bonus *iniBonus (float posX, float posY, int effet, int last_player) {
	Bonus* bonus = malloc(sizeof(Bonus));
  if (bonus == NULL){
    fprintf(stderr, "Echec de l'allocation du bonus.\n");
    exit(EXIT_FAILURE);
 	}
  bonus-> etat = 1;
 	bonus->posX = posX;
  bonus->posY = posY;
  bonus-> radius = 10;
	bonus -> effet = effet;

  if (last_player == 1){ 
    bonus->vitX = -4.0;
    bonus->last_player = last_player;
  }
  
  else{
    bonus->vitX = 4.0;
    bonus->last_player = last_player;
  }
  return bonus;
}

void drawingBonus(Bonus bonus) {
  int nbDivisionCircle = 50;
  int i;
  float x, y;
  if(bonus.etat == 1){
    glBegin(GL_POLYGON);
    for(i=0; i < nbDivisionCircle; i++) {
      x = bonus.radius*cos(i*2*M_PI/nbDivisionCircle);
      y = bonus.radius*sin(i*2*M_PI/nbDivisionCircle);
      /*glTexCoord2f(x, y);*/
      glVertex2f(bonus.posY+y,bonus.posX+x);
    }
    glEnd();
  }
}

void moveBonus(Bonus *bonus, PlayerTab* Joueurs){
  bonus->posX = bonus->posX + bonus->vitX;
}


void collisionBonus(Bonus *bonus, Barre* barre1, Barre* barre2, PlayerTab* Joueurs, Son* son, int BonusPris[3]){
  int i;
  float x, y;
  int nbDivisionCircle = 50;
  for(i=0; i < nbDivisionCircle; i++) {
      x = bonus->radius*cos(i*2*M_PI/nbDivisionCircle);
      y = bonus->radius*sin(i*2*M_PI/nbDivisionCircle);

      /*Sortie du terrain*/
      if((bonus->posX+x<0.0 && bonus->vitX<0)){
        bonus -> etat = 0;
      }
      if((bonus->posX+x > WINDOW_HEIGHT*1.0 && bonus->vitX>0)){
        bonus -> etat = 0;
      }
      /*Contact avec les barres*/
      if((bonus->posX+x<barre1->posX+2.0 && bonus->posX+x>barre1->posX-2.0 && bonus->posY+y<barre1->posY+barre1->rayon+2.0 && bonus->posY+y>barre1->posY-barre1->rayon-2.0 && bonus->vitX<0)){
        bonus-> etat = 0;
        BonusEffet(*bonus, barre1, son, BonusPris);
      }
      if((bonus->posX+x<barre2->posX+2.0 && bonus->posX+x>barre2->posX-2.0 && bonus->posY+y<barre2->posY+barre2->rayon+2.0 && bonus->posY+y>barre2->posY-barre2->rayon-2.0 && bonus->vitX>0)){
        bonus-> etat = 0;
        BonusEffet(*bonus, barre2, son, BonusPris);
      }
    }
}

void BonusEffet(Bonus bonus, Barre *barre, Son* son, int BonusPris[3]) {
  barre->temps = 500;
  int numBonus = 0;
  if (BonusPris[0] == 0){
    numBonus = 2;
  }
  if (BonusPris[1] == 0 && bonus.effet > 2){
    numBonus = 2;
  }
  switch(bonus.effet + numBonus) {
    case 0:
      break;
    case 1:
      increaseSizeBarre(barre);
      Mix_PlayChannel(-1, son->bonus, 0);
      break;
    case 2:
      reduceSizeBarre(barre);
      Mix_PlayChannel(-1, son->malus, 0);
      break;
    case 3:
      increaseSpeedBarre(barre);
      Mix_PlayChannel(-1, son->bonus, 0);
      break;
    case 4:
      reduceSpeedBarre(barre);
      Mix_PlayChannel(-1, son->malus, 0);
      break;
    case 5:
      GoUpXbarre(barre);
      Mix_PlayChannel(-1, son->bonus, 0);
      break;
    case 6:
      GoDownXbarre(barre);
      Mix_PlayChannel(-1, son->malus, 0);
      break;
    default:
      break;
  }
}

BonusTab* iniBonusTab (){
  BonusTab *TabB;
  TabB = malloc(sizeof(BonusTab));
  if (TabB == NULL){
    return NULL;
  }
  TabB->nbrBonus=0;
  return TabB;
}

void aujoutBonusTab(BonusTab *bonustab, Bonus *bonus){
  if (bonustab->nbrBonus !=20){
    bonustab->tabBonus[bonustab->nbrBonus] = bonus;
    ++(bonustab->nbrBonus);

  }
}

void gestionBonus(BonusTab *tabBonus, Barre* barreJ1, Barre* barreJ2, PlayerTab* Joueurs, Son* son, int BonusPris[3]){
  int i;
  for (i=0; i<tabBonus->nbrBonus; ++i){
    glColor3ub(165,40,10);
    drawingBonus(*(tabBonus->tabBonus[i]));
    moveBonus(tabBonus->tabBonus[i], Joueurs);
    collisionBonus(tabBonus->tabBonus[i], barreJ1, barreJ2, Joueurs, son, BonusPris);
  }
}

void freeBonus(BonusTab *tab){
  int i;
  for (i=0;i<tab->nbrBonus;++i){
    free(tab->tabBonus[i]);
  }
  free(tab);
}