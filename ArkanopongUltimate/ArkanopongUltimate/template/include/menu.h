#ifndef MENU_H_
#define MENU_H_

typedef enum{
  MENU, STORYMODE, DEFIMODE, DEFIIA, DEFI2J, OPTION
} MenuType;



void drawSquare(float posX, float posY, float haut, float larg, GLuint ind);
void loadTextureMenuP(GLuint ind[5]);
void loadMenuP(GLuint ind[5]);
void freeTextureMenuP(GLuint ind[5]);
void loadTextureStory(GLuint ind[3]);
void loadStoryMode(GLuint ind[3]);
void freeTextureStory(GLuint ind[3]);
void loadTextureDefi(GLuint ind[3]);
void loadDefi(GLuint ind[3]);
void freeTextureDefi(GLuint ind[3]);
void loadTextureDefiIA(GLuint ind[10]);
void loadDefiIA(GLuint ind[10]);
void freeTextureDefiIA(GLuint ind[10]);
void loadTextureDefi2J(GLuint ind[10]);
void loadDefi2J(GLuint ind[10]);
void freeTextureDefi2J(GLuint ind[10]);
void loadTextureOption(GLuint ind[16]);
void loadOption(GLuint ind[16], int musiqueOn, int sonOn, int BonusPris[3]);
void freeTextureOption(GLuint ind[16]);




#endif