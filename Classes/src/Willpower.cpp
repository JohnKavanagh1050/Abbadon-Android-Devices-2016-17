#include "Willpower.h"

USING_NS_CC;

Willpower * Willpower::create()
{
	Willpower * willpower = new Willpower();

	if (willpower && willpower->initWithFile("GameScreen/willpower1.png", Rect(0, 0, 116.69, 112)))
	{
		//Create and run animation
		Vector<SpriteFrame*> animFrames(13);
		char str[100] = { 0 };
		for (int i = 0; i < 13; i++)
		{
			sprintf(str, "GameScreen/willpower1.png");
			auto frame = SpriteFrame::create(str, Rect((116.69) * i, 0, 116.69, 112));
			animFrames.pushBack(frame);
		}
		auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.25f, 100000);
		auto animate = CCAnimate::create(animation);
		//make body for collisions
		cocos2d::Size size(116.5, 112);
		auto bossBody = PhysicsBody::createBox(size);
		bossBody->setCollisionBitmask(0x000001);
		bossBody->setContactTestBitmask(true);
		bossBody->setTag(10);
		willpower->setPhysicsBody(bossBody);
		willpower->runAction(animate);
		willpower->init();
		willpower->setTag(10);

		return willpower;
	}
	CC_SAFE_DELETE(willpower);
	return NULL;
}

bool Willpower::getRemove(){
	return remove;
}

void Willpower::initWillpower(){

}

void Willpower::update()
{

}