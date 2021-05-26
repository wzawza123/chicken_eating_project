#pragma once
#include<cocos2d.h>
#include "consts.h"
using namespace cocos2d;
class hero :public cocos2d::Node
{
public:
	hero();
	
	int getMovingState()const;				//获得运动状态
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);	//获取键盘事件
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
private:
	void bindSprite(cocos2d::Sprite* sprite);
	int currentMovingState;
	cocos2d::Sprite* delegateSprite;
	void setMovingState(int state);		//改变运动状态
	void moveUpdate();					//根据运动状态进行运动
	void stopMoving();					//原地停止
	void update(float delta) override;
};

