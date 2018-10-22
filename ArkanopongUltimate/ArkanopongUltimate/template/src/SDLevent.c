#include "constante.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;


#include "SDLevent.h"
#include "objets/joueur.h"


void initialisationFen(){
  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
  fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
  exit(EXIT_FAILURE);
  }
   
  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
  fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
  exit(EXIT_FAILURE);
  }

  glClear(GL_COLOR_BUFFER_BIT);
  /* Titre de la fenêtre */
  SDL_WM_SetCaption("ARKANE KNIGHT", NULL);
  glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0., 1.0*WINDOW_WIDTH,1.0*WINDOW_HEIGHT,0.);
}

GLuint loadTexture(const char *path){
  GLuint ind;
  GLenum format = GL_RED;
  SDL_Surface* texture;
  texture = IMG_Load(path);
  glGenTextures(1, &ind);
  if(texture == NULL){
    fprintf(stderr, "Allocation de la mémoire pour une texture a échouée. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  glBindTexture(GL_TEXTURE_2D, ind);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  switch(texture->format->BytesPerPixel){
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
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->w, texture->h, 0, format, GL_UNSIGNED_BYTE, texture->pixels);
  SDL_FreeSurface(texture);
  glBindTexture(GL_TEXTURE_2D, 0);
  return ind;
}

void Start(){
  GLuint ind[6];
  int i;
  ind[0]=loadTexture("textures/5.png");
  ind[1]=loadTexture("textures/4.png");
  ind[2]=loadTexture("textures/3.png");
  ind[3]=loadTexture("textures/2.png");
  ind[4]=loadTexture("textures/1.png");
  ind[5]=loadTexture("textures/go.png");

  for(i=0; i<6; i++){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ind[i]);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(400, 300);
      glTexCoord2f(0, 1);
      glVertex2f(400, 500);
      glTexCoord2f(1, 1);
      glVertex2f(600, 500);
      glTexCoord2f(1, 0);
      glVertex2f(600, 300);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_GL_SwapBuffers();
    SDL_Delay(500);
  }
  glDisable(GL_TEXTURE_2D);

  for(i=0; i<6; i++){
    glDeleteTextures(1, &ind[i]);
  }
}



Son* iniSon(Son* son){
  son = malloc(sizeof(Son));
  if (son == NULL){
    fprintf(stderr, "Allocation de la mémoire pour le son a échouée. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  son->tombe = Mix_LoadWAV("musiques/tombe.wav");
  son->bonus = Mix_LoadWAV("musiques/bonus.wav");
  son->malus = Mix_LoadWAV("musiques/malus.wav");
  son->victoire = Mix_LoadWAV("musiques/victoire.wav");
  son->rebond = Mix_LoadWAV("musiques/rebond.wav");
  return son;
}

Texture* iniTex(const char *path){
  Texture* nvTexture = malloc(sizeof(Texture));
  if (nvTexture == NULL){
    fprintf(stderr, "Allocation de la mémoire pour les textures a échouée. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  char B1[80]="";
  char B2[80]="";
  char B3[80]="";
  char B4[80]="";
  char PDV[80]="";
  /*char B1[80];*/
  strcat(strcat(B1, path), "/B1.png");
  strcat(strcat(B2, path), "/B2.png");
  strcat(strcat(B3, path), "/B3.png");
  strcat(strcat(B4, path), "/B4.png");
  strcat(strcat(PDV, path), "/pv.png");

  nvTexture->B1 = loadTexture(B1);
  nvTexture->B2 = loadTexture(B2);
  nvTexture->B3 = loadTexture(B3);
  nvTexture->B4 = loadTexture(B4);
  nvTexture->PDV = loadTexture(PDV);

  /*printf("%d %d %d %d \n\n", nvTexture->B1, nvTexture->B, nvTexture->B3, nvTexture->B4);*/
  return nvTexture;
}