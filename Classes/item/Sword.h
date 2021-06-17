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
	void changeBulletamount(int mode) override;
protected:
};

#endif