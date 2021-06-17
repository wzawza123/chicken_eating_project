#pragma once

#ifndef _Weapon_H_
#define _Weapon_H_

#include "Item.h"
#include "Bullet.h"

using namespace cocos2d;

class Weapon :public Item
{
public:
	Weapon();

	void setPower(int power);

	int getPower();

	void setShootingSpeed(float speed);

	float getShootingSpeed();

	void setBulletCapacity(int capacity);

	static int getCapacity();

	virtual void update(float dt) = 0;

	Sprite* getMouseImage();

	static int getNowBulletAmount();

	virtual void changeBulletamount(int mode) = 0;

	Vec2 getWeaponPosition();
	Vec2 HeroPosition;

	int weaponType = 0;

	void restoreAttackState(float dt);
	void setAttackState(bool state);
	virtual void Fire(Vec2 MousePosition,bool attackDirection) = 0;
	Vec2 viewPosition;//处理相机移动问题

protected:
	Sprite* MouseImage;
    Bullet*  myBullet;
	int MyWeaponPower = 0;
	float ShootingSpeed = 0;
	static int BulletCapacity;
	static int nowBulletAmount;
	bool AttackState = true;
	
};
#endif