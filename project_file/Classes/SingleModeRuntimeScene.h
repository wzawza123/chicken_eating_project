//
//  SingleModeRuntimeScence.h
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#ifndef SingleModeRuntimeScene_h
#define SingleModeRuntimeScene_h

//#pragma once
#include "cocos2d.h"
#include "Box2D.h"
#include "actor\hero.h"

USING_NS_CC;

class SingleModeRuntime : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    hero player;
    
    void menuPauseCallback(Ref* pSender);
    
    void menuCloseCallback(Ref* pSender);
    
    static void scheduleBlood(float delta);
    
    //生成物理世界
    void initPhysical();
    
   
    
    
    //暂停界面回调
    //void pauseByKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    
    CREATE_FUNC(SingleModeRuntime);
    
    b2World * world;
    
    TMXTiledMap *testMap;
};


#endif /* SingleModeRuntimeScence_h */
