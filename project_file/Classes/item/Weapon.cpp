#include"Weapon.h"

int Weapon::nowBulletAmount = 0;
int Weapon::BulletCapacity = 0;

Weapon::Weapon()
{
	myBullet = Bullet::create();
	MouseImage = Sprite::create("aimer.png");
	addChild(MouseImage);
}

int Weapon::getPower()
{
	return MyWeaponPower;
}

void Weapon::setPower(int power)
{
	MyWeaponPower = power;
}

void Weapon::setShootingSpeed(float speed)
{
	ShootingSpeed = speed;
}

void Weapon::setBulletCapacity(int capacity)
{
	BulletCapacity = capacity;
}

int Weapon::getCapacity()
{
	return BulletCapacity;
}

float Weapon::getShootingSpeed()
{
	return ShootingSpeed;
}

Vec2 Weapon::getWeaponPosition()
{
	return mySprite->getPosition();
}


Sprite* Weapon::getMouseImage()
{
	return MouseImage;
}

int Weapon::getNowBulletAmount()
{
	return nowBulletAmount;
}

void Weapon::restoreAttackState(float dt)
{
	AttackState = true;
}
void Weapon::setAttackState(bool state)
{
	AttackState = state;
}
