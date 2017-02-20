#pragma once
#include <cocos2d.h>
#include <memory>

class CustomTile {
public:

	CustomTile(cocos2d::Vec2 position, int const size);
	~CustomTile();

	void update();
	void updatePosition(cocos2d::Vec2 newPos);
	cocos2d::Rect bounds;
	cocos2d::Sprite *m_CustomTileSprite;
	enum CustomTileType
	{
		FLOOR,
		WALL,
		DOOR,
		FLOORNIGHT,
		WALLNIGHT,
		DOORNIGHT
	};

	void setType(CustomTile::CustomTileType newType);
	CustomTileType tileType = CustomTileType::FLOOR;
private:
	cocos2d::Vec2 m_position;
	cocos2d::Vec2 m_size;
	int count = 0;

};