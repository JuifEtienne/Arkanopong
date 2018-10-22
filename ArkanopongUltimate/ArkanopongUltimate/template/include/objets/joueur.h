#ifndef JOUEUR_H_
#define JOUEUR_H_

typedef struct{
  int PDV;
  int ID;
}Player;

typedef struct{ 
  int nbrPlayer;
  Player** players;
}PlayerTab;


Player* iniPlayer(int id);
PlayerTab* iniPlayerTab (int nbrPlayer);
void modifPV (PlayerTab* tab, int numPlayer, int effet);
void drawPDV(Player player, Texture texture);
void freePlayerTab(PlayerTab* tab);

#endif