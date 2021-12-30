#include "IntroLayer.h"
#include "ControlsLayer.h"

IntroLayer* IntroLayer::_instance = NULL;

IntroLayer* IntroLayer::instance(Game* game) {
	if (_instance == NULL)
		_instance = new IntroLayer(game);
	return _instance;
}

IntroLayer::IntroLayer(Game* game) : MenuLayer("res/intro.png", game) {}

void IntroLayer::onContinue() {
	game->changeLayer(ControlsLayer::instance(game));
}