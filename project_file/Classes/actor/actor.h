//
//  actor.h
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#ifndef actor_h
#define actor_h
#include<cocos2d.h>
#include "const.h"
using namespace cocos2d;
using namespace actorConsts;
class actor:public Node
{
private:
public:
	Sprite* delegateSprite;
	actor();
	int getHealthPoint();
	int getDefencePoint();
	bool doDamage(int attackPoint);
	Vec2 getSpritePosition();
protected:
	bool canMove;
	bool isInvincible;
	float moveSpeedRatio;
	int sHealthPoint;
	int sDefencePoint;
	int sActorType;
	void bindSprite(Sprite* sprite);
	bool bindPhysicalBody();
};
#endif