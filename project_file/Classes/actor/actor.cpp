//
//  actor.cpp
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#include "actor.h"
//actor* actor::presentHero=nullptr;
//
//  actor.cpp
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#include "actor.h"
#include "const.h"

int actor::sHealthPoint = actorConsts::maxHealthPoint;
int actor::sDefencePoint = actorConsts::maxArmorPoint;


actor::actor()
{
    canMove = true;
    isInvincible = false;
    delegateSprite = nullptr;
    sActorType = at_null;
    moveSpeedRatio = 1.0;
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
    if (attackPoint < 0)
    {

    }
    else
    {
        if (sDefencePoint > 0)
        {
            sDefencePoint -= attackPoint;
            sDefencePoint = sDefencePoint > 0 ? sDefencePoint : 0;
        }
        else
        {
            if (sHealthPoint <= 0)
            {
                return false;
            }
            else
            {
                sHealthPoint -= attackPoint;
                if (sHealthPoint <= 0)
                {
                    return false;
                }
                else
                {
                    sHealthPoint -= attackPoint;
                }
            }
        }
    }
    return true;
}
bool actor::bindPhysicalBody()
{
    if (this->delegateSprite == nullptr)
    {
        log("failed to bind physical body for no sprite");
        return false;
    }
    else
    {
        PhysicsBody* phyBody = PhysicsBody::createBox(Size(sizeOfContext[sActorType][0], sizeOfContext[sActorType][1]));
        phyBody->setDynamic(true);
        phyBody->setCategoryBitmask(1);
        phyBody->setCollisionBitmask(1);
        phyBody->setContactTestBitmask(1);
        phyBody->setRotationEnable(false);
        delegateSprite->setPhysicsBody(phyBody);
    }
    return true;
}
Vec2 actor::getSpritePosition()
{
    return delegateSprite->getPosition();
}

Animate* actor::createAnimation(const char* animationName, const char* actorName)
{
    int iFrameNum = 4;
    SpriteFrame* frame = NULL;
    Vector<SpriteFrame*> frameVec;
    for (int i = 1; i <= iFrameNum; i++)
    {
        frame = SpriteFrame::create(StringUtils::format("Actor\\%s_%s%d.png", actorName, animationName, i), Rect(0, 0, actorConsts::sizeOfContext[sActorType][0], actorConsts::sizeOfContext[sActorType][1]));
        frameVec.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(-1);//设置重复次数
    animation->setDelayPerUnit(0.05f);
    Animate* action = Animate::create(animation);
    return action;
}