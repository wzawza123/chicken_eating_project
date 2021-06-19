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

	int getCapacity();

	virtual void update(float dt) = 0;

	Sprite* getMouseImage();

	static int getNowBulletAmount();

	virtual void changeBulletamount(int mode,int num) = 0;

	Vec2 getWeaponPosition();
	Vec2 HeroPosition;

	int weaponType = 0;

	void restoreAttackState(float dt);
	virtual void Fire(Vec2 MousePosition,bool attackDirection) = 0;
	Vec2 viewPosition;//处理相机移动问题

	static int getBulletInventory(int type);

	void setBulletInventory(bool mode,int num,int type);//mode1为增加，，0为减少

	void setAttackState(bool state);
protected:
	Sprite* MouseImage;
    Bullet*  myBullet;
	int MyWeaponPower = 0;
	float ShootingSpeed = 0;
	
	static int nowBulletAmount;//该武器在弹夹中的子弹数量
	bool AttackState = true;
	static int nowBulletInventory_1;//现背包中该手枪的子弹数量
	static int nowBulletInventory_2;//现背包中该步枪的子弹数量
	int BulletCapacity;//手枪的子弹容量
};
#endif