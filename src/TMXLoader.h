#pragma once

#include "GameLayer.h"

class TMXLoader
{
public:
	static void loadMapTMX(string name, GameLayer* gameLayer, Level* level);
	static void loadTMXTile(int tileNum, float x, float y, bool physic, GameLayer* gameLayer, Level* level);
	static const int tileSize = 32;
};
