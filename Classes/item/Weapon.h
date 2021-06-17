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

	void SetPower(int power);

	int GetPower();

	void SetShootingSpeed(float speed);

	float GetShootingSpeed();

	void SetBulletCapacity(int capacity);

	int GetCapacity();


	virtual Bullet* CreateBullet();

	virtual void update(float dt);

	Sprite* getMouseImage();

	int getNowBulletAmount();

	virtual void changeBulletamount(int mode) = 0;


	Vec2 getWeaponPosition();
	Vec2 MousePosition;
	Vec2 HeroPosition;
	
protected:
	Sprite* MouseImage;
    Bullet*  myBullet;
	int MyWeaponPower = 0;
	float ShootingSpeed = 0;
	int BulletCapacity = 0;
	int nowBulletAmount = 0;
};
#endif