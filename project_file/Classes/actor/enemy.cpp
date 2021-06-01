
#include "enemy.h"
#include <cocos2d.h>
using namespace cocos2d;
enemy::enemy()
{
    bindSprite(Sprite::create("enemy.png"));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for enemy===================== ");
    }
    delegateSprite->setPosition(Point(100, 200));
}