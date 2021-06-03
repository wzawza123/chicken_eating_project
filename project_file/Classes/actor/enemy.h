//
//  enemy.h
//  PUBG
//
//  Created by wza on 2021/5/31.
//
#ifndef ENEMY_H
#define ENEMY_H
#include "actor.h"
class enemy :public actor
{
public:
	enemy(int x = 300,int y = 400);
private:
	void update(float delta);
};
#endif