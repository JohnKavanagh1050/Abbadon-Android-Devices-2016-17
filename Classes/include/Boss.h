#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameScene.h"
#include "GameStates.h"

class Boss : public cocos2d::Sprite{
public:
	static Boss * create(void);
	void initBullet();
	void update(GameScene* world);
	bool getRemove();
	void move(float x, float y);
	void animateBullet();

private:
	int timeAlive;
	int timecounter;
	short const TIMETOLIVE = 60;
	bool remove;
	float dirX, dirY;
	float speed;
};