#pragma once

#include <cocos2d.h>
#include <memory>
#include "CustomTile.h"

class Grid
{
public:
	Grid();

	void initialise(int width, int height, int level);

	void update();

	std::vector<std::shared_ptr<CustomTile>> tiles;

	bool isDayTime = true;
	int m_width;
	int m_height;

	void ChangeLevel(bool isDayTime);
private:
	int currentLevel[10][10];
	cocos2d::Vec2 offset;

};
