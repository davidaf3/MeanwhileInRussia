#include "LevelCompleteLayer.h"
#include "InputController.h"
#include "EndLayer.h"

LevelCompleteLayer* LevelCompleteLayer::_instance = NULL;

LevelCompleteLayer* LevelCompleteLayer::instance(Game* game) {
	if (_instance == NULL)
		_instance = new LevelCompleteLayer(game);
	return _instance;
}

LevelCompleteLayer::LevelCompleteLayer(Game* game) : MenuLayer("res/level_complete.png", game) {
	gameLayer = GameLayer::instance(game);
}

string millisToString(int millis) {
	int seconds = (int) (millis / 1000);
	int minutes = (int) (seconds / 60);
	int remainingSeconds = seconds % 60;
	int remainingMillis = millis % 1000;

	string secondsString = (remainingSeconds < 10 ? "0" : "") + to_string(remainingSeconds);
	string millisString = to_string(remainingMillis);
	if (remainingMillis < 100)
		millisString = (remainingMillis < 10 ? "00" : "0") + millisString;

	return to_string(minutes) + ":" +  secondsString + "," + millisString;
}

string scoreToLetter(int score, SDL_Color* textColor) {
	textColor->a = 255;

	if (score < 50000) {
		textColor->r = 191;
		textColor->g = 255;
		textColor->b = 127;
		return "D";
	}

	if (score < 70000) {
		textColor->r = 255;
		textColor->g = 255;
		textColor->b = 127;
		return "C";
	}

	if (score < 90000) {
		textColor->r = 255;
		textColor->g = 223;
		textColor->b = 127;
		return "B";
	}

	if (score < 110000) {
		textColor->r = 255;
		textColor->g = 191;
		textColor->b = 127;
		return "A";
	}

	textColor->r = 255;
	textColor->g = 127;
	textColor->b = 127;
	return "S";
}

void LevelCompleteLayer::doInit() {
	SDL_Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;

	float enemiesKilledRate = (float)gameLayer->enemiesKilled / gameLayer->currentLevel.numberOfEnemies;
	chrono::milliseconds endTimeMillis =
		chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	int levelTime = endTimeMillis.count() - gameLayer->startTimeMillis.count();

	int enemiesScore = enemiesKilledRate * 100000;
	int timeScore = (gameLayer->currentLevel.parTime - levelTime) / 4;
	int score = enemiesScore + timeScore;

	// No ponemos puntuaciones menores que 0
	if (score < 0) score = 0;

	texts.clear();
	texts.push_back(new Text("res/Buran USSR.ttf", 30, to_string((int) (enemiesKilledRate * 100)) + "%", white, 280, 235, game));
	texts.push_back(new Text("res/Buran USSR.ttf", 30, millisToString(levelTime), white, 170, 325, game));
	texts.push_back(new Text("res/Buran USSR.ttf", 30, millisToString(gameLayer->currentLevel.parTime), white, 590, 325, game));
	texts.push_back(new Text("res/Buran USSR.ttf", 30, to_string(score) + " puntos", white, 200, 415, game));

	SDL_Color scoreColor;
	string scoreLetter = scoreToLetter(score, &scoreColor);
	texts.push_back(new Text("res/Buran USSR.ttf", 120, scoreLetter, scoreColor, 720, 430, game));
}

void LevelCompleteLayer::doDraw() {
	for (auto const& text : texts)
		text->draw();

	SDL_RenderPresent(game->renderer);
}

void LevelCompleteLayer::onContinue() {
	gameLayer->currentLevel.number++;

	if (gameLayer->currentLevel.number > gameLayer->lastLevel) {
		gameLayer->backgroundMusic->pause();
		game->changeLayer(EndLayer::instance(game));
		return;
	}

	game->changeLayer(gameLayer);
}