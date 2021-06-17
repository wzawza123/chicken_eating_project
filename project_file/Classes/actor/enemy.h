//
//  enemy.h
//  PUBG
//
//  Created by wza on 2021/5/31.
//
#ifndef ENEMY_H
#define ENEMY_H
#include "actor.h"
#include "const.h"
class enemy :public actor
{
public:
	enemy(int x = 300,int y = 360);
private:
	
	void update(float delta);
	void generateVelocity(float delta);
	Vec2 velocity = Vec2(0,0);
};
#endif