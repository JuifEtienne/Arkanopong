#ifndef BONUS_H_
#define BONUS_H_

typedef struct bonus
{
  float posX, posY;
  float vitX;
  int radius; /*c'est un cercle le bonus nan ?*/
  int effet;
  int last_player; 
  int etat;
} Bonus;

typedef struct BonusTab{ 
  int nbrBonus;
  Bonus* tabBonus[20];
} BonusTab;

Bonus *iniBonus (float posX, float posY, int effet, int last_player);
void drawingBonus(Bonus bonus);
void moveBonus(Bonus *bonus, PlayerTab* Joueurs);
void collisionBonus(Bonus *bonus, Barre* barre1, Barre* barre2, PlayerTab* Joueurs, Son* son, int BonusPris[3]);
void BonusEffet(Bonus bonus, Barre *barre, Son* son, int BonusPris[3]);
BonusTab* iniBonusTab ();
void aujoutBonusTab(BonusTab *bonustab, Bonus *bonus);
void gestionBonus(BonusTab *tabBonus, Barre* barreJ1, Barre* barreJ2, PlayerTab* Joueurs, Son* son, int BonusPris[3]);
void freeBonus(BonusTab *tab);

#endif