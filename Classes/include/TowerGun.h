#pragma once

#include <utility>
#include "cocos2d.h"
#include "GameData.h"
#include "Projectile.h"

class TowerGun : public cocos2d::Sprite
{
private:
	static const double PI;
	std::pair<float, bool> m_rotateToPoint;	// The point we need to rotate the tower gun to.
	cocos2d::Vec2 m_centrePoint;	// Centre point of tower gun.
	std::vector<Projectile *> m_projectiles;	// A list of active projectiles.

	void openFire();
	cocos2d::Vec2 pointOnCircle(float radius, int angle, cocos2d::Vec2 origin);

public:
	bool m_fireRequest;
	TowerGun();

	static TowerGun * create(cocos2d::Vec2 position);

	void initOptions(cocos2d::Vec2 position);

	void rotateTowerToPoint(cocos2d::Vec2 touchPoint);

	bool rotateTower();

	void update(float dt);

	std::vector<Projectile *> const & getProjectileList() const;

};