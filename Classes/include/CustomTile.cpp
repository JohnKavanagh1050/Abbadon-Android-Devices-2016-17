#include "CustomTile.h"
#include <iostream>
CustomTile::CustomTile(cocos2d::Vec2 position, int const size = 16) :
	m_position(position), m_size(size, size)
{
	bounds.origin.x = position.x;
	bounds.origin.y = position.y;
	bounds.size.width = size;
	bounds.size.height = size;
<<<<<<< HEAD
	m_CustomTileSprite = cocos2d::Sprite::create("GameScreen/grass1.png");
}

=======
	m_CustomTileSprite = cocos2d::Sprite::create("GameScreen/tile_Floor.png");
}
>>>>>>> 46775e90af4b3d18af30072b927076445e3487f4
CustomTile::~CustomTile()
{

}
<<<<<<< HEAD

=======
>>>>>>> 46775e90af4b3d18af30072b927076445e3487f4
void CustomTile::update()
{

}
<<<<<<< HEAD

=======
>>>>>>> 46775e90af4b3d18af30072b927076445e3487f4
void CustomTile::setType(CustomTile::CustomTileType newType)
{
	switch (newType)
	{
	case CustomTile::FLOOR:
		m_CustomTileSprite = cocos2d::Sprite::create("GameScreen/grass1.png");
		break;
	case CustomTile::WALL:
		m_CustomTileSprite = cocos2d::Sprite::create("GameScreen/wall.png");
		break;
	case CustomTile::DOOR:
		m_CustomTileSprite = cocos2d::Sprite::create("GameScreen/door.png");
		break;
	case CustomTile::FLOORNIGHT:
		m_CustomTileSprite = cocos2d::Sprite::create("GameScreen/grass1_D.png");
		break;
	case CustomTile::WALLNIGHT:
		m_CustomTileSprite = cocos2d::Sprite::create("GameScreen/wall1_D.png");
		break;
	case CustomTile::DOORNIGHT:
		m_CustomTileSprite = cocos2d::Sprite::create("GameScreen/door_D.png");
		break;
	default:
		break;
	}
	tileType = newType;
}

void CustomTile::updatePosition(cocos2d::Vec2 newPos)
{
	m_CustomTileSprite->setPosition(newPos.x, newPos.y);

	bounds.origin.x = newPos.x;
	bounds.origin.y = newPos.y;
}