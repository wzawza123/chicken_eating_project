#include"Weapon.h"

Weapon::Weapon()
{
	myBullet = Bullet::create();
	MouseImage = Sprite::create("aimer.png");
	addChild(MouseImage);
}

int Weapon::GetPower()
{
	return MyWeaponPower;
}

void Weapon::SetPower(int power)
{
	MyWeaponPower = power;
}

void Weapon::SetShootingSpeed(float speed)
{
	ShootingSpeed = speed;
}

void Weapon::SetBulletCapacity(int capacity)
{
	BulletCapacity = capacity;
}

int Weapon::GetCapacity()
{
	return BulletCapacity;
}

float Weapon::GetShootingSpeed()
{
	return ShootingSpeed;
}

Bullet* Weapon::CreateBullet()
{
	return nullptr;
}

Vec2 Weapon::getWeaponPosition()
{
	return mySprite->getPosition();
}

void Weapon::update(float dt)
{

}

Sprite* Weapon::getMouseImage()
{
	return MouseImage;
}

int Weapon::getNowBulletAmount()
{
	return nowBulletAmount;
}
