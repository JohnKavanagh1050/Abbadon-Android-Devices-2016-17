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
	//int level1[10][10];
	//int level2[10][10];
	//int level3[10][10];
	//int level4[10][10];
	//int level5[10][10];

	int m_width;
	int m_height;
private:

};
