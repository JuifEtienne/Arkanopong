#include "constante.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "SDLevent.h"
#include "objets/joueur.h"



Player* iniPlayer(int id){
  Player *nvPlayer = malloc(sizeof(Player));
  if (nvPlayer == NULL){
    return NULL;
  }
  nvPlayer->PDV=5;
  nvPlayer->ID=id;
  return nvPlayer;
}

PlayerTab* iniPlayerTab (int nbrPlayer){
  PlayerTab *TabP;
  int i;
  TabP = malloc(sizeof(PlayerTab));
  if (TabP == NULL){
    return NULL;
  }
  TabP->nbrPlayer=nbrPlayer;
  TabP->players = malloc(nbrPlayer*sizeof(Player));
  if (TabP->players == NULL){
    return NULL;
  }
  for (i=0;i<nbrPlayer;++i){
    TabP->players[i] = iniPlayer(i+1);
    if (TabP->players[i] == NULL){
      return NULL;
    }
  }

  
  return TabP;
} 

void modifPV (PlayerTab* tab, int numPlayer, int effet){
  if(effet==0){
    (tab->players[numPlayer])->PDV -= 1;
  }
  else{
    (tab->players[numPlayer])->PDV += 1;
  }
}

/* DrawPDV fait des carrés de 20x20 espacés de 15, 
le problème est que la barre peut aller dessus si jamais elle est reculée par un bonus */


void drawPDV(Player player, Texture texture){
  int i;
  
  if(player.ID==1){
    for(i=0;i<player.PDV;++i){
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texture.PDV);
      glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(WINDOW_WIDTH-15-(35*i),15);
        glTexCoord2f(0, 1);
        glVertex2f(WINDOW_WIDTH-15-(35*i),35);
        glTexCoord2f(1, 1);
        glVertex2f(WINDOW_WIDTH-35-(35*i),35);
        glTexCoord2f(1, 0);
        glVertex2f(WINDOW_WIDTH-35-(35*i),15);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
  else if (player.ID==2){
    for(i=0;i<player.PDV;++i){
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texture.PDV);
      glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(15+(35*i),765);
        glTexCoord2f(0, 1);
        glVertex2f(15+(35*i),785);
        glTexCoord2f(1, 1);
        glVertex2f(35+(35*i),785);
        glTexCoord2f(1, 0);
        glVertex2f(35+(35*i),765);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
}

void freePlayerTab(PlayerTab* tab){
  int i;
  for (i=0;i<tab->nbrPlayer;++i){
    free(tab->players[i]);
    }
  free(tab);
}

