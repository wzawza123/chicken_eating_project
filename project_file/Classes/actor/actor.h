//
//  actor.h
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#ifndef actor_h
#define actor_h
#include<cocos2d.h>
class actor:public cocos2d::Node
{
private:
public:
	actor();
	int getHealthPoint();
	int getDefencePoint();
	bool doDamage(int attackPoint);
protected:
	cocos2d::Sprite* delegateSprite;
	bool canMove;
	bool isInvincible;
	int sHealthPoint;
	int sDefencePoint;
	void bindSprite(cocos2d::Sprite* sprite);
};
#endif