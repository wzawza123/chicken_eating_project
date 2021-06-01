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
	actor();
	int getHealthPoint();
	int getDefencePoint();
	bool doDamage(int attackPoint);
protected:
	Sprite* delegateSprite;
	bool canMove;
	bool isInvincible;
	int sHealthPoint;
	int sDefencePoint;
	int sActorType;
	void bindSprite(Sprite* sprite);
	bool bindPhysicalBody();
};
#endif