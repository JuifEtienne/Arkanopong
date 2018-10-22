#include "constante.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>


#include "SDLevent.h"
#include "menu.h"


void drawSquare(float posX, float posY, float haut, float larg, GLuint ind){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, ind);
  glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(posY, posX);
    glTexCoord2f(0, 1);
    glVertex2f(posY, posX+haut);
    glTexCoord2f(1, 1);
    glVertex2f(posY+larg, posX+haut);
    glTexCoord2f(1, 0);
    glVertex2f(posY+larg, posX);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}
  
void loadTextureMenuP(GLuint ind[5]){
  ind[0]=loadTexture("textures/menu/titre.png");
  ind[1]=loadTexture("textures/menu/histoire.png");
  ind[2]=loadTexture("textures/menu/defi.png");
  ind[3]=loadTexture("textures/menu/option.png");
  ind[4]=loadTexture("textures/menu/retour.png");
}

void loadMenuP(GLuint ind[5]){
  drawSquare(20, 300, 80, 400, ind[0]);
  drawSquare(120, 100, 180, 800, ind[1]);
  drawSquare(320, 100, 180, 800, ind[2]);
  drawSquare(520, 100, 180, 800, ind[3]);
  drawSquare(720, 800, 60, 150, ind[4]);
}

void freeTextureMenuP(GLuint ind[5]){
  glDeleteTextures(1,&(ind[0]));
  glDeleteTextures(1,&(ind[1]));
  glDeleteTextures(1,&(ind[2]));
  glDeleteTextures(1,&(ind[3]));
  glDeleteTextures(1,&(ind[4]));
}

void loadTextureStory(GLuint ind[3]){
  ind[0]=loadTexture("textures/menu/knight.png");
  ind[1]=loadTexture("textures/menu/prez.png");
  ind[2]=loadTexture("textures/menu/retour.png");
}

void loadStoryMode(GLuint ind[3]){
  drawSquare(50, 75, 650, 400, ind[0]);
  drawSquare(50, 550, 650, 400, ind[1]);
  drawSquare(720, 800, 60, 150, ind[2]);
}


void freeTextureStory(GLuint ind[3]){
  glDeleteTextures(1,&(ind[0]));
  glDeleteTextures(1,&(ind[1]));
  glDeleteTextures(1,&(ind[2]));
}


void loadTextureDefi(GLuint ind[3]){
  ind[0]=loadTexture("textures/menu/IA.png");
  ind[1]=loadTexture("textures/menu/2J.png");
  ind[2]=loadTexture("textures/menu/retour.png");
}

void loadDefi(GLuint ind[3]){
  drawSquare(50, 75, 650, 400, ind[0]);
  drawSquare(50, 550, 650, 400, ind[1]);
  drawSquare(720, 800, 60, 150, ind[2]);
}


void freeTextureDefi(GLuint ind[3]){
  glDeleteTextures(1,&(ind[0]));
  glDeleteTextures(1,&(ind[1]));
  glDeleteTextures(1,&(ind[2]));
}






void loadTextureDefiIA(GLuint ind[10]){
  ind[0]=loadTexture("textures/defiIA/defi1.png");
  ind[1]=loadTexture("textures/defiIA/defi2.png");
  ind[2]=loadTexture("textures/defiIA/defi3.png");
  ind[3]=loadTexture("textures/defiIA/defi4.png");
  ind[4]=loadTexture("textures/defiIA/defi5.png");
  ind[5]=loadTexture("textures/defiIA/defi6.png");
  ind[6]=loadTexture("textures/defiIA/defi7.png");
  ind[7]=loadTexture("textures/defiIA/defi8.png");
  ind[8]=loadTexture("textures/defiIA/deficharge.png");
  ind[9]=loadTexture("textures/menu/retour.png");
}

void loadDefiIA(GLuint ind[10]){
  drawSquare(50, 75, 180, 200, ind[0]);
  drawSquare(50, 300, 180, 200, ind[1]);
  drawSquare(50, 525, 180, 200, ind[2]);
  drawSquare(50, 750, 180, 200, ind[3]);
  drawSquare(275, 75, 180, 200, ind[4]);
  drawSquare(275, 300, 180, 200, ind[5]);
  drawSquare(275, 525, 180, 200, ind[6]);
  drawSquare(275, 750, 180, 200, ind[7]);
  drawSquare(500, 300, 200, 400, ind[8]);
  drawSquare(720, 800, 60, 150, ind[9]);
}


void freeTextureDefiIA(GLuint ind[10]){
  glDeleteTextures(1,&(ind[0]));
  glDeleteTextures(1,&(ind[1]));
  glDeleteTextures(1,&(ind[2]));
  glDeleteTextures(1,&(ind[3]));
  glDeleteTextures(1,&(ind[4]));
  glDeleteTextures(1,&(ind[5]));
  glDeleteTextures(1,&(ind[6]));
  glDeleteTextures(1,&(ind[7]));
  glDeleteTextures(1,&(ind[8]));
  glDeleteTextures(1,&(ind[9]));
}



void loadTextureDefi2J(GLuint ind[10]){
  ind[0]=loadTexture("textures/defi2J/defi1.png");
  ind[1]=loadTexture("textures/defi2J/defi2.png");
  ind[2]=loadTexture("textures/defi2J/defi3.png");
  ind[3]=loadTexture("textures/defi2J/defi4.png");
  ind[4]=loadTexture("textures/defi2J/defi5.png");
  ind[5]=loadTexture("textures/defi2J/defi6.png");
  ind[6]=loadTexture("textures/defi2J/defi7.png");
  ind[7]=loadTexture("textures/defi2J/defi8.png");
  ind[8]=loadTexture("textures/defi2J/deficharge.png");
  ind[9]=loadTexture("textures/menu/retour.png");
}

void loadDefi2J(GLuint ind[10]){
  drawSquare(50, 75, 180, 200, ind[0]);
  drawSquare(50, 300, 180, 200, ind[1]);
  drawSquare(50, 525, 180, 200, ind[2]);
  drawSquare(50, 750, 180, 200, ind[3]);
  drawSquare(275, 75, 180, 200, ind[4]);
  drawSquare(275, 300, 180, 200, ind[5]);
  drawSquare(275, 525, 180, 200, ind[6]);
  drawSquare(275, 750, 180, 200, ind[7]);
  drawSquare(500, 300, 200, 400, ind[8]);
  drawSquare(720, 800, 60, 150, ind[9]);
}


void freeTextureDefi2J(GLuint ind[10]){
  glDeleteTextures(1,&(ind[0]));
  glDeleteTextures(1,&(ind[1]));
  glDeleteTextures(1,&(ind[2]));
  glDeleteTextures(1,&(ind[3]));
  glDeleteTextures(1,&(ind[4]));
  glDeleteTextures(1,&(ind[5]));
  glDeleteTextures(1,&(ind[6]));
  glDeleteTextures(1,&(ind[7]));
  glDeleteTextures(1,&(ind[8]));
  glDeleteTextures(1,&(ind[9]));
}




void loadTextureOption(GLuint ind[16]){
  ind[0]=loadTexture("textures/menu/musique.png");
  ind[1]=loadTexture("textures/menu/son.png");
  ind[2]=loadTexture("textures/menu/bonus.png");
  ind[3]=loadTexture("textures/menu/on.png");
  ind[4]=loadTexture("textures/menu/off.png");
  ind[5]=loadTexture("textures/menu/on.png");
  ind[6]=loadTexture("textures/menu/off.png");
  ind[7]=loadTexture("textures/menu/bonus1.png");
  ind[8]=loadTexture("textures/menu/bonus2.png");
  ind[9]=loadTexture("textures/menu/bonus3.png");
  ind[10]=loadTexture("textures/menu/retour.png");
  ind[11]=loadTexture("textures/menu/onselect.png");
  ind[12]=loadTexture("textures/menu/offselect.png");
  ind[13]=loadTexture("textures/menu/bonus1pris.png");
  ind[14]=loadTexture("textures/menu/bonus2pris.png");
  ind[15]=loadTexture("textures/menu/bonus3pris.png");
}

void loadOption(GLuint ind[16], int musiqueOn, int sonOn, int BonusPris[3]){
  drawSquare(50, 100, 100, 300, ind[0]);
  drawSquare(200, 100, 100, 300, ind[1]);
  drawSquare(350, 100, 100, 300, ind[2]);
  if(musiqueOn == 1){
    drawSquare(50, 600, 100, 100, ind[11]);
    drawSquare(50, 750, 100, 100, ind[4]);
  }
  else{
    drawSquare(50, 600, 100, 100, ind[3]);
    drawSquare(50, 750, 100, 100, ind[12]);
  }
  if(sonOn == 1){
    drawSquare(200, 600, 100, 100, ind[11]);
    drawSquare(200, 750, 100, 100, ind[6]);
  }
  else{
    drawSquare(200, 600, 100, 100, ind[5]);
    drawSquare(200, 750, 100, 100, ind[12]);
  }
  if(BonusPris[0]==1){
    drawSquare(500, 300, 100, 100, ind[13]);
  }
  else{
    drawSquare(500, 300, 100, 100, ind[7]);
  }
  if(BonusPris[1]==1){
    drawSquare(500, 450, 100, 100, ind[14]);
  }
  else{
    drawSquare(500, 450, 100, 100, ind[8]);
  }
  if(BonusPris[2]==1){
    drawSquare(500, 600, 100, 100, ind[15]);
  }
  else{
    drawSquare(500, 600, 100, 100, ind[9]);
  }
  drawSquare(720, 800, 60, 150, ind[10]);
}


void freeTextureOption(GLuint ind[16]){
  glDeleteTextures(1,&(ind[0]));
  glDeleteTextures(1,&(ind[1]));
  glDeleteTextures(1,&(ind[2]));
  glDeleteTextures(1,&(ind[3]));
  glDeleteTextures(1,&(ind[4]));
  glDeleteTextures(1,&(ind[5]));
  glDeleteTextures(1,&(ind[6]));
  glDeleteTextures(1,&(ind[7]));
  glDeleteTextures(1,&(ind[8]));
  glDeleteTextures(1,&(ind[9]));
  glDeleteTextures(1,&(ind[10]));
}


