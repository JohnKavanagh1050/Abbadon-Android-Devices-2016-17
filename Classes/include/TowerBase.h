#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"

class TowerBase : public cocos2d::Sprite
{
private:
	GameStates & m_gameState;
	bool m_touched;
public:
	TowerBase(GameStates & gameState);

	static TowerBase * create(cocos2d::Vec2 position, GameStates & gameState);

	void initOptions(cocos2d::Vec2 position);

	void addEvents();
	void handleTouchEvent(cocos2d::Touch* touch);

	bool isTouched() const;

	

};