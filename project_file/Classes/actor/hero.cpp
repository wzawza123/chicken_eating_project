//
//  hero.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/25.
//

#include "hero.h"

int hero::heroCount = 0;
//hero的构造函数
hero::hero(int x,int y)
{
    //成员变量初始化
    index = heroCount++;   //为英雄分配id
    isJumping = false;
    canJump = true;
    currentMovingState = actorConsts::ms_standing;
    lastVec = Vec2(0, 0);
    moveVec = Vec2(0, 0);
    //绑定键盘监听器
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    //设定更新函数
    scheduleUpdate();
    sActorType = actorConsts::at_player;
    //绑定精灵
    bindSprite(Sprite::create("hero.png"));
    bindPhysicalBody();
    delegateSprite->setContentSize(Size(40,40));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for hero===================== ");
    }
    delegateSprite->setPosition(Point(x,y));
}
void hero::moveUpdate(float delta)
{
    if (!canMove)
    {
        return;
    }
    calculateMoveVec();
    Point currentPosition = delegateSprite->getPosition();
    Point movePosition = currentPosition;
    MoveBy* move_up = MoveBy::create(delta, Point(0, actorConsts::moveDistance));
    //log("hero:%d v:%f,%f", index,moveVec.x, moveVec.y);
    delegateSprite->getPhysicsBody()->setVelocity(moveVec * moveDistance * moveSpeedRatio);
    if (fabs(moveVec.x) > 1e-6)
    {
        if (moveVec.x<0)
		{
			delegateSprite->runAction(ScaleTo::create(0.f, -1.0f, 1.0f));
		}
		else
		{
			delegateSprite->runAction(ScaleTo::create(0.f, 1.0f, 1.0f));
		}
    }
}
Vec2 hero::getMovingState()const
{
    return moveVec;
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
    //log("key %d up", keycode);
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
    cocos2d::MoveBy* moveUp = cocos2d::MoveBy::create(moveTime, Point(0, actorConsts::moveDistance));
    cocos2d::MoveBy* moveDown = cocos2d::MoveBy::create(moveTime, Point(0, -actorConsts::moveDistance));
    cocos2d::MoveBy* moveLeft = cocos2d::MoveBy::create(moveTime, Point(-actorConsts::moveDistance, 0));
    cocos2d::MoveBy* moveRight = cocos2d::MoveBy::create(moveTime, Point(actorConsts::moveDistance, 0));
    //log("key %d down", keycode);
    if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        //log("pressed space");
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
//计算移动速度矢量
void hero::calculateMoveVec()
{
    lastVec = moveVec;
    moveVec = Vec2(0, 0);
    for (int i = 1; i <= 4; ++i)
    {
        if (pressedKey[i])
        {
            moveVec += actorConsts::moveVec[i];
        }
    }
    float length = sqrt(moveVec.x* moveVec.x + moveVec.y* moveVec.y);
    if (fabs(length) > 1e-6)
    {
		moveVec.x /= length;
		moveVec.y /= length;
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
        int rotateDegree = moveVec.x > 0 ? 360 : -360;
        delegateSprite->runAction(RotateBy::create(jumpTime,rotateDegree));
        scheduleOnce(CC_SCHEDULE_SELECTOR(hero::stopJump), jumpTime);
    }
}
void hero::stopJump(float dt)
{
    log("stop jumping");
    isJumping = false;
    isInvincible = false;
    moveSpeedRatio /= jumpMoveSpeedRatio;
    //log("%f", moveSpeedRatio);
    delegateSprite->setScale(1);
    scheduleOnce(CC_SCHEDULE_SELECTOR(hero::jumpRecover), jumpCD);
}
void hero::jumpRecover(float dt)
{
    canJump = true;
}

