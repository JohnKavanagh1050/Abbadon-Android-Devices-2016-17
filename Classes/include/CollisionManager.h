#pragma once

#include <memory>
#include <cocos2d.h>
class CollisionManager
{
public:
	CollisionManager();
	bool checkCollision(cocos2d::Vec2 &point, cocos2d::Rect &box);
	bool checkCollision(cocos2d::Rect &a, cocos2d::Rect &b);
	float getHorizontalIntersectionDepth(cocos2d::Rect a, cocos2d::Rect b);
	float getVerticalIntersectionDepth(cocos2d::Rect a, cocos2d::Rect b);

private:

};