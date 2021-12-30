#pragma once

#include "Layer.h"

#include "Character.h"
#include "Player.h"
#include "Tile.h"
#include "Background.h"
#include "Projectile.h"
#include "Collectable.h"
#include "HUDText.h"
#include "Audio.h"

#include "Space.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>
#include <chrono>

class InputController;

class LevelCompleteLayer;

typedef struct Level {
	string name;
	string tileset;
	int tilesetWidth;
	int tilesetHeight;
	int tilesetColumns;
	int tilesetMargin;
	int tilesetSpacing;
	float endLevelX;
	int numberOfEnemies;
	int parTime;
	int number;
	int mapWidth = 0;
	int mapHeight = 0;
	int initialGun;
	set<int> initialGunsInventory;
	map<string, int> initialAmmoInventory;
} Level;

class GameLayer : public Layer
{
public:
	static GameLayer* instance(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void onGameOver();
	void onLevelComplete();

	void onCharacterDead(Character* character, GunCollectable* droppedGun) override;
	void onEnemyKilled() override;
	void onCharacterFire(Projectile* projectile) override;

	void setToFirstLevel();
	void deletePlayer();

	string levels[3] = { "res/street.tmx", "res/army.tmx", "res/lab.tmx" };
	int lastLevel = 2;
	Level currentLevel;
	chrono::milliseconds startTimeMillis;
	int enemiesKilled;

	bool pause;

	void calculateScroll();
	float scrollX;
	float scrollY;
	
	list<Tile*> tiles;
	list<Character*> characters;
	list<Projectile*> projectiles;
	list<Collectable*> collectables;
	list<HUDText*> texts;
	Player* player;
	Background* background;
	Audio* backgroundMusic;
	InputController* inputController;

	HUDText* ammoText;
	HUDText* healthText;
	HUDText* focusText;
	
	LevelCompleteLayer* levelCompleteLayer;
private:
	static GameLayer* _instance;
	GameLayer(Game* game);
};

