#pragma once
#include<cocos2d.h>
#include "consts.h"
using namespace cocos2d;
class hero :public cocos2d::Node
{
public:
	hero();
	
	int getMovingState()const;				//����˶�״̬
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);	//��ȡ�����¼�
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
private:
	void bindSprite(cocos2d::Sprite* sprite);
	int currentMovingState;
	cocos2d::Sprite* delegateSprite;
	void setMovingState(int state);		//�ı��˶�״̬
	void moveUpdate();					//�����˶�״̬�����˶�
	void stopMoving();					//ԭ��ֹͣ
	void update(float delta) override;
};

