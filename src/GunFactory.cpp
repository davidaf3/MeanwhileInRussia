#include "GunFactory.h"
#include "Pistol.h"
#include "SMG.h"
#include "AssaultRifle.h"
#include "MachineGun.h"
#include "Shotgun.h"
#include "SniperRifle.h"
#include "RicochetGun.h"
#include "BFG.h"

Gun* GunFactory::forNumber(int nGun, Character* holder, Game* game) {
	switch (nGun)
	{
	case 1:
		return new SMG(game, holder, SMG::smgMagSize);
	case 2:
		return new Shotgun(game, holder, Shotgun::sgMagSize);
	case 3:
		return new AssaultRifle(game, holder, AssaultRifle::arMagSize);
	case 4:
		return new MachineGun(game, holder, MachineGun::mgMagSize);
	case 5:
		return new SniperRifle(game, holder, SniperRifle::sMagSize);
	case 6:
		return new RicochetGun(game, holder, RicochetGun::rgMagSize);
	case 7:
		return new BFG(game, holder);
	default:
		return new Pistol(game, holder, Pistol::pistolMagSize);
	}
}