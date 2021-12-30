#pragma once
#include <SDL_mixer.h> // libreria de audio
#include "Audio.h"

class MP3Audio : public Audio
{
public:
	MP3Audio(string filename);
	~MP3Audio() override;
	void doPlay() override;
	void doPause() override;
	void resume() override;
	Mix_Music* mix; // Lib mixer
};

