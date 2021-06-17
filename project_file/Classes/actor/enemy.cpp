
#include "enemy.h"
#include <cocos2d.h>
using namespace cocos2d;
enemy::enemy(int x,int y)
{
    sActorType=actorConsts::at_enemy;
    bindSprite(Sprite::create("Actor\\Monster\\O_small_monster2.png"));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for enemy===================== ");
    }
    //auto moveAction = createAnimation("monster", "Monster\\O_small");
    //delegateSprite->runAction(moveAction);
    delegateSprite->setPosition(Point(x, y));
    bindPhysicalBody();
    scheduleUpdate();
    schedule(CC_SCHEDULE_SELECTOR(enemy::generateVelocity),  actorConsts::eneMoveUpdateTime);
}
void enemy::update(float delta)
{
    
}
void enemy::generateVelocity(float delta)
{
    int genx, geny;
    genx = rand() % (actorConsts::eneMaxVol*2) - actorConsts::eneMaxVol;
    geny = rand() % (actorConsts::eneMaxVol * 2) - actorConsts::eneMaxVol;
    velocity = Vec2(genx, geny);
    if (fabs(genx) > 1e-6)
    {
        if (genx < 0)
        {
            delegateSprite->setFlippedX(true);
        }
        else
        {
            delegateSprite->setFlippedX(false);
        }
    }
    delegateSprite->getPhysicsBody()->setVelocity(velocity);
    log("position:%d %d", delegateSprite->getPosition().x, delegateSprite->getPosition().y);
}