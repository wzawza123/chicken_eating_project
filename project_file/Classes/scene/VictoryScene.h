//
//  VictoryScene.h
//  PUBG
//
//  Created by PC1 on 2021/6/8.
//

#ifndef VictoryScene_h
#define VictoryScene_h

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class Victory : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    void mainMenuCallback(Ref* pSender);
    
    CREATE_FUNC(Victory);
    
private:
    Sprite* victoryBackground;
    
    MenuItemImage* clickItem;
    
    Menu* closeButtonMenu;
    
    Label* labelTips;
    
};

#endif /* VictoryScene_h */
