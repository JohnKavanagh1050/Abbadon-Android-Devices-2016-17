#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"
#include "GameScene.h"

class Block : public cocos2d::Sprite{
public:
	static Block * create(void);
	void initMeteor();
	void deleteMeteor(GameScene* world, int i);
	void updateMeteor();
	bool getRemove();

private:
	int timeAlive;
	int timecounter;
	short const TIMETOLIVE = 60;
	bool remove;

	short counter;
	const short SECOND = 60;
};