#include "TMXLoader.h"
#include "tinyxml2.h"
#include "Enemy.h"
#include "GunCollectable.h"
#include "Medkit.h"
#include "FokusnoffBottle.h"
#include "BFG.h"
#include <map>

void getProperties(tinyxml2::XMLElement* propertiesElement, map<string, string>* properties) {
	tinyxml2::XMLElement* propertyEl;
	for (propertyEl = propertiesElement->FirstChildElement(); propertyEl != NULL; propertyEl = propertyEl->NextSiblingElement()) {
		string propertyName = propertyEl->Attribute("name");
		(*properties)[propertyName] = propertyEl->Attribute("value");
	}
}

void TMXLoader::loadMapTMX(string name, GameLayer* gameLayer, Level* level) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile(name.c_str());
	tinyxml2::XMLNode* mapNode = doc.FirstChildElement("map");

	level->mapWidth = stoi(mapNode->ToElement()->Attribute("width")) * tileSize;
	level->mapHeight = stoi(mapNode->ToElement()->Attribute("height")) * tileSize;

	// Propiedades del nivel
	map<string, string>* mapProperties = new map<string, string>;
	tinyxml2::XMLElement* propertiesElement = mapNode->FirstChildElement("properties");
	getProperties(propertiesElement, mapProperties);

	level->name = (*mapProperties)["name"];
	level->parTime = stoi((*mapProperties)["parTime"]);
	level->endLevelX = stof((*mapProperties)["endLevelX"]);

	delete mapProperties;

	// Tileset del nivel
	tinyxml2::XMLElement* tilesetElement = mapNode->FirstChildElement("tileset");
	const char* margin = tilesetElement->Attribute("margin");
	const char* spacing = tilesetElement->Attribute("spacing");
	level->tilesetMargin = margin != NULL ? stoi(margin) : 0;
	level->tilesetSpacing = spacing != NULL ? stoi(spacing) : 0;
	level->tilesetColumns = stoi(tilesetElement->Attribute("columns"));

	tinyxml2::XMLElement* imageElement = tilesetElement->FirstChildElement("image");
	stringstream tileset;
	tileset << "res/" << imageElement->Attribute("source");
	level->tileset = tileset.str();
	level->tilesetWidth = stoi(imageElement->Attribute("width"));
	level->tilesetHeight = stoi(imageElement->Attribute("height"));

	tinyxml2::XMLElement* c; // ChildMap
	// Procesar cada hijo del nodo <Map>, es decir cada "Capa"
	for (c = mapNode->FirstChildElement("layer"); c != NULL; c = c->NextSiblingElement()) {

		string name = c->Attribute("name");

		// Hijos de mapNode que tienen nombre Background* o Static*
		// string::npos , es como el null de los strings
		if (name.find("background") != string::npos
			|| name.find("static") != string::npos) {

			bool physic = false;
			if (name.rfind("static") != string::npos) {
				physic = true;
			}

			string tilesLayer1 = c->FirstChildElement("data")->GetText();
			string delimiterDoc = "\n";
			string delimiterLine = ",";
			size_t posLine = 0;
			string line, tileNum;

			// Por línea
			for (int i = 0; posLine != string::npos; i++) {
				posLine = tilesLayer1.find(delimiterDoc);
				line = tilesLayer1.substr(0, posLine);

				// El tiled a veces mete líneas vacías "", no contarlas;
				if (line == "") {
					i--;
				}

				size_t posCharacter = 0;
				for (int j = 0; posCharacter != string::npos; j++) {
					posCharacter = line.find(delimiterLine);
					tileNum = line.substr(0, posCharacter);

					float x = tileSize / 2 + j * tileSize; // x central
					float y = tileSize / 2 + i * tileSize; // y central

					if (tileNum != "" && tileNum != "0") {
						loadTMXTile(stoi(tileNum), x, y, physic, gameLayer, level);
					}
					line.erase(0, posCharacter + delimiterLine.length());
				}
				tilesLayer1.erase(0, posLine + delimiterDoc.length());
			}
		}

		// Capa de objetos "Players"
		if (name == "players") {
			tinyxml2::XMLNode* n;
			for (n = c->FirstChild(); n != NULL; n = n->NextSibling()) {
				string objectX = n->ToElement()->Attribute("x");
				string objectY = n->ToElement()->Attribute("y");

				gameLayer->player = new Player(stoi(objectX), stoi(objectY), 
					level->initialGunsInventory, level->initialAmmoInventory, level->initialGun, gameLayer->game);

				gameLayer->player->observers.push_back(gameLayer);
				for (auto const& text : gameLayer->texts)
					gameLayer->player->observers.push_back(text);

				gameLayer->space->addDynamicActor(gameLayer->player);
			}
		}

		// Capa de objetos "Enemies"
		if (name == "enemies") {
			int numberOfEnemies = 0;
			tinyxml2::XMLNode* n;
			for (n = c->FirstChild(); n != NULL; n = n->NextSibling()) {
				numberOfEnemies++;
				tinyxml2::XMLElement* element = n->ToElement();
				string objectX = element->Attribute("x");
				string objectY = element->Attribute("y");

				map<string, string>* enemyProperties = new map<string, string>;
				tinyxml2::XMLElement* propertiesElement = element->FirstChildElement("properties");
				getProperties(propertiesElement, enemyProperties);

				Enemy* enemy = new Enemy(stoi(objectX), stoi(objectY), gameLayer->game, stoi((*enemyProperties)["gun"]),
					gameLayer->player, (*enemyProperties)["kind"], stoi((*enemyProperties)["life"]), stof((*enemyProperties)["aim"]));
				enemy->observers.push_back(gameLayer);
				gameLayer->characters.push_back(enemy);
				gameLayer->space->addDynamicActor(enemy);

				delete enemyProperties;
			}
			level->numberOfEnemies = numberOfEnemies;
		}

		// Capa de objetos "Collectables"
		if (name == "collectables") {
			tinyxml2::XMLNode* n;
			for (n = c->FirstChild(); n != NULL; n = n->NextSibling()) {
				tinyxml2::XMLElement* element = n->ToElement();
				string objectX = element->Attribute("x");
				string objectY = element->Attribute("y");

				map<string, string>* collectableProperties = new map<string, string>;
				tinyxml2::XMLElement* propertiesElement = element->FirstChildElement("properties");
				getProperties(propertiesElement, collectableProperties);

				string collectableKind = (*collectableProperties)["kind"];
				Collectable* collectable;

				if (collectableKind == "bfg") collectable = new GunCollectable(new BFG(gameLayer->game, stof(objectX), stof(objectY)));
				else if (collectableKind == "medkit") collectable = new Medkit(stof(objectX), stof(objectY), gameLayer->game);
				else if (collectableKind == "bottle") collectable = new FokusnoffBottle(stof(objectX), stof(objectY), gameLayer->game);

				gameLayer->collectables.push_back(collectable);
				gameLayer->space->addDynamicActor(collectable);
				delete collectableProperties;
			}
		}
	}
}

void TMXLoader::loadTMXTile(int tileNum, float x, float y, bool physic, GameLayer* gameLayer, Level* level) {
	Tile* tile = new Tile(level->tileset, tileNum, x, y, level->tilesetWidth, level->tilesetHeight, gameLayer->game, level);
	gameLayer->tiles.push_back(tile);

	if (physic) { // Si es un suelo o pared tiene que ir al Space
		gameLayer->space->addStaticActor(tile);
	}
}