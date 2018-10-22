#ifndef SDLEVENT_H_
#define SDLEVENT_H_

typedef struct Son{
	Mix_Chunk *rebond;
	Mix_Chunk *bonus;
	Mix_Chunk *malus;
	Mix_Chunk *tombe;
	Mix_Chunk *victoire;
} Son;

typedef struct Texture{
	GLuint B1;
	GLuint B2;
	GLuint B3;
	GLuint B4;
	GLuint PDV;
	/*GLuint Fond;*/
} Texture;

void initialisationFen();
GLuint loadTexture(const char *path);
void Start();
Son* iniSon(Son* son);
Texture* iniTex(const char *path);


#endif