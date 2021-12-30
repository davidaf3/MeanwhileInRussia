#pragma once
#include "MenuLayer.h"
#include "GameLayer.h"
#include "Text.h"

class LevelCompleteLayer :
    public MenuLayer
{
public:
	static LevelCompleteLayer* instance(Game* game);
	void doInit() override;
	void doDraw() override;

	void onContinue() override;

	GameLayer* gameLayer;
	list<Text*> texts;
	bool unpause = false;
private:
	static LevelCompleteLayer* _instance;
	LevelCompleteLayer(Game* game);
};

