#include"Pistol.h"


Pistol::Pistol()
{
	Size winSize = Director::getInstance()->getWinSize();
	bindSprite(Sprite::create("pistol.png"));
	if (mySprite == nullptr)
	{
		log("pistol.png is not found");
	}
	scheduleUpdate();

	SetPower(pistolPower);
	SetBulletCapacity(pistolBulletCapacity);
}

bool Pistol::init()
{
	return true;
}

void Pistol::update(float dt) 
{
	mySprite->setPosition(HeroPosition.x + 24, HeroPosition.y - 5);
}

Bullet* Pistol::shootBullet(Vec2 vec)
{
	Bullet* newBullet = Bullet::create();
	newBullet->setPosition(getWeaponPosition());
	newBullet->m_pBulletSprite->getPhysicsBody()->setVelocity( vec);
	return newBullet;
}

void Pistol::changeBulletamount(int mode)
{
	switch (mode)
	{
		case 1:
			nowBulletAmount--;
			break;
		case 2:
			nowBulletAmount = pistolBulletCapacity;
			break;
	}
}