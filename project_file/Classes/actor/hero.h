//
//  hero.h
//  PUBG
//
//  Created by PC1 on 2021/5/25.
//

#ifndef hero_h
#define hero_h

#pragma once
#include<cocos2d.h>
#include "const.h"
#include "actor/actor.h"
#include "Item/Weapon.h"
#include "Item/Pistol.h"
#include "Item/Sword.h"
#include "item/rifle.h"
//#include "general/general.h"
using namespace cocos2d;
using namespace tagConsts;

class hero :public actor
{
public:
    bool isJumping;
    bool canJump;
    hero(int x = 200, int y = 300, const char* heroName = "hero");
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    bool onContactBegin(PhysicsContact& contact);
    void setMainWeapon(Weapon* pNewWeapon);//设置主武器
    void setSecondWeapon(Weapon* pNewWeapon);//设置副武器
    void SetWeaponPosition();//设置武器位置
    Weapon* getMyMainWeapon();//获取主武器
    Weapon* getMySecondWeapon();//获取副武器
    Weapon* pickWeapon(Weapon* pNewWeapon);//拾取武器
    void changeWeapon();//更换主武器
    std::map<std::string, bool> mouseKeys;//记录鼠标的按键状态
    Vec2 MousePosition;
    bool getPickingState();
    void dropWeapon();
    void stopPicking(float dt);
    std::string name;
    static hero* getInstance();
private:
    static hero* presentHero;
    void showNameLabel();
    void resetLabelPosition();
    bool isPicking = false;
    Label* playerID;
    static int heroCount;
    int index;
    int currentMovingState;
    Point moveVec;
    bool pressedKey[5] = { 0 };
    void moveUpdate(float delta);
    void stopMoving();
    void update(float delta) override;
    void calculateMoveVec();
    void doJump();
    void stopJump(float dt);
    void jumpRecover(float dt); 

    Weapon* myMainWeapon = nullptr;//主武器
    Weapon* mySecondWeapon = nullptr;//副武器
    bool heroDirection = true;//英雄方向，1为右，0为左
    void heroFire();
    Animate* moveAction;
    int pistolBullet = 20;//英雄持有的手枪子弹数
};


#endif /* hero_h */
