//
//  OnlineJoinScene.h
//  PUBG
//
//  Created by PC1 on 2021/6/15.
//

#ifndef OnlineJoinScene_h
#define OnlineJoinScene_h
#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace ui;


class OnlineJoin : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    //EditBox* editBox;
    
    const char* roomNum;
    
    CREATE_FUNC(OnlineJoin);
    
private:
    
    
    
};


#endif /* OnlineJoinScene_h */
