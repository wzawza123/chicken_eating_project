//
//  actor.cpp
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#include "actor.h"
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