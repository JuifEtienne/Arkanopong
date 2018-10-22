#ifndef JEU_H_
#define JEU_H_


void IABarre(Barre* barre, Ball* balle1, Ball* balle2);
int Game(const char *path, Mix_Music* fond, Son* son, Texture* texture, int IA, int musiqueOn, int sonOn, int BonusPris[3]);
int victoire(PlayerTab* Joueurs, int IA, Son* son);
int StoryModeKnight(Mix_Music* fond, Son* son, Texture* texture, int musiqueOn, int sonOn, int BonusPris[3]);
int StoryModePrez(Mix_Music* fond, Son* son, Texture* texture, int musiqueOn, int sonOn, int BonusPris[3]);

#endif