#pragma once
#include <SDL_mixer.h> // libreria de audio
#include "Audio.h";

class WAVAudio : public Audio
{
public:
	WAVAudio(string filename, bool loop = false);
	~WAVAudio() override;
	void doPlay() override;
	void doPause() override;
	void resume() override;
	bool loop;
	Mix_Chunk* sound;
};

