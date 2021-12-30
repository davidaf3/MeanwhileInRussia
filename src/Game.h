#pragma once

// Todas las librerias de SDL y otras utilidades
#include <iostream>
#include <string>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>

#include <SDL_mixer.h> // libreria de audio
#include "WAVAudio.h"

// Valores generales
#define WIDTH 960
#define HEIGHT 640
#define TEXT_SIZE 26
#define TEXT_BORDER 2

class Layer;

class Game
{
public:
	Game();
	SDL_Texture* getTexture(string filename);
	map<string, SDL_Texture*> mapTextures;

	TTF_Font* getFont(string fontname, int size, int outlineSize = 0);
	map<string, TTF_Font*> mapFonsts;

	WAVAudio* getWAV(string filename, bool loop = false);
	map<string, WAVAudio*> mapWAVs;

	void loop();
	void changeLayer(Layer* layer);
	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador
	bool loopActive; // Juego activo
	Layer* layer;

	int frameRate = 30;
};
