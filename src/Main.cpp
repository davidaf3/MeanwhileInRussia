#include "Game.h"
#undef main  //esto es para quitar el main que hay en la Librería SDL_main

int main() {
	Game* game = new Game();
	return 0;
}
