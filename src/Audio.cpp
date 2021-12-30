#include "Audio.h"

Audio::Audio(string filename) {
	this->filename = filename;
}

Audio::~Audio() {}

void Audio::play() {
	if (paused) resume();
	else doPlay();
	paused = false;
}

void Audio::pause() {
	paused = true;
	doPause();
}

void Audio::doPause() {}

void Audio::doPlay() {}

void Audio::resume() {}