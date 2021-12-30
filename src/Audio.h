#pragma once

#include <iostream>
#include <string>

using namespace std;

class Audio
{
public:
	Audio(string filename);
	virtual ~Audio();
	void play();
	void pause();
	bool paused = false;
	string filename;
protected:
	virtual void doPlay();
	virtual void doPause();
	virtual void resume();
};
