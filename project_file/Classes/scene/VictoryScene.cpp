//
//  VictoryScene.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/8.
//
#include "VictoryScene.h"

USING_NS_CC;

Scene* Victory::createScene()
{
    return Victory::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Victory::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    
  
    clickItem = MenuItemImage::create(
                                           "victoryBackground.png",
                                           "victoryBackground.png",
                                           CC_CALLBACK_1(Victory::mainMenuCallback, this));

    if (clickItem == nullptr ||
        clickItem->getContentSize().width <= 0 ||
        clickItem->getContentSize().height <= 0)
    {
        problemLoading("'victoryBackground.png'");
    }
    else
    {
        float x = visibleSize.width/2;
        float y = visibleSize.height/2;
        clickItem->setPosition(Vec2(x,y));
    }
    
    closeButtonMenu = Menu::create(clickItem, NULL);
    closeButtonMenu->setPosition(Vec2::ZERO);
    this->addChild(closeButtonMenu, 1);
    
    labelTips = Label::createWithTTF("Click to return", "fonts\\IRANYekanBold.ttf",20 );
    if (labelTips == nullptr)
    {
        problemLoading("'fonts\\IRANYekanBold.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelTips->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/4 - labelTips->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(labelTips, 1);
    }
    
    victoryBackground = Sprite::create("Victory.png");
    if (victoryBackground == nullptr)
    {
        problemLoading("'Victory.png'");
    }
    else
    {
        //victoryBackground->setScale(0.5);
        //pauseBackground->setAnchorPoint(Vec2(visibleSize.width/2,visibleSize.height/2));
        // position the sprin the center of the screen
        victoryBackground->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(victoryBackground, 1);
    }
    
    return true;
}


void Victory::mainMenuCallback(Ref* pSender)
{
    //Close the cocos2d-x game over scene and jump to the start scene
    Director::getInstance()->replaceScene(HelloWorld::create());
}
