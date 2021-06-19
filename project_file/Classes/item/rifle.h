#pragma once

#ifndef _Rifle_H_
#define _Rifle_H_

#include "item/Item.h"
#include"item/Weapon.h"
using namespace cocos2d;

class Rifle :public Weapon
{
public:
	Rifle();
	Bullet* shootBullet(Vec2 vec);
	void changeBulletamount(int mode, int num) override;
	bool init() override;
	void update(float dt) override;
	void Fire(Vec2 MousePosition, bool attackDirection) override;
	CREATE_FUNC(Rifle);
};



#endif