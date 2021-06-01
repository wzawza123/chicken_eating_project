//
//  actor.cpp
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#include "actor.h"
actor::actor()
{
	canMove = true;
	isInvincible = false;
}
void actor::bindSprite(cocos2d::Sprite* sprite)
{
	delegateSprite = sprite;
	addChild(delegateSprite);
}
int actor::getHealthPoint()
{
	return sHealthPoint;
}
int actor::getDefencePoint()
{
	return sDefencePoint;
}
bool actor::doDamage(int attackPoint)
{
	int damage = attackPoint - this->getDefencePoint();
	if(damage<0)
	{
		
	}
	else
	{
		this->sHealthPoint -= damage;
		return sHealthPoint > 0;	//maybe he is dead
	}
	return true;
}