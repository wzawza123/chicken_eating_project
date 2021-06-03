
#include "enemy.h"
#include <cocos2d.h>
using namespace cocos2d;
enemy::enemy(int x,int y)
{
    bindSprite(Sprite::create("enemy.png"));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for enemy===================== ");
    }
    delegateSprite->setPosition(Point(x, y));
    bindPhysicalBody();
    scheduleUpdate();
}
void enemy::update(float delta)
{
    delegateSprite->getPhysicsBody()->setVelocity(Vec2(rand() % 30-15, rand() % 30-15));
}