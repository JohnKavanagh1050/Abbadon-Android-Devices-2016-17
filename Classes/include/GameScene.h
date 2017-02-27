#pragma once

#include "cocos2d.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "GameWonScene.h"
#include "GameData.h"
#include "GameStates.h"
#include "CollisionManager.h"
#include "Grid.h"
#include "SimpleAudioEngine.h"  

#include <string>
#include <iostream>
#include <memory>

class Player;
class Boss;
class Willpower;

class GameScene : public cocos2d::Layer
{
private:
	Player* player;
	Boss* boss;
	Willpower* willpower;

	std::shared_ptr<CollisionManager> collisionManager;

	//level vars
	int currentLevel = 1;
	int maxLevels = 5;
	//HUD vars
	int timerNotMoving = 0;
	int timerMoving = 1200;
	int cantMoveTimer = 0;
	bool moving = true;
	bool notMoving = false;
	bool cantMove = false;
	cocos2d::Label *comboLabel1;
	cocos2d::Label *comboLabel2;

	Grid map;
	GameStates m_gameState = GameStates::GameInit;

public:
	cocos2d::PhysicsWorld * sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
    static cocos2d::Scene* createScene();
    virtual bool init();

	void updateScore(int score);

	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);
    
	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);
	// Called at game over 
	void activateGameOverScene(Ref *pSender);
	//calls game won
	void activateGameWonScene(Ref *pSender);
	//void createTowerBases();
	void update(float dt);
	//void scrollBk();

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	bool onContactBegin(cocos2d::PhysicsContact &contact);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#include "Player.h"
#include "Boss.h"
#include "Willpower.h"