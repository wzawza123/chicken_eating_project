#pragma once
#ifndef _Item_H_
#define _Item_H_

#include"cocos2d.h"
#include "const.h"
using namespace itemConsts;
using namespace cocos2d;

class Item : public Node
{
public:
	Sprite* getSprite();	
	void bindSprite(Sprite* sprite);

	bool getState();
	void setState(bool InHand);
	void flipSprite(bool isFlip);//��ת����
	
protected:
	Sprite* mySprite;

	bool MyInHand = false;
};
#endif