#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"
#include "GameScene.h"
#include "Boss.h"

class Player : public cocos2d::Sprite{
public:
	static Player * create(void);

	void move(float x, float y);
	void update(GameScene* world);
	void idle();
	void loseLives();

	float getLives();
	float setLives();

	bool stopSpeed();
	bool giveSpeed();
	bool getMoving();
	bool movingTrue();

private:
	void initPlayer();

	float dirX, dirY;
	float speed;
	float lives = 10;

	bool moving;
	bool hit;

	short counter;
	const short SECOND = 60;

	float yValue = 0;
};