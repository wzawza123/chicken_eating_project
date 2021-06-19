//
//  GuestWaitScene.h
//  PUBG
//
//  Created by PC1 on 2021/6/18.
//

#ifndef GuestWaitScene_h
#define GuestWaitScene_h

#include "cocos2d.h"

USING_NS_CC;

class GuestWait : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    //EditBox* editBox;
    
    const char* roomNum;
    
    CREATE_FUNC(GuestWait);
    
private:
    
    
    
};

#endif /* GuestWaitScene_h */
