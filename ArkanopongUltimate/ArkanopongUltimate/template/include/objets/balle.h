#ifndef BALLE_H_
#define BALLE_H_

typedef struct Ball {
  float posX, posY;
  float vitX, vitY;
  int radius; /*rayon*/
  int last_player; 
} Ball;

void iniVitesse(Ball* ball, int player);
Ball *iniBall (int last_player);
void drawingBall(Ball ball);
void collision2(Ball *ball1, Ball *ball2, Son* son, int sonOn);
void collision1(Ball *ball, Barre barre1, Barre barre2, PlayerTab* Joueurs, TabBrique* tab, BonusTab* bonustab, Son* son, int sonOn);
void moveBall(Ball *balle, Barre barre1, Barre barre2, PlayerTab* Joueurs, TabBrique* tab, BonusTab* bonustab, Son* son, int sonOn);
void moveBalls(Ball *ball1, Ball *ball2, Barre barre1, Barre barre2, PlayerTab* Joueurs, TabBrique* tab, BonusTab* bonustab, Son* son, int sonOn);

#endif