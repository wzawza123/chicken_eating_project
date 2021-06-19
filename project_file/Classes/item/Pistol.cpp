#include"Pistol.h"

Pistol::Pistol()
{
	bindSprite(Sprite::create("pistol.png"));
	if (mySprite == nullptr)
	{
		log("pistol.png is not found");
	}
	scheduleUpdate();
	weaponType = isPistol;
	setPower(pistolPower);
	setBulletCapacity(pistolBulletCapacity);
	setShootingSpeed(pistolShottingSpeed);
	
}

bool Pistol::init()
{
	return true;
}

void Pistol::update(float dt) 
{
	if (getState() == false)
		;
	else
	{
		mySprite->setPosition(HeroPosition);
	}
}

Bullet* Pistol::shootBullet(Vec2 vec)
{
	Bullet* newBullet = Bullet::create();
	newBullet->setPosition(getWeaponPosition());
	newBullet->m_pBulletSprite->getPhysicsBody()->setVelocity( vec);
	return newBullet;
}

void Pistol::changeBulletamount(int mode, int num)
{
	switch (mode)
	{
		case 1:
			nowBulletAmount--;
			break;
		case 2:
			nowBulletAmount = pistolBulletCapacity;
			break;
		case 3:
			nowBulletAmount += num;
			break;
	}
}

void Pistol::Fire(Vec2 MousePosition, bool attackDirection)
{
	/*������ӵ�*/
	if (getNowBulletAmount() > 0 && AttackState == true)
	{
		/*��ȡ�ӵ����䷽��*/
		auto X = MousePosition.x - convertToWorldSpace(getWeaponPosition()).x;
		auto Y = MousePosition.y - convertToWorldSpace(getWeaponPosition()).y;
		auto length = hypot(X, Y);
		auto XCoefficient = X / length;
		auto YCoefficient = Y / length;
		log("=============================================================");
		/*ÿ�ε�����һ�����ӵ�*/
		Bullet* newBullet;
		newBullet = shootBullet(Vec2(2000 * XCoefficient, 2000 * YCoefficient));
		newBullet->setCameraMask((unsigned short)CameraFlag::USER2);
		addChild(newBullet, 1, tagConsts::tagBullet);

		changeBulletamount(1,0);//�ӵ����м���
		log("Fire!!!");
		log("Bullet number is %d", getNowBulletAmount());

		AttackState = false;//���һ�κ���ʱ�޷����
		scheduleOnce(CC_SCHEDULE_SELECTOR(Pistol::restoreAttackState), getShootingSpeed());
	}
	else if (getNowBulletAmount() == 0)
	{
		log("Bullets is ran out");
	}
}
