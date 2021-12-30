#include "ControlsLayer.h"
#include "GameLayer.h"

ControlsLayer* ControlsLayer::_instance = NULL;

ControlsLayer* ControlsLayer::instance(Game* game) {
	if (_instance == NULL)
		_instance = new ControlsLayer(game);
	return _instance;
}

ControlsLayer::ControlsLayer(Game* game) : MenuLayer("res/controls.png", game) {}

void ControlsLayer::onContinue() {
	GameLayer* gameLayer = GameLayer::instance(game);
	gameLayer->setToFirstLevel();
	game->changeLayer(gameLayer);
}