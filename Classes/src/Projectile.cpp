#include "Projectile.h"

USING_NS_CC;


Projectile::Projectile()
{

}

Projectile * Projectile::create(Vec2 position)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);

	Projectile * pSprite = new Projectile();
	if (pSprite->initWithSpriteFrameName(ptr->m_projectileFile))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Projectile::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y); // +this->getContentSize().height / 2);
}

void Projectile::update(float dt)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	Vec2 nextPosition(m_dirVec.x * ptr->m_velocity, m_dirVec.y * ptr->m_velocity);
	this->setPosition(this->getPosition().x + nextPosition.x, this->getPosition().y + nextPosition.y);
	m_ttl -= dt;	
}

void Projectile::setTTL(int ttl)
{
	m_ttl = ttl;
}


