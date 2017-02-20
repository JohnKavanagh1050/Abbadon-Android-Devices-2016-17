#include "Player.h"
USING_NS_CC;

Player * Player::create()
{
	Player * player = new Player();
	if (player && player->initWithFile("GameScreen/Player.png", Rect(0, 0, 40, 55)))
	{
		//Create and run animation
		Vector<SpriteFrame*> animFrames(4);
		char str[100] = { 0 };
		for (int i = 0; i < 3; i++)
		{
			sprintf(str, "GameScreen/Player.png");
			auto frame = SpriteFrame::create(str, Rect(40 * i, 0, 40, 55));
			animFrames.pushBack(frame);
		}
		auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.15f, 100000);
		auto animate = CCAnimate::create(animation);
		//make body for collisions
		cocos2d::Size size(40, 55);

		player->runAction(animate);
		player->initPlayer();
		player->setTag(20);
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::move(float x, float y)
{
	dirX = x;
	dirY = y;
	moving = true;
}

float Player::getLives(){
	return lives;
}

float Player::setLives(){
	lives = 10;
	return lives;
}

void Player::update(GameScene* world)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	if (moving) //check if moving
	{
		setPositionX(getPosition().x + dirX * speed);
		setPositionY(getPosition().y + dirY * speed);
	}

	if (getPositionY() >= s.height - 20)
	{
		setPosition(getPositionX(), s.height - 20);
	}

	if (getPositionY() <= 20)
	{
		setPosition(getPositionX(), 20);
	}

	if (getPositionX() >= s.width - 20)
	{
		setPosition(s.width - 20, getPositionY());
	}

	if (getPositionY() <= 20)
	{
		setPosition(20, getPositionY());
	}

	setRotation(0);
	counter++;
}

void Player::loseLives(){
	lives--;
}

void Player::idle()
{
	moving = false;
}

void Player::initPlayer(){
	speed = 5.f;
	lives = 10;
	dirX = dirY = 0;
}