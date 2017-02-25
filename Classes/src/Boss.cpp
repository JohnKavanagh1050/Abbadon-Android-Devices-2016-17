#include "Boss.h"

USING_NS_CC;

Boss * boss = new Boss();
Boss * Boss::create()
{
	if (boss && boss->initWithFile("GameScreen/Reaper.png", Rect(0, 0, 69, 60)))
	{
		//Create and run animation
		Vector<SpriteFrame*> animFrames(4);
		char str[100] = { 0 };
		for (int i = 0; i < 3; i++)
		{
			sprintf(str, "GameScreen/Reaper.png");
			auto frame = SpriteFrame::create(str, Rect((69) * i, 0, 69, 60));
			animFrames.pushBack(frame);
		}
		auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.15f, 100000);
		auto animate = CCAnimate::create(animation);
		//make body for collisions
		cocos2d::Size size(69, 60);
		boss->runAction(animate);
		boss->initBullet();
		boss->setTag(10);
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return NULL;
}

void Boss::animateBullet()
{

}

void Boss::move(float x, float y)
{
	dirX = x;
	dirY = y;
}

bool Boss::getRemove(){
	return remove;
}

void Boss::initBullet(){
	speed = 1.f;
	dirX = dirY = 0;
}

void Boss::update(GameScene* world)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	setPositionX(getPosition().x + dirX * speed);
	setPositionY(getPosition().y + dirY * speed);
	setRotation(0);

	if (dirX < 0) {
		boss->_flippedX = true;
	}
	else
		boss->_flippedX = false;
}