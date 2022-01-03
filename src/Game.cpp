#include "Game.h"
#include "IntroLayer.h"
#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif

void loopCallback(void* arg)
{
  static_cast<Game*>(arg)->loopStep();
}

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error SDL_Init" << SDL_GetError() << endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		cout << "Error Window y Renderer" << SDL_GetError() << endl;
	}

	SDL_Surface* iconSurface = IMG_Load("res/icon.png");
	SDL_SetWindowIcon(window, iconSurface);
	SDL_SetWindowTitle(window, "Meanwhile In Russia");

	// Escalado de im�genes de calidad 
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	// Audio
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_VolumeMusic(50);

	// fuentes
	TTF_Init();

	SDL_Surface* surface = IMG_Load("res/crosshair.png");
	SDL_Cursor* cursor = SDL_CreateColorCursor(surface, 0, 0);
	SDL_SetCursor(cursor);

	changeLayer(IntroLayer::instance(this));

	loopActive = true; // bucle activo
	loop();
}

void Game::loop() {
	#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg(&loopCallback, this, 0, 1);
	#else
		while (loopActive) {
			loopStep();
		}
		Mix_CloseAudio();
	#endif
}

void Game::loopStep() {
	int initTick = SDL_GetTicks();

	// Controles
	layer->processControls();
	// Actualizar elementos
	layer->update();
	// Dibujar
	layer->draw();
	
	int endTick = SDL_GetTicks();
	int differenceTick = endTick - initTick;
	
	if (differenceTick < (1000 / frameRate)) {
		SDL_Delay((1000 / frameRate) - differenceTick);
	}
}

void Game::changeLayer(Layer* layer) {
	layer->init();
	this->layer = layer;
}

SDL_Texture* Game::getTexture(string filename) {
	if (mapTextures.find(filename) == mapTextures.end()) {
		SDL_Surface* surface = IMG_Load(filename.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		mapTextures[filename] = texture;
	}

	return mapTextures[filename];
}

TTF_Font* Game::getFont(string fontname, int size, int outlineSize) {
	string fontnameAndSize = fontname + to_string(size) + "_" + to_string(outlineSize);
	if (mapFonsts.find(fontnameAndSize) == mapFonsts.end()) {
		TTF_Font* font = TTF_OpenFont(fontname.c_str(), size);
		if (outlineSize > 0) TTF_SetFontOutline(font, outlineSize);
		mapFonsts[fontnameAndSize] = font;
	}

	return mapFonsts[fontnameAndSize];
}

WAVAudio* Game::getWAV(string filename, bool loop) {
	string filenameWithLoop = filename + to_string(loop);
	if (mapWAVs.find(filenameWithLoop) == mapWAVs.end()) {
		mapWAVs[filenameWithLoop] = new WAVAudio(filename, loop);
	}

	return mapWAVs[filenameWithLoop];
}
