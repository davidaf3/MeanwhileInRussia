#pragma once

#include "Actor.h"
#include <list>

class Space
{
public:
	Space(float gravity);
	void update();
	void updateMoveRight(Actor* dynamicAct, float vx, bool restrict);
	void updateMoveLeft(Actor* dynamicAct, float vx, bool restrict);
	void updateMoveDown(Actor* dynamicAct, float vy, bool restrict);
	void updateMoveTop(Actor* dynamicAct, float vy, bool restrict);
	void addDynamicActor(Actor* actor);
	void addStaticActor(Actor* actor);
	void removeDynamicActor(Actor* actor);
	void removeStaticActor(Actor* actor);
	bool isRectFree(float x, float y, float width, float height);
	bool isSegmentFree(float x1, float y1, float x2, float y2);
	float gravity;
	list<Actor*> dynamicActors;
	list<Actor*> staticActors;
};

