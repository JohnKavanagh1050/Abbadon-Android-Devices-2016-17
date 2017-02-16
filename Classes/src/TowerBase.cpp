#include "TowerBase.h"

USING_NS_CC;

TowerBase::TowerBase(GameStates & gameState) : 
m_gameState(gameState),
m_touched(false)
{
	
}

TowerBase * TowerBase::create(Vec2 position, GameStates & gameState)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);		

	TowerBase* pSprite = new TowerBase(gameState);
	if (pSprite->initWithSpriteFrameName(ptr->m_towerBaseFile))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);

		pSprite->addEvents();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void TowerBase::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}

void TowerBase::addEvents()
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 pos = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(pos))
		{
			return true; // to indicate that we have consumed it.
		}

		return false; // we did not consume this event, pass through.
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		handleTouchEvent(touch);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void TowerBase::handleTouchEvent(cocos2d::Touch* touch)
{
	// Change gameState in response to sprite touched
	m_gameState = GameStates::GameInit;
	m_touched = true;
}

bool TowerBase::isTouched() const
{
	return m_touched;
}
