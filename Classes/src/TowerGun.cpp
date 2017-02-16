#include "TowerGun.h"

USING_NS_CC;

const double TowerGun::PI = 4.0 * atan(1.0);

TowerGun::TowerGun() :
m_fireRequest(false)
{

}

TowerGun * TowerGun::create(Vec2 position)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);

	TowerGun* pSprite = new TowerGun();
	if (pSprite->initWithSpriteFrameName(ptr->m_towerGunFile))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void TowerGun::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y + this->getContentSize().height / 4);
	m_centrePoint = this->getPosition();
	// Set the anchor point lower on the y-axis for the tower gun, so rotations look better.
	this->setAnchorPoint(Vec2(0.5f, 0.3f));	
}

////////////////////////////////////////////////////////////
void TowerGun::rotateTowerToPoint(Vec2 touchPoint)
{	
	Vec2 pos(touchPoint.y - this->getPosition().y, touchPoint.x - this->getPosition().x);
	float theta_deg = atan2(pos.y, pos.x) / PI * 180; 
	m_rotateToPoint.first = std::round(theta_deg); 
	
	// If our rotateToPoint is a negative angle, express as a positive angle.
	if (m_rotateToPoint.first < 0)
	{
		m_rotateToPoint.first = 360 - std::abs(m_rotateToPoint.first);
	}

	// Set tower not aligned status.
	m_rotateToPoint.second = false;	
}

////////////////////////////////////////////////////////////
bool TowerGun::rotateTower()
{
	bool aligned = true;
	// Check if this tower needs to rotate to face a point.
	int degrees = this->getRotation();

	// If rotating CCW, degrees becomes negative. Convert to a positive value.
	//  E.g. -1 will become (360 - 1) = 359
	if (degrees < 0)
	{
		degrees = 360 - std::abs(degrees);
	}
	// If degrees are positive, use mod operator to keep within a range 0 to 359.
	else if (degrees >= 360)
	{
		degrees = degrees % 360;
	}

	// Rotate the shortest way to the rotation point (either negative or positive rotation)
	if (degrees != m_rotateToPoint.first)
	{
		aligned = false;
		int rotation = m_rotateToPoint.first - degrees;
		int signOfRotation = std::copysign(1.0f, rotation); // get the sign of the number rotation (+ or -)
				
		int rotationSpeed = 3; 
		// If close to desired heading, slow down rotation speed to 1 degree increments.
		if (std::abs(rotation) <= 3) 
		{
			rotationSpeed = 1;
		}
		// Compute the shortest route to rotate to our desired angle.
		if (std::abs(rotation) < 180)
		{			
			this->setRotation(degrees + (signOfRotation * rotationSpeed));
		}
		else // degrees >= 180
		{
			this->setRotation(degrees + (-1.0f * signOfRotation * rotationSpeed));
		}
	}
	return aligned;
}

void TowerGun::update(float dt) 
{
	bool aligned = false;
	if (m_fireRequest)
	{
		aligned = rotateTower();
		if (aligned)
		{
			openFire();
			m_fireRequest = false;
		}
	}
	
	auto iter = m_projectiles.begin();
	// Todo (possibly): Check if tower is ready to fire.	
	for (; iter != m_projectiles.end();)
	{
		if ((*iter)->m_ttl > 0)
		{
			(*iter)->update(dt);
			++iter;
		}
		else
		{
			// Remove from the scene and erase this element.
			Director::getInstance()->getRunningScene()->removeChild((*iter));
			iter = m_projectiles.erase(iter);
		}			
	}		
}


std::vector<Projectile *> const & TowerGun::getProjectileList() const
{
	return m_projectiles;
}

void TowerGun::openFire()
{	
	// Projectile launch point is the end of the gun turret.
	//  Take approx 3/4 of sprite height for the gun portion of the tower.
	float gunLength = this->getContentSize().height * 0.75;
	Vec2 launchPosition = pointOnCircle(gunLength, this->getRotation(), m_centrePoint);	

	// Add the projectile to the scene.
	auto projectile = Projectile::create(launchPosition);	
	Director::getInstance()->getRunningScene()->addChild(projectile, 1);

	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	projectile->m_ttl = ptr->m_ttl;	
	projectile->m_dirVec = Vec2(launchPosition.x - m_centrePoint.x, launchPosition.y - m_centrePoint.y);
	projectile->m_dirVec.normalize();
	m_projectiles.push_back(projectile);	
}

////////////////////////////////////////////////////////////
Vec2 TowerGun::pointOnCircle(float radius, int angle, Vec2 origin)
{
	// Angle is a clockwise offset from positive y axis
	// sin and cos use radians, computed as an counter clockwise offset from positive x axis
	// When working with radians, we use (90 - angle) to allow for this difference.
	float radians = (90 - angle) * PI / 180.0f;
	float x = static_cast<float>(radius * cos(radians)); 
	float y = static_cast<float>(radius * sin(radians)); 
	
	x += origin.x;
	y += origin.y;	
	return Vec2(x, y);
}