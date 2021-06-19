#include"Weapon.h"

int Weapon::nowBulletAmount = 0;
int Weapon::nowBulletInventory_1 = 40;
int Weapon::nowBulletInventory_2 = 40;

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

void Weapon::setBulletCapacity(const int capacity)
{
	Weapon::BulletCapacity = capacity;

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

int Weapon::getBulletInventory(int type)
{
	if (type == isPistol)
		return nowBulletInventory_1;
	else if (type == isRifle)
		return nowBulletInventory_2;

		return 0;

}

void Weapon::setBulletInventory(bool mode, int num,int type)
{
	if (mode==true)
	{
		if (type == isPistol)
			nowBulletInventory_1 += num;
		else if (type == isRifle)
			nowBulletInventory_2 += num;
	}
	else
	{
		if (type == isPistol)
			nowBulletInventory_1 -= num;
		else if (type == isRifle)
			nowBulletInventory_2 -= num;
	}
}

void Weapon::setAttackState(bool state)
{
	AttackState = state;
}
