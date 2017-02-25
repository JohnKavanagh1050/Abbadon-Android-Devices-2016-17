#include "CollisionManager.h"
#include <iostream>

CollisionManager::CollisionManager()
{

}

bool CollisionManager::checkCollision(cocos2d::Vec2 &point, cocos2d::Rect &box)
{
	if (box.containsPoint(point))
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkCollision(cocos2d::Rect &a, cocos2d::Rect &b)
{
	if (a.intersectsRect(b))
	{
		return true;
	}
	return false;
}

float CollisionManager::getHorizontalIntersectionDepth(cocos2d::Rect a, cocos2d::Rect b)
{
	float halfWidthA = a.size.width / 2;
	float halfWidthB = b.size.width / 2;

	float centerA = a.origin.x + halfWidthA;
	float centerB = b.origin.x + halfWidthB;

	float distanceX = centerA - centerB;
	float minDistanceX = halfWidthA + halfWidthB;

	if (std::abs(distanceX) >= minDistanceX)
	{
		return 0;
	}

	if (distanceX > 0) {
		return minDistanceX - distanceX;
	}
	else
	{
		return -minDistanceX - distanceX;
	}
}

float CollisionManager::getVerticalIntersectionDepth(cocos2d::Rect a, cocos2d::Rect b)
{
	float halfHeightA = a.size.height / 2;
	float halfHeightB = b.size.height / 2;

	float centerA = a.origin.y + halfHeightA;
	float centerB = b.origin.y + halfHeightB;

	float distanceY = centerA - centerB;
	float minDistanceY = halfHeightA + halfHeightB;

	if (std::abs(distanceY) >= minDistanceY)
	{
		return 0;
	}

	if (distanceY > 0) {
		return minDistanceY - distanceY;
	}
	else
	{
		return -minDistanceY - distanceY;
	}
}