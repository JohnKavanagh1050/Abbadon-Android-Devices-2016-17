#include "Block.h"

USING_NS_CC;

Block * Block::create()
{
	Block * block = new Block();

	if (block && block->initWithFile("GameScreen/Meteor.png", Rect(0, 0, 67, 67)))
	{
		cocos2d::Size size(67, 67);
		auto blockBody = PhysicsBody::createBox(size);
		blockBody->setCollisionBitmask(0x000003);
		blockBody->setContactTestBitmask(true);
		blockBody->setTag(30);
		block->setPhysicsBody(blockBody);
		block->initMeteor();
		block->setTag(30);

		return block;
	}
	CC_SAFE_DELETE(block);
	return NULL;
}

bool Block::getRemove(){
	return remove;
}

void Block::initMeteor(){
	timecounter = timeAlive = 0;
	remove = false;
}

void Block::updateMeteor()
{
	setPositionX(getPositionX() + 5);
	timecounter++;
	if (timecounter >= 1000){
		remove = true;
	}
}