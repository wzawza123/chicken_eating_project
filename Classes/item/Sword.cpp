#include"Sword.h"

Sword::Sword()
{
	bindSprite(Sprite::create("sword.png"));
	if (mySprite == nullptr)
	{
		log("pistol.png is not found");
	}
	scheduleUpdate();


	SetPower(swordPower);

	SetShootingSpeed(0);
	SetBulletCapacity(0);
}

bool Sword::init()
{
	return true;
}

void Sword::update(float dt)
{
	if (this->getState() == true)
	{
		mySprite->setPosition(HeroPosition.x + 24, HeroPosition.y - 10);
	}
	else
		;
}

void Sword::changeBulletamount(int mode)
{
	;
}