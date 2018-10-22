#include "constante.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "objets/barre.h"



Barre* iniBarre(int joueur){
  Barre *nvBarre = malloc(sizeof(Barre));
  if (nvBarre == NULL){
    fprintf(stderr, "Allocation de la mémoire barre échouée. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  nvBarre->rayon=(WINDOW_WIDTH/20);
  nvBarre->joueur=joueur;
  if(nvBarre->joueur==1){
    nvBarre->posX=50.0;
  }
  else{
    nvBarre->posX=750.0;
  }
  nvBarre->vitY=20.0;
  nvBarre->posY=1.0*WINDOW_WIDTH/2;
  nvBarre->temps=0;
  return nvBarre;
}

void moveBarreLeft (Barre* barre){
  if(barre->posY-barre->vitY>=barre->rayon){
    barre->posY-=barre->vitY;
  }
  else{
    barre->posY=barre->rayon;
  }
}


void moveBarreRight (Barre* barre){
  if(barre->posY+barre->vitY<=WINDOW_WIDTH-barre->rayon){
    barre->posY+=barre->vitY;
  }
  else{
    barre->posY=1.0*WINDOW_WIDTH-barre->rayon;
  }
}

/* void drawBarre(Barre barre){
  glBegin(GL_LINES);
      glVertex2f(1.0*barre.posX, barre.posY-rayon);
      glVertex2f(1.0*barre.posX, barre.posY+rayon);
    glEnd();
  return;
} */

void drawBarre(Barre barre){
  float NbSeg=50;
  float radius=0.2;
  int i;
  glBegin(GL_POLYGON);
  for(i=0;i<=NbSeg;++i){
    glVertex2f(barre.posY-barre.rayon+radius+cos(M_PI/2+(i/2)*(M_PI/NbSeg))*radius,barre.posX+2.0-radius+sin(M_PI/2+(i/2)*(M_PI/NbSeg))*radius);
  }
  for(i=0;i<=NbSeg;++i){
    glVertex2f(barre.posY-barre.rayon+radius+cos(M_PI+(i/2)*(M_PI/NbSeg))*radius,barre.posX-2.0+radius+sin(M_PI+(i/2)*(M_PI/NbSeg))*radius);
  }
  for(i=0;i<=NbSeg;++i){
      glVertex2f(barre.posY+barre.rayon-radius+cos(-M_PI/2+(i/2)*(M_PI/NbSeg))*radius,barre.posX-2.0+radius+sin(-M_PI/2+(i/2)*(M_PI/NbSeg))*radius);
  }
  for(i=0;i<=NbSeg;++i){
      glVertex2f(barre.posY+barre.rayon-radius+cos((i/2)*(M_PI/NbSeg))*radius,barre.posX+2.0-radius+sin((i/2)*(M_PI/NbSeg))*radius);
  }
    glEnd();
}

void increaseSizeBarre (Barre * barre){ 
  if(barre->rayon<WINDOW_WIDTH/10){
    barre->rayon+=WINDOW_WIDTH/200;
  }
}

void reduceSizeBarre(Barre* barre){
  if(barre->rayon>WINDOW_WIDTH/40){
    barre->rayon-=WINDOW_WIDTH/200;
  }
}

void increaseSpeedBarre(Barre* barre){
  if(barre->vitY<WINDOW_WIDTH/20){
    barre->vitY+=WINDOW_WIDTH/800;
  }
}

void reduceSpeedBarre(Barre* barre){
  if(barre->vitY>WINDOW_WIDTH/80){
    barre->vitY-=WINDOW_WIDTH/500;
  }
}

void GoUpXbarre(Barre* barre){
  if(barre->joueur==1){
    if(barre->posX>50.0){
      barre->posX-=50.0;
    }
  }
  else if(barre->joueur==2){
    if(barre->posX>600.0){
      barre->posX-=50.0;
    }
  }
}

void GoDownXbarre(Barre* barre){
  if(barre->joueur==1){
    if(barre->posX<200.0){
      barre->posX+=50.0;
    }
  }
  else if(barre->joueur==2){
    if(barre->posX<750.0){
      barre->posX+=50.0;
    }
  }
}


void reiniBarre(Barre* barre){
  barre->rayon=(WINDOW_WIDTH/20);
  if(barre->joueur==1){
    barre->posX=50;
  }
  else if(barre->joueur==2){
    barre->posX=750;
  }
  barre->vitY=WINDOW_WIDTH/40;
}

void stopBonus(Barre* barre){
  if(barre->temps == 1){
    reiniBarre(barre);
    barre->temps = 0;
  }
  else if(barre->temps > 1){
    --(barre->temps);
  }
}