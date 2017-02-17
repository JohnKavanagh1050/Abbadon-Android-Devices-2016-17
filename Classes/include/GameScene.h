#pragma once

#include "cocos2d.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "GameData.h"
#include "GameStates.h"
#include "TowerBase.h"
#include "TowerGun.h"

#include "SimpleAudioEngine.h"  

#include <string>
#include <iostream>

class Player;
class Boss;
class Willpower;

class GameScene : public cocos2d::Layer
{
private:
	GameStates m_gameState;

	Player* player;
	Boss* boss;
	Willpower* willpower;
	//MeteorFactory* meteorFactory;

	cocos2d::CCSprite* bk1;
	cocos2d::CCSprite* bk2;

public:
	cocos2d::PhysicsWorld * sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
    static cocos2d::Scene* createScene();
    virtual bool init();

	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);
    
	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);
	// Called at game over 
	void activateGameOverScene(Ref *pSender);
	void createTowerBases();
	void update(float dt);
	void scrollBk();

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	bool onContactBegin(cocos2d::PhysicsContact &contact);


    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#include "Player.h"
#include "Boss.h"
#include "Willpower.h"