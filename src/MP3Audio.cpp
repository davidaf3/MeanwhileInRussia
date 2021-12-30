#include "MP3Audio.h"

MP3Audio::MP3Audio(string filename) : Audio(filename) {
	mix = Mix_LoadMUS(filename.c_str());
}

MP3Audio::~MP3Audio() {
	if (!paused) doPause();
}

void MP3Audio::doPlay() {
	Mix_PlayMusic(mix, -1);
}

void MP3Audio::doPause() {
	Mix_FreeMusic(mix);
}

void MP3Audio::resume() {
	mix = Mix_LoadMUS(filename.c_str());
	doPlay();
}