#include "WAVAudio.h"

WAVAudio::WAVAudio(string filename, bool loop) : Audio(filename) {
	this->sound = Mix_LoadWAV(filename.c_str());
	this->loop = loop;
}

WAVAudio::~WAVAudio() {
	if (!paused) doPause();
}

void WAVAudio::doPlay() {
	Mix_PlayChannel(-1, sound, loop ? -1 : 0);
}

void WAVAudio::doPause() {
	Mix_FreeChunk(sound);
}

void WAVAudio::resume() {
	sound = Mix_LoadWAV(filename.c_str());
	doPlay();
}