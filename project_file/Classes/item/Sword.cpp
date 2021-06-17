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
	/*���������ӵ�������Ҫ���д���*/
	;
}

void Sword::Fire(Vec2 MousePosition, bool attackDirection)
{
	if (AttackState == true) 
	{
		mySprite->setVisible(false);
		Sprite* attackSp;
		/*���Ƿ�������*/
		if (attackDirection)
		{
			attackSp = Sprite::create("sword_action1.png");
			attackSp->setPosition((HeroPosition - viewPosition).x + 10, (HeroPosition - viewPosition).y);//��ȥ�ӽ��ƶ���Ӱ��
		}
		else
		{
			attackSp = Sprite::create("sword_leftaction1.png");
			attackSp->setPosition((HeroPosition - viewPosition).x - 10, (HeroPosition - viewPosition).y);//��ȥ�ӽ��ƶ���Ӱ��
		}
		attackSp->setTag(1000);
		this->addChild(attackSp);

		attackSp->runAction(attackAnimation(attackDirection));
		scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::attackEnd), 0.2f);

		AttackState = false;//����һ�κ���ʱ�޷����
		scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::restoreAttackState), getShootingSpeed());
	}
}

Animate* Sword::attackAnimation(bool attackDirection)
{
	int iFrameNum = 4;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	if (attackDirection)//���ҹ���
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
	animation->setLoops(1);//�����ظ�����
	animation->setDelayPerUnit(0.05f);
	Animate* action = Animate::create(animation);
	
	return action;
}

void Sword::attackEnd(float dt)
{
	/*�������*/
	dynamic_cast<Sprite*>(this->getChildByTag(1000))->removeFromParentAndCleanup(true);
	mySprite->setVisible(true);
}