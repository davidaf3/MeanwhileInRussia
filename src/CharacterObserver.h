#pragma once

class Character;

class Projectile;

class GunCollectable;

class CharacterObserver
{
public:
	virtual void onCharacterDead(Character* character, GunCollectable* droppedGun) {}
	virtual void onEnemyKilled() {}
	virtual void onCharacterFire(Projectile* projectile) {}
	virtual void onCharacterAmmoChange(Character* character) {}
	virtual void onCharacterHealthChange(Character* character) {}
	virtual void onCharacterFocusChange(Character* character) {}
};

