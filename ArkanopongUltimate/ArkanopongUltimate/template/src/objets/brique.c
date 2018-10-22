#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>


#include "constante.h"
#include "SDLevent.h"
#include "objets/joueur.h"
#include "objets/brique.h"


/*void loadTextureBrique(Texture texture){
  int i;
  GLenum format = GL_RED;
  SDL_Surface* texture[4];
  texture[0]= IMG_Load("./textures/test0.jpg");
  texture[1]= IMG_Load("./textures/test1.jpg");
  texture[2]= IMG_Load("./textures/test2.jpg"); 
  texture[3]= IMG_Load("./textures/test3.jpg");
  glGenTextures(4, ind);
  for(i=0; i<4; ++i){
    if(texture[i] == NULL){
      fprintf(stderr, "Allocation de la mémoire pour une texture a échouée. Fin du programme.\n");
      exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, ind[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    switch(texture[i]->format->BytesPerPixel){
      case 1:
        format = GL_RED;
        break;
      case 3:
        format = GL_RGB;
        break;
      case 4:
        format = GL_RGBA;
        break;
      default:
        fprintf(stderr, "Format des pixels de l'image non pris en charge. Fin du programme.\n");
        exit(EXIT_FAILURE);
        break;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture[i]->w, texture[i]->h, 0, format, GL_UNSIGNED_BYTE, texture[i]->pixels);
    SDL_FreeSurface(texture[i]);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}*/

Brique * iniBrique (int posX, int posY, int type, int larg, int haut, GLuint texture){
  Brique *memoireAllouee = malloc(sizeof(Brique));
  if (memoireAllouee == NULL){
    fprintf(stderr, "Allocation de la mémoire brique échouée. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  memoireAllouee-> posX = posX;
  memoireAllouee-> posY = posY;
  memoireAllouee-> type = type; /*0 = normal, 1 = indestructible, 2 = Bonus/Malus A (taille), 3 = Bonus/Malus B (vitesse)*/
  memoireAllouee-> larg = larg;
  memoireAllouee-> haut = haut;
  memoireAllouee-> texture = texture;
  if(type == 7){
    memoireAllouee-> etat = 0;
  }
  else{
    memoireAllouee-> etat = 1;
  }
  return memoireAllouee;
}

TabBrique * iniTabBrique (const char *path, Texture texture){
  int larg, haut;
  int i, j;
  int type;
  int largBrique, hautBrique;
  GLuint ind[4];

  ind[0]= texture.B1;
  ind[1]= texture.B2;
  ind[2]= texture.B3;
  ind[3]= texture.B4;

  TabBrique *memoireAllouee = malloc(sizeof(TabBrique));
  if (memoireAllouee == NULL){
    fprintf(stderr, "Allocation de la mémoire tableau de briques échouée. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  /*Récupérations des informations du fichier*/
  FILE *f=fopen(path,"r");
  if (f==NULL){
    fprintf(stderr, "Récupération du fichier échouée. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  fscanf(f, "%d %d", &haut, &larg);
  int tab[larg*haut];
  for(i=0;i<larg*haut;i++){
    fscanf(f, "%d ", &tab[i]);
  }
  fclose(f);
  /*Initialisation du tableau*/
  memoireAllouee->nbrLin = haut;
  memoireAllouee->nbrCol = larg;
  memoireAllouee->briqueTab = malloc(larg*haut*sizeof(Brique));
  if (memoireAllouee->briqueTab == NULL){
    return NULL;
  }

  largBrique = WINDOW_WIDTH/larg;
  hautBrique = WINDOW_HEIGHT/(3*haut);
  for(i=0;i<haut;++i){
    for(j=0; j<larg; ++j){
      type = tab[larg*i+j];
      memoireAllouee->briqueTab[larg*i+j] = iniBrique(i*hautBrique+WINDOW_HEIGHT/3, j*largBrique, tab[larg*i+j], largBrique, hautBrique, ind[type]);
    } 
  }
  return memoireAllouee;
}

int presenceBrique(int posX, int posY, TabBrique tab){
  /*Indique s'il y a une brique en vie à la position (posX, posY)*/
  int i;
  int larg, haut;
  larg = tab.nbrCol;
  haut = tab.nbrLin;
  if(posX < 260 && posX > 530){ /*la position n'est pas dans la zone des briques*/
    return 0;
  }
  for(i=0;i<larg*haut;++i){
    /*posX entre tab.briqueTab[i].posX et tab.briqueTab[i+j].posX + tab.briqueTab[i+j].tailleX */
    if (posX >= tab.briqueTab[i]->posX && posX < tab.briqueTab[i]->posX + tab.briqueTab[i]->haut){
      if (posY >= tab.briqueTab[i]->posY && posY < tab.briqueTab[i]->posY + tab.briqueTab[i]->larg){
        if (tab.briqueTab[i]->etat == 0){
          return -1;
        } 
        else{
          return i;
        }
      }
    }
  }
  return -1;
}

void drawBrique(Brique brique){
  int posX, posY, larg, haut;

  posX = brique.posX;
  posY = brique.posY;
  larg = brique.larg;
  haut = brique.haut;
  /*glColor3ub(10,255/(x+1),67);*/

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, brique.texture);
  glBegin(GL_QUADS);
    glTexCoord2f(1, 0);
    glVertex2f(posY*1.0, posX*1.0);
    glTexCoord2f(1, 1);
    glVertex2f(posY*1.0, posX*1.0+haut);
    glTexCoord2f(0, 1);
    glVertex2f(posY*1.0+larg, posX*1.0+haut);
    glTexCoord2f(0, 0);
    glVertex2f(posY*1.0+larg, posX*1.0);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

void drawBriqueTab(TabBrique tab){
  int i;
  int larg, haut;
  glColor3ub(255,255,255);
  larg = tab.nbrCol;
  haut = tab.nbrLin;
  for(i=0;i<larg*haut;++i){
    if (tab.briqueTab[i]->etat == 1){
      if (tab.briqueTab[i]->type == 0){

        drawBrique(*(tab.briqueTab[i]));
        
      }
      if (tab.briqueTab[i]->type == 1){

        drawBrique(*(tab.briqueTab[i]));

      }
      if (tab.briqueTab[i]->type == 2){

        drawBrique(*(tab.briqueTab[i]));

      }
      if (tab.briqueTab[i]->type == 3){

        drawBrique(*(tab.briqueTab[i]));

      }
    }
  }
}


void freeBrique(Brique* brique){
  free(brique);
}

void freeTabBrique(TabBrique* tab){
  int i;
  for(i=0;i<tab->nbrLin*tab->nbrCol;++i){
      freeBrique(tab->briqueTab[i]);
  }
  free(tab);
}

void freeTexture(GLuint ind[]){
  glDeleteTextures(4, ind);
}