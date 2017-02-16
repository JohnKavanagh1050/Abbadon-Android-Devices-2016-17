/*#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"
#include "GameScene.h"
#include "Meteor.h"

class MeteorFactory : public cocos2d::Sprite{
public:
	static MeteorFactory * createMeteorFactory(void);
	void deleteMeteor(GameScene* world, int i);
	void updateMeteorFactory(GameScene* world);
//	std::vector<Meteor*> getMeteors();

private:
	int timeAlive;
	int timecounter;
	short const TIMETOLIVE = 60;
	bool remove;

	short counter;
	const short SECOND = 60;

	std::vector<Meteor*> currentMeteors;
};*/