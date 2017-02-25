#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"
#include "GameScene.h"

class Willpower : public cocos2d::Sprite{
public:
	static Willpower * create(void);
	void initWillpower();
	void update(GameScene* world);
	bool getRemove();

private:
	int timeAlive;
	int timecounter;
	short const TIMETOLIVE = 60;
	bool remove;

	short counter;
	const short SECOND = 60;
};