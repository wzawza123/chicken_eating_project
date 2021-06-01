//
//  hero.cpp
//  PUBG
//
//  Created by wza 2021-5-26
//

#include "hero.h"
hero::hero()
{
    isJumping = false;
    canJump = true;
    currentMovingState = actorConsts::ms_standing;
    moveVec = Point(0, 0);
    //绑定键盘监听器
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    scheduleUpdate();
    sActorType = at_null;
    bindSprite(Sprite::create("player.png"));
    bindPhysicalBody();
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for hero===================== ");
    }
    delegateSprite->setPosition(Point(100, 200));
}
void hero::setMovingState(int state)
{
    currentMovingState = state;
}
void hero::moveUpdate(float delta)
{
    //log("called move update");
    //log("currentMovingState:%d", currentMovingState);
    if (!canMove)
    {
        return;
    }
    calculateMoveVec();
    Point currentPosition = delegateSprite->getPosition();
    Point movePosition = currentPosition;
    MoveBy* move_up = MoveBy::create(delta, Point(0, actorConsts::moveDistance));
    //log("x:%d y:%d", currentPosition.x, currentPosition.y);
    //MoveBy* move = MoveBy::create(delta, moveVec*actorConsts::moveDistance);
    //delegateSprite->runAction(move);
    delegateSprite->getPhysicsBody()->setVelocity(moveVec * moveDistance * moveSpeedRatio);
}
void hero::processJump()
{
}
int hero::getMovingState()const
{
    return currentMovingState;
}
void hero::stopMoving()
{
    currentMovingState = actorConsts::ms_standing;
}
void hero::update(float dt)
{
    moveUpdate(dt);    //»ÀŒÔŒª÷√µƒ∏¸–¬
}
void hero::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    log("key %d up", keycode);
    /*if (currentMovingState == actorConsts::ms_standing)
    {
        return;
    }
    if (keycode == actorConsts::directionKeyCode[currentMovingState])
    {
        stopMoving();
    }*/
	for (int i = 1; i <= 4; ++i)
	{
		if (keycode == actorConsts::directionKeyCode[i])
		{
			pressedKey[i] = false;
		}
	}
}
void hero::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    float moveTime = 0.01f;
    log("key %d down", keycode);
    if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        log("pressed space");
        doJump();
    }
    else
    {
        
        for (int i = 1; i <= 4; ++i)
        {
            if (keycode == actorConsts::directionKeyCode[i])
            {
                pressedKey[i] = true;
            }
        }
    }
    //player.moveUpdate();
}
void hero::calculateMoveVec()
{
    moveVec = Point(0, 0);
    for (int i = 1; i <= 4; ++i)
    {
        if (pressedKey[i])
        {
            moveVec += actorConsts::moveVec[i];
        }
    }
}
void hero::doJump()
{
    if (!isJumping&&canJump)
    {
        isJumping = true;
        isInvincible = true;
        canJump = false;
        moveSpeedRatio *= jumpMoveSpeedRatio;
        delegateSprite->setScale(jumpScale);
        float rollingDegeree = delegateSprite->getPhysicsBody()->getVelocity().x < 0 ? -360 : 360;
        delegateSprite->runAction(RotateBy::create(jumpTime,rollingDegeree));
        scheduleOnce(CC_SCHEDULE_SELECTOR(hero::stopJump), jumpTime);
    }
}
void hero::stopJump(float dt)
{
    log("stop jumping");
    isJumping = false;
    isInvincible = false;
    moveSpeedRatio /= jumpMoveSpeedRatio;
    log("%f", moveSpeedRatio);
    delegateSprite->setScale(1);
    scheduleOnce(CC_SCHEDULE_SELECTOR(hero::jumpRecover), jumpCD);
}
void hero::jumpRecover(float dt)
{
    canJump = true;
}