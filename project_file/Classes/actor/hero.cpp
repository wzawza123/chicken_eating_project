#include "hero.h"
hero::hero()
{
	currentMovingState = ms_standing;	//目前的运动方向为站立
	//监听键盘
	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	scheduleUpdate();
	bindSprite(Sprite::create("sprite1.png"));
	if (delegateSprite == nullptr)
	{
		log("==============failed to create sprite for hero===================== ");
	}
	delegateSprite->setPosition(Point(100, 200));
}
void hero::setMovingState(int state)
{
	currentMovingState = state;			//改变运动状态
}
void hero::moveUpdate()
{
	log("called move update");
	log("currentMovingState:%d", currentMovingState);
	Point currentPosition = delegateSprite->getPosition();
	Point movePosition = currentPosition;
	switch (currentMovingState)
	{
		case ms_up:
			movePosition.y += moveDistance;
			break;
		case ms_down:
			movePosition.y -= moveDistance;
			break;
		case ms_left:
			movePosition.x -= moveDistance;
			break;
		case ms_right:
			movePosition.x += moveDistance;
			break;
		default:
			break;
	}
	log("x:%d y:%d", currentPosition.x, currentPosition.y);
	delegateSprite->setPosition(movePosition);
}
void hero::bindSprite(cocos2d::Sprite* sprite)
{
	delegateSprite = sprite;
	addChild(delegateSprite);		//作为子对象来进行渲染
}
int hero::getMovingState()const
{
	return currentMovingState;
}
void hero::stopMoving()
{
	currentMovingState = ms_standing;
}
void hero::update(float dt)
{
	moveUpdate();	//人物位置的更新
}
void hero::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	log("key %d up", keycode);
	if (currentMovingState == ms_standing)
	{
		return;
	}
	if (keycode == directionKeyCode[currentMovingState])
	{
		stopMoving();
	}
}
void hero::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	float moveTime = 0.01f;
	int moveDistance = 1;
	cocos2d::MoveBy* moveUp = cocos2d::MoveBy::create(moveTime, Point(0, moveDistance));
	cocos2d::MoveBy* moveDown = cocos2d::MoveBy::create(moveTime, Point(0, -moveDistance));
	cocos2d::MoveBy* moveLeft = cocos2d::MoveBy::create(moveTime, Point(-moveDistance, 0));
	cocos2d::MoveBy* moveRight = cocos2d::MoveBy::create(moveTime, Point(moveDistance, 0));
	log("key %d down", keycode);
	switch (keycode)
	{
		case EventKeyboard::KeyCode::KEY_W:
			setMovingState(ms_up);
			break;
		case EventKeyboard::KeyCode::KEY_S:
			setMovingState(ms_down);
			break;
		case EventKeyboard::KeyCode::KEY_A:
			setMovingState(ms_left);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			setMovingState(ms_right);
			break;
		default:
			break;
	}
	//player.moveUpdate();
}