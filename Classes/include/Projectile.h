#pragma once

#include <utility>
#include "cocos2d.h"
#include "GameData.h"

class Projectile : public cocos2d::Sprite
{
private:
	
public:
	float m_ttl;
	cocos2d::Vec2 m_dirVec;
	
	Projectile();

	static Projectile * create(cocos2d::Vec2 position);

	void initOptions(cocos2d::Vec2 position);

	void update(float dt);

	void setTTL(int ttl);
};