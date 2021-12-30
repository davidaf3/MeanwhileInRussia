#pragma once
#include "EnemyState.h"

class AliveEnemyState :
    public EnemyState
{
public:
    static AliveEnemyState* instance();
private:
    static AliveEnemyState* _instance;
    AliveEnemyState();
};

