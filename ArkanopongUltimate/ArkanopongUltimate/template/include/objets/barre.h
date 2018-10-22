#ifndef BARRE_H_
#define BARRE_H_

typedef struct{
  int rayon;
  float posX;
  float posY;
  float vitY;
  int joueur;
  int temps; /*temps d'activation du bonus sur la barre*/
}Barre;

Barre* iniBarre(int joueur);
void moveBarreLeft (Barre* barre);
void moveBarreRight (Barre* barre);
void drawBarre(Barre barre);
void increaseSizeBarre (Barre * barre);
void reduceSizeBarre(Barre* barre);
void increaseSpeedBarre(Barre* barre);
void reduceSpeedBarre(Barre* barre);
void GoUpXbarre(Barre* barre);
void GoDownXbarre(Barre* barre);
void reiniBarre(Barre* barre);
void stopBonus(Barre* barre);
/*void IABarre(Barre* barre, Ball* balle1, Ball* balle2);*/

#endif