//
//  const.h
//  PUBG
//
//  Created by PC1 on 2021/5/23.
//

#ifndef const_h
#define const_h

#pragma once
#include <cocos2d.h>
using namespace cocos2d;
//class hero
//const float moveTime = 3.0f;
namespace actorConsts
{
    enum actorType
    {
        at_null, at_player,at_enemy
    };
    const int sizeOfContext[3][2] = { {0,0},{52,52},{48,48} }; //width height
    const int moveDistance = 100;
    const int maxHealthPoint = 600;
    const int maxArmorPoint = 300;

    const float jumpMoveSpeedRatio = 1.5;
    const float jumpTime = 0.50;
    const float jumpScale = 1.1;
    const float jumpCD = 2.0;
    const float pickTime = 1.0f;
    const Point moveVec[5] = { Point(0,0),Point(0,1),Point(0,-1),Point(-1,0),Point(1,0) };
    enum movingState {ms_standing, ms_up, ms_down, ms_left, ms_right };
    const EventKeyboard::KeyCode directionKeyCode[5] = {
            EventKeyboard::KeyCode::KEY_0,
            EventKeyboard::KeyCode::KEY_W,
            EventKeyboard::KeyCode::KEY_S,
            EventKeyboard::KeyCode::KEY_A,
            EventKeyboard::KeyCode::KEY_D
    };

    const int eneMaxVol = 60;
    const int eneMoveUpdateTime = 1;
    const int enemyHealth = 1000;
}

namespace itemConsts
{
    /*手枪相关参数*/
    const int pistolPower = 1;//手枪子弹威力
    const int pistolBulletCapacity = 5;//弹夹容量
    const float pistolShottingSpeed = 0.2f;//每个子弹发射时间间隔

    /*刀相关参数*/
    const int swordPower = 1;
    const float swordAttackSpeed = 0.6f;

    /*来福步枪相关参数*/
    const int riflePower = 1;
    const int rifleBulletCapacity = 30;
    const float rifleShottingSpeed = 0.1f;

    //当前主武器
    const int isKnife = 0;
    const int isPistol = 1;
    const int isRifle = 2;


}

namespace tagConsts
{
    const int tagHero = 10;
    const int tagBarrier = 20;
    const int tagBullet = 30;
    const int tagEnemyStart = 40;
}

namespace gameConsts
{
    const int maxEnemy = 20;
    const int enemyCount = 2;
    const int maxPlayer = 10;
}

//int BLOOD_BAR=1;
//int PLAYER_LIFE=100;
#endif /* const_h */

