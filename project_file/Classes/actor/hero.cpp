//
//  hero.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/25.
//

#include "hero.h"
int hero::heroCount = 0;
hero* hero::presentHero = nullptr;


hero::hero(int x, int y, const char* heroName)
{
    if (presentHero == nullptr)
    {
        presentHero = this;
    }
    moveAction = createAnimation("move", "knight");
    index = heroCount++;
    isJumping = false;
    canJump = true;
    currentMovingState = actorConsts::ms_standing;
    moveVec = Point(0, 0);
    //绑定键盘监听器
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    
    scheduleUpdate();
    sActorType = at_player;
    auto sprite = Sprite::create("Actor\\knight_rest1.png");
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for hero===================== ");
    }
    bindSprite(sprite);

    delegateSprite->setContentSize(Size(actorConsts::sizeOfContext[at_player][0], actorConsts::sizeOfContext[at_player][1]));
    bindPhysicalBody();
    delegateSprite->setPosition(Point(x, y));

    name = heroName;
    //设置名片
    playerID = Label::createWithTTF(name, "fonts\\arial.ttf", 12.f);
    if (playerID == nullptr)
    {
        log("=============failed to create hero label===============");
    }
    showNameLabel();
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

    delegateSprite->getPhysicsBody()->setVelocity(moveVec * moveDistance * moveSpeedRatio);
}
 
void hero::stopMoving()
{
    currentMovingState = actorConsts::ms_standing;
}
void hero::update(float dt)
{
    SetWeaponPosition();
    resetLabelPosition();
    moveUpdate(dt);    
    heroFire();
}
void hero::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    //log("key %d up", keycode);
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
    else if (keycode == EventKeyboard::KeyCode::KEY_R)//换子弹的实现
    {
        log("Add bullet to my weapon.");
        log("before BulletInventory is %d", myMainWeapon->getBulletInventory(myMainWeapon->weaponType));
        log("before BulletAmount is %d", myMainWeapon->getNowBulletAmount());
        log("before Capacity is %d", myMainWeapon->getCapacity());
        
        auto num = myMainWeapon->getCapacity() - myMainWeapon->getNowBulletAmount();//需要添加的子弹数

        if (myMainWeapon->getBulletInventory(myMainWeapon->weaponType) < num)//背包剩余子弹数少于需要加的子弹数
        {
            myMainWeapon->changeBulletamount(3, myMainWeapon->getBulletInventory(myMainWeapon->weaponType));
            myMainWeapon->setBulletInventory(0, myMainWeapon->getBulletInventory(myMainWeapon->weaponType), myMainWeapon->weaponType);
        }
        else //背包弹量充足，可以完整换弹
        {
            myMainWeapon->setBulletInventory(0, num, myMainWeapon->weaponType);
            myMainWeapon->changeBulletamount(2, 0);   
        }

        log("now BulletInventory is %d", myMainWeapon->getBulletInventory(myMainWeapon->weaponType));
        log("now BulletAmount is %d", myMainWeapon->getNowBulletAmount());
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_E)//拾取物品
    {
        log("pick something");
        isPicking = true;
        scheduleOnce(CC_SCHEDULE_SELECTOR(hero::stopPicking), pickTime);
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_G)//丢弃物品
    {
        log("drop something");
        dropWeapon();
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_F)//更换武器
    {
        log("Begin to change weapon");
        changeWeapon();
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
    float length = sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y);
    if (fabs(length) > 1e-6)
    {
        moveVec.x /= length;
        moveVec.y /= length;
        if (!isWalking)
        {
            isWalking = true;
            moveAction = createAnimation("move", "knight");
            delegateSprite->runAction(moveAction);
        }
    }
    else
    {
        if (isWalking)
        {
            isWalking = false;
            delegateSprite->stopAction(moveAction);
        }
    }
    //moveVec = Vec2(0, 0);
}
void hero::doJump()
{
    if (!isJumping && canJump)
    {
        isJumping = true;
        isInvincible = true;
        canJump = false;
        if (myMainWeapon)
        {
            myMainWeapon->setAttackState(false);
        }
        moveSpeedRatio *= jumpMoveSpeedRatio;
        delegateSprite->setScale(jumpScale);
        int rotateDegree = moveVec.x > 0 ? 360 : -360;
        delegateSprite->runAction(RotateBy::create(jumpTime, rotateDegree));
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
    if (myMainWeapon)
    {
        myMainWeapon->setAttackState(true);
    }
    scheduleOnce(CC_SCHEDULE_SELECTOR(hero::jumpRecover), jumpCD);
}
void hero::jumpRecover(float dt)
{
    canJump = true;
}

void hero::setMainWeapon(Weapon* pNewWeapon)
{
    myMainWeapon = pNewWeapon;
    pNewWeapon->setState(true);
}

void hero::SetWeaponPosition()
{
    auto myWorldPos = convertToWorldSpace(delegateSprite->getPosition());
    if (myWorldPos.x < MousePosition.x)
    {
        heroDirection = true;
    }
    else
    {
        heroDirection = false;

    }
    delegateSprite->setFlippedX(!heroDirection);
    myMainWeapon->flipSprite(!heroDirection);
    
    if (myMainWeapon != nullptr)
    {
        if (heroDirection == true)
            myMainWeapon->HeroPosition.x = (this->getSpritePosition().x + 24);
        else
            myMainWeapon->HeroPosition.x = (this->getSpritePosition().x - 24);
        myMainWeapon->HeroPosition.y = (this->getSpritePosition().y - 8);
    }
    if (mySecondWeapon != nullptr)
    {
        mySecondWeapon->HeroPosition = this->getSpritePosition();
    }

}

Weapon* hero::getMyMainWeapon()
{
    return myMainWeapon;
}

Weapon* hero::pickWeapon(Weapon* pNewWeapon)
{
    if (pNewWeapon->getState() == false) //判断武器是否被持有，若未被持有则可以拾取
    {
        pNewWeapon->setState(true);
        if (myMainWeapon != nullptr && mySecondWeapon == nullptr)//主武器不为空,副武器为空
        {
            mySecondWeapon = myMainWeapon;
            mySecondWeapon->getSprite()->setVisible(false);
            mySecondWeapon->getMouseImage()->setVisible(false);
            myMainWeapon = pNewWeapon;
            myMainWeapon->getMouseImage()->setVisible(true);
        }
        else if (myMainWeapon == nullptr)//主武器为空（相当于没有武器）
        {
            myMainWeapon = pNewWeapon;
            myMainWeapon->getMouseImage()->setVisible(true);
        }
        else//主副武器都满了
        {
            auto temp = myMainWeapon;
            temp->setState(false);
            temp->getMouseImage()->setVisible(false);
            temp->setPosition(this->getPosition());
            myMainWeapon = pNewWeapon;
            myMainWeapon->getMouseImage()->setVisible(true);
        }
    }
    return myMainWeapon;
}

void hero::changeWeapon()
{
    if (myMainWeapon != nullptr && mySecondWeapon != nullptr)
    {
        log("Change successfully!");
        auto temp = myMainWeapon;
        myMainWeapon = mySecondWeapon;
        mySecondWeapon = temp;
        myMainWeapon->getSprite()->setVisible(true);
        myMainWeapon->getMouseImage()->setVisible(true);
        mySecondWeapon->getSprite()->setVisible(false);
        mySecondWeapon->getMouseImage()->setVisible(false);
        
    }
    myMainWeapon->flipSprite(!heroDirection);//确保换武器时，武器的方向正确
}

void hero::setSecondWeapon(Weapon* pNewWeapon)
{
    mySecondWeapon = pNewWeapon;
    mySecondWeapon->getSprite()->setVisible(false);
    mySecondWeapon->getMouseImage()->setVisible(false);
    mySecondWeapon->setState(true);
}

void hero::heroFire()
{
    if (mouseKeys["Down"] == true)
    {
        myMainWeapon->Fire(MousePosition,heroDirection);
    }
}


bool hero::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    log("=========+++++++++++++++++++++++++++++++++++=========");
    if (isJumping)
    {

    }
    else
    {
        if (nodeA->getTag() == tagConsts::tagBullet || nodeB->getTag() == tagConsts::tagBullet)
        {
            this->doDamage(100);
            int a = getHealthPoint();
            log("====     %d      ====", a);
        }
        if (nodeA->getTag() == tagConsts::tagBarrier || nodeB->getTag() == tagConsts::tagBarrier)
        {
            this->delegateSprite->getPhysicsBody()->setVelocity(Vec2::ZERO);
        }
    }
    return true;
}

bool hero::getPickingState()
{
    return isPicking;
}

void hero::dropWeapon()
{
    /*有主武器且有副武器才可扔武器*/
    if (myMainWeapon != nullptr && mySecondWeapon != nullptr)
    {
        myMainWeapon->setState(false);
        myMainWeapon->getMouseImage()->setVisible(false);
        myMainWeapon->getSprite()->setPosition(myMainWeapon->HeroPosition);
        log("drop the mainWeapon");

        myMainWeapon = mySecondWeapon;
        myMainWeapon->getMouseImage()->setVisible(true);
        myMainWeapon->getSprite()->setVisible(true);
        mySecondWeapon = nullptr;
    }
    else
        log("You don't have mainWeapon.");
}

Weapon* hero::getMySecondWeapon()
{
    return mySecondWeapon;
}

void hero::stopPicking(float dt)
{
    isPicking = false;
    log("isPicking state turn to false");
}

void hero::showNameLabel()
{
    resetLabelPosition();
    addChild(playerID);
}

void hero::resetLabelPosition()
{
    Point labelPosition = delegateSprite->getPosition();
    labelPosition.y += 30;
    playerID->setPosition(labelPosition);
}
hero* hero::getInstance()
{
    return presentHero;
}