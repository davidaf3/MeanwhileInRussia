#pragma once

class Enemy;

class Player;

class EnemyState
{
public:
	virtual void draw(Enemy* enemy, float scrollX, float scrollY);
	virtual void update(Enemy* enemy);
	virtual void onDead(Enemy* enemy);
};

