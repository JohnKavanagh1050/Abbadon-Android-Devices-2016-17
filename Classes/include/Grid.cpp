//Created by Dale Sinnott
#include "Grid.h"
#include <iostream>
Grid::Grid()
{

}

void Grid::update()
{
	for (int i = 0; i < m_height * m_width; i++)
	{
		tiles.at(i)->update();
	}
}
void Grid::initialise(int width, int height, int loadLevel)
{
	/* LEVEL TILES
	0 - Floor
	1 - Wall
	2 - door
	3 - floor dark
	4 - wall dark
	5 - door dark
	*/
	tiles.clear();
	m_width = width;
	m_height = height;
	cocos2d::Vec2 offset = cocos2d::Vec2(200, 400);
	int currentLevel[10][10];
	switch (loadLevel)
	{

	case 1:
	{
		int level1[10][10] = {
			{ 1,1,1,1,1,1,1,1,1,1 },
			{ 1,2,1,0,0,0,0,0,0,1 },
			{ 1,0,1,0,1,0,1,1,1,1 },
			{ 1,0,1,0,1,0,0,0,0,1 },
			{ 1,0,1,0,1,0,1,0,0,1 },
			{ 1,0,1,0,1,0,1,0,0,1 },
			{ 1,0,0,0,1,3,1,0,0,1 },
			{ 1,0,1,1,1,1,1,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,1 },
			{ 1,1,1,1,1,1,1,1,1,1 } };
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				currentLevel[x][y] = level1[x][y];
			}
		}
	}
	break;
	case 2:
	{
		int level2[10][10] = {
			{ 1,1,1,1,1,1,1,1,1,1 },
			{ 1,0,0,1,0,0,0,0,0,1 },
			{ 1,0,0,1,1,1,1,1,0,1 },
			{ 1,0,0,0,0,0,0,0,0,1 },
			{ 1,1,1,1,1,0,1,0,0,1 },
			{ 1,0,1,0,1,0,1,0,0,1 },
			{ 1,0,1,0,1,2,1,0,0,1 },
			{ 1,3,0,0,0,1,0,1,0,1 },
			{ 1,0,1,0,0,0,0,0,0,1 },
			{ 1,1,1,1,1,1,1,1,1,1 }
		};
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				currentLevel[x][y] = level2[x][y];
			}
		}
	}
	break;
	case 3:
	{
		int level3[10][10] = {
			{ 1,1,1,1,1,1,1,1,1,1 },
			{ 1,0,0,0,0,0,0,1,3,1 },
			{ 1,0,1,1,1,1,0,1,0,1 },
			{ 1,0,1,0,0,0,0,0,0,1 },
			{ 1,0,1,0,0,0,0,0,0,1 },
			{ 1,0,1,0,1,0,1,1,0,1 },
			{ 1,0,1,0,1,0,0,1,0,1 },
			{ 1,2,0,0,1,0,0,1,0,1 },
			{ 1,0,0,0,0,0,0,0,0,1 },
			{ 1,1,1,1,1,1,1,1,1,1 } };
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				currentLevel[x][y] = level3[x][y];
			}
		}
	}
	break;
	case 4:
	{
		int level4[10][10] = {
			{ 1,1,1,1,1,1,1,1,1,1 },
			{ 1,3,1,0,0,0,0,1,2,1 },
			{ 1,0,1,0,1,1,0,1,0,1 },
			{ 1,0,1,0,1,0,0,0,0,1 },
			{ 1,0,0,0,1,0,1,0,0,1 },
			{ 1,0,1,0,1,0,1,0,0,1 },
			{ 1,0,1,0,0,0,0,0,0,1 },
			{ 1,0,1,1,1,1,1,1,0,1 },
			{ 1,0,0,0,0,0,0,1,0,1 },
			{ 1,1,1,1,1,1,1,1,1,1 }
		};
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				currentLevel[x][y] = level4[x][y];
			}
		}
	}
	break;
	case 5:
	{
		int level5[10][10] = {
			{ 1,1,1,1,1,1,1,1,1,1 },
			{ 1,2,1,1,4,4,4,4,4,1 },
			{ 1,4,1,4,4,4,4,4,4,1 },
			{ 1,4,1,4,1,1,1,1,4,1 },
			{ 1,4,1,4,1,4,4,4,4,1 },
			{ 1,4,4,4,1,1,1,1,1,1 },
			{ 1,4,1,1,1,4,4,4,4,1 },
			{ 1,4,4,4,4,4,4,4,4,1 },
			{ 1,4,4,4,4,4,4,4,4,1 },
			{ 1,1,1,1,1,1,1,1,1,1 }
		};
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				currentLevel[x][y] = level5[x][y];
			}
		}
	}
	break;
	default:
		break;
	}
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{//set tiles into grid
			CustomTile tempTile(cocos2d::Vec2(0 * 64, 0 * 64), 64);
			switch (currentLevel[x][y])
			{
			case 0:
				tempTile.setType(CustomTile::FLOOR);
				break;
			case 1:
				tempTile.setType(CustomTile::WALL);
				break;
			case 2:
				tempTile.setType(CustomTile::DOOR);
				break;
			case 3:
				tempTile.setType(CustomTile::FLOORNIGHT);
				break;
			case 4:
				tempTile.setType(CustomTile::WALLNIGHT);
				break;
			case 5:
				tempTile.setType(CustomTile::DOORNIGHT);
				break;
			default:
				break;
			}

			tempTile.updatePosition(cocos2d::Vec2(offset.x + y * 64, 1080 - (offset.y + x * 64)));
			tiles.push_back(std::make_shared<CustomTile>(tempTile));
		}
	}


}