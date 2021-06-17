#include"Sword.h"

Sword::Sword()
{
	bindSprite(Sprite::create("sword.png"));
	if (mySprite == nullptr)
	{
		log("pistol.png is not found");
	}
	scheduleUpdate();
	setPower(swordPower);
	setShootingSpeed(swordAttackSpeed);
	setBulletCapacity(0);
	weaponType = 2;
}

bool Sword::init()
{
	return true;
}

void Sword::update(float dt)
{
	if (this->getState() == true)
	{
		mySprite->setPosition(HeroPosition);
	}
	else
		;
}

void Sword::changeBulletamount(int mode)
{
	/*刀不产生子弹，不需要进行处理*/
	;
}

void Sword::Fire(Vec2 MousePosition, bool attackDirection)
{
	if (AttackState == true) 
	{
		mySprite->setVisible(false);
		Sprite* attackSp;
		/*考虑方向问题*/
		if (attackDirection)
		{
			attackSp = Sprite::create("sword_action1.png");
			attackSp->setPosition((HeroPosition - viewPosition).x + 10, (HeroPosition - viewPosition).y);//减去视角移动的影响
		}
		else
		{
			attackSp = Sprite::create("sword_leftaction1.png");
			attackSp->setPosition((HeroPosition - viewPosition).x - 10, (HeroPosition - viewPosition).y);//减去视角移动的影响
		}
		attackSp->setTag(1000);
		this->addChild(attackSp);

		attackSp->runAction(attackAnimation(attackDirection));
		scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::attackEnd), 0.2f);

		AttackState = false;//攻击一次后，暂时无法射击
		scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::restoreAttackState), getShootingSpeed());
	}
}

Animate* Sword::attackAnimation(bool attackDirection)
{
	int iFrameNum = 4;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	if (attackDirection)//向右攻击
	{
		for (int i = 1; i <= iFrameNum; i++)
		{
			frame = SpriteFrame::create(StringUtils::format("sword_action%d.png", i), Rect(0, 0, 60, 60));
			frameVec.pushBack(frame);
		}
	}
	else
	{
		for (int i = 1; i <= iFrameNum; i++)
		{
			frame = SpriteFrame::create(StringUtils::format("sword_leftaction%d.png", i), Rect(0, 0, 60, 60));
			frameVec.pushBack(frame);
		}
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);//设置重复次数
	animation->setDelayPerUnit(0.05f);
	Animate* action = Animate::create(animation);
	
	return action;
}

void Sword::attackEnd(float dt)
{
	/*清除动画*/
	dynamic_cast<Sprite*>(this->getChildByTag(1000))->removeFromParentAndCleanup(true);
	mySprite->setVisible(true);
}