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
using namespace cocos2d;
class hero :public actor
{
public:
    hero();
    
    int getMovingState()const;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
private:
    
    int currentMovingState;
    Point moveVec;
    bool pressedKey[5] = { 0 };
    void setMovingState(int state);
    void moveUpdate(float delta);
    void stopMoving();
    void update(float delta) override;
    void processJump();
    void calculateMoveVec();
};

#endif /* hero_h */
