#pragma once
#include "Gun.h"
#include "Character.h"

class GunFactory
{
public:
	static Gun* forNumber(int nGun, Character* holder, Game* game);
};

