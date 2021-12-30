#pragma once
#include "EnemyState.h"
class EnemyStateDead :
    public EnemyState
{
public:
	void draw(Enemy* enemy, float scrollX, float scrollY) override;
	void update(Enemy* enemy) override;
	void onDead(Enemy* enemy) override;
	static EnemyStateDead* instance();
private:
	static EnemyStateDead* _instance;
	EnemyStateDead();
};
