#ifndef INTERSECTION_H_
#define INTERSECTION_H_

typedef struct Brique{
  int posX, posY; /*(posX, posY) = (hauteur,largeur) du coin en haut à gauche */
  int etat; /*1 vivant, 0 mort*/
  int type; 
  int larg, haut;
  GLuint texture;
} Brique;

typedef struct TabBrique{
  int nbrLin;
  int nbrCol;
  Brique ** briqueTab;
} TabBrique;

/*void loadTextureBrique(GLuint* ind);*/
Brique * iniBrique (int posX, int posY, int type, int larg, int haut, GLuint texture);
TabBrique * iniTabBrique (const char *path, Texture texture);
int presenceBrique(int posX, int posY, TabBrique tab);
void drawBrique(Brique brique);
void drawBriqueTab(TabBrique tab);
void freeBrique(Brique* brique);
void freeTabBrique(TabBrique* tab);
void freeTexture(GLuint ind[]);


#endif