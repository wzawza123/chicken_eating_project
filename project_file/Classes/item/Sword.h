#pragma once


#ifndef _Sword_H_
#define _Sword_H_

#include "Item/Item.h"
#include"Item/Weapon.h"
using namespace cocos2d;


class Sword :public Weapon
{
public:
	Sword();
	bool init()override;
	void update(float dt) override;
	void changeBulletamount(int mode, int num) override;
	void Fire(Vec2 MousePosition, bool attackDirection) override;
	Animate*  attackAnimation(bool attackDirection);
	void attackEnd(float dt);
};

#endif