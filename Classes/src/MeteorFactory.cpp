/*#include "MeteorFactory.h"

USING_NS_CC;
MeteorFactory * MeteorFactory::createMeteorFactory()
{
	MeteorFactory * meteorFactory = new MeteorFactory();
	CC_SAFE_DELETE(meteorFactory);
	return;
}

void MeteorFactory::deleteMeteor(GameScene* world, int i)
{
	world->removeChild(currentMeteors[i]);
	currentMeteors.erase(std::remove(currentMeteors.begin(), currentMeteors.end(), currentMeteors[i]));
}

std::vector<Meteor*> MeteorFactory::getMeteors()
{
	return 	currentMeteors;
}

void MeteorFactory::updateMeteorFactory(GameScene* world)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	for (int i = 0; i < currentMeteors.size(); i++){
			if (currentMeteors[i]->getRemove()){
				deleteMeteor(world, i);
			}
			else currentMeteors[i]->updateMeteor();
		}

	if (counter % (SECOND) == 0){
		Meteor *meteor = Meteor::createMeteor();
		currentMeteors.push_back(meteor);
		meteor->setPosition(0, 300);
		world->addChild(meteor, 5);

		counter = 0;
	}
	counter++;
	if (timecounter >= 1000){
		remove = true;
	}
}*/