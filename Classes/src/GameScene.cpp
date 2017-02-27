#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto pauseItem = MenuItemImage::create("GameScreen/Pause_Button.png",
		"GameScreen/Pause_Button(Click).png", CC_CALLBACK_1(GameScene::activatePauseScene, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	pauseItem->setPosition(Vec2(850, s.height - 50));

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 6);

	collisionManager = std::make_shared<CollisionManager>(CollisionManager());

	/*willpower = Willpower::create();
	willpower->setPosition(Vec2(50, s.height - 50));
	this->addChild(willpower, 5);*/

	player = Player::create();
	player->setPosition(Vec2(300, 300));
	this->addChild(player, 5);

	boss = Boss::create();
	boss->setPosition(Vec2(400, 600));
	this->addChild(boss, 5);

	this->scheduleUpdate();
	comboLabel1 = Label::create("Willpower", "Arial", 40);
	comboLabel2 = Label::create("12", "Arial", 40);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	comboLabel1->setPosition(100, winSize.height - comboLabel1->getContentSize().height / 2 - 50);
	comboLabel2->setPosition(250, winSize.height - comboLabel1->getContentSize().height / 2 - 50);

	// add this to the layer
	this->addChild(comboLabel1, 6);
	this->addChild(comboLabel2, 6);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	map.initialise(10, 10, currentLevel);
	map.ChangeLevel(true);
	for (int i = 0; i < map.tiles.size(); i++)
	{
		this->addChild(map.tiles.at(i)->m_CustomTileSprite);
	}
	for (int i = 0; i < map.tiles.size(); i++)
	{
		map.tiles.at(i)->m_CustomTileSprite->setVisible(true);
	}
	m_gameState = GameStates::GameDay;

	return true;
}

void GameScene::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	auto backgroundSprite = Sprite::create
	(ptr->m_backgroundTextureFile);
	backgroundSprite->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(backgroundSprite, -1);
}

void GameScene::update(float dt)
{
	if (moving)
	{
		timerMoving -= 3;
	}
	if (notMoving)
	{
		timerMoving++;
	}
	if (cantMove)
	{
		cantMoveTimer++;
		if (cantMoveTimer >= 200)
		{
			cantMove = false;
		}
	}
	if (timerMoving > 1200)
	{
		timerMoving = 1200;
	}
	//updating willpower HUD
	if (timerMoving <= 0) {
		comboLabel2->setString("0");
		cantMove = true;
	}
	//updating willpower HUD
	else if (timerMoving <= 100 && timerMoving >= 0) {
		comboLabel2->setString("1");
	}
	//updating willpower HUD
	else if (timerMoving <= 200 && timerMoving >= 100) {
		comboLabel2->setString("2");
	}
	//updating willpower HUD
	else if (timerMoving <= 300 && timerMoving >= 200) {
		comboLabel2->setString("3");
	}
	//updating willpower HUD
	else if (timerMoving <= 400 && timerMoving >= 300) {
		comboLabel2->setString("4");
	}
	//updating willpower HUD
	else if (timerMoving <= 500 && timerMoving >= 400) {
		comboLabel2->setString("5");
	}
	//updating willpower HUD
	else if (timerMoving <= 600 && timerMoving >= 500) {
		comboLabel2->setString("6");
	}
	//updating willpower HUD
	else if (timerMoving <= 700 && timerMoving >= 600) {
		comboLabel2->setString("7");
	}
	//updating willpower HUD
	else if (timerMoving <= 800 && timerMoving >= 700) {
		comboLabel2->setString("8");
	}
	//updating willpower HUD
	else if (timerMoving <= 900 && timerMoving >= 800) {
		comboLabel2->setString("9");
	}
	//updating willpower HUD
	else if (timerMoving <= 1000 && timerMoving >= 900) {
		comboLabel2->setString("10");
	}
	//updating willpower HUD
	else if (timerMoving <= 1100 && timerMoving >= 1000) {
		comboLabel2->setString("11");
	}
	//updating willpower HUD
	else if (timerMoving <= 1200 && timerMoving >= 1100) {
		comboLabel2->setString("12");
	}
	//when will power is 0 you cannot move for a shrt period of time
	if (!cantMove){
		player->update(this);
	}
	boss->update(this);

	//allows the enemy reaper to follow the player
	float x = player->getPosition().x - boss->getPosition().x;
	float y = player->getPosition().y - boss->getPosition().y;
	float magnitude = sqrtf(powf(x, 2) + powf(y, 2));
	x /= magnitude;
	y /= magnitude;

	boss->move(x, y);

	//collision between boss and player
	if (collisionManager->checkCollision(player->getBoundingBox(), boss->getBoundingBox()))
	{
		activateGameOverScene(this);
	}

	if (player->getMoving() == false)
	{
		if (map.isDayTime != false)
		{
			map.ChangeLevel(true);
		}
	}
	else
	{
		if (map.isDayTime == false)
		{
			map.ChangeLevel(false);
		}
	}
	for (int i = 0; i < map.tiles.size(); i++)
	{
		switch (map.tiles.at(i)->tileType)
		{
		case CustomTile::WALL:
			if (collisionManager->checkCollision(player->getBoundingBox(), map.tiles.at(i)->m_CustomTileSprite->getBoundingBox()))
			{
				float offsetX = 0;
				float offsetY = 0;
				offsetX = collisionManager->getHorizontalIntersectionDepth(player->getBoundingBox(), map.tiles.at(i)->m_CustomTileSprite->getBoundingBox());
				offsetY = collisionManager->getVerticalIntersectionDepth(player->getBoundingBox(), map.tiles.at(i)->m_CustomTileSprite->getBoundingBox());

				if (abs(offsetX) > abs(offsetY))
				{
					player->setPositionY(player->getPositionY() + offsetY);
				}
				else
				{
					player->setPositionX(player->getPositionX() + offsetX);
				}
			}
			break;
		case CustomTile::DOOR:
			if (collisionManager->checkCollision(player->getBoundingBox(), map.tiles.at(i)->m_CustomTileSprite->getBoundingBox()))
			{
				map.initialise(10, 10, currentLevel++);
				for (int i = 0; i < map.tiles.size(); i++)
				{
					this->addChild(map.tiles.at(i)->m_CustomTileSprite);
				}
				for (int i = 0; i < map.tiles.size(); i++)
				{
					map.tiles.at(i)->m_CustomTileSprite->setVisible(true);
				}
				if (currentLevel > 5)
				{
					activateGameWonScene(this);
				}
			}
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < map.tiles.size(); i++)
	{
		switch (map.tiles.at(i)->tileType)
		{
		case CustomTile::WALLNIGHT:
			if (collisionManager->checkCollision(player->getBoundingBox(), map.tiles.at(i)->m_CustomTileSprite->getBoundingBox()))
			{
				float offsetX = 0;
				float offsetY = 0;
				offsetX = collisionManager->getHorizontalIntersectionDepth(player->getBoundingBox(), map.tiles.at(i)->m_CustomTileSprite->getBoundingBox());
				offsetY = collisionManager->getVerticalIntersectionDepth(player->getBoundingBox(), map.tiles.at(i)->m_CustomTileSprite->getBoundingBox());

				if (abs(offsetX) > abs(offsetY))
				{
					player->setPositionY(player->getPositionY() + offsetY);
				}
				else
				{
					player->setPositionX(player->getPositionX() + offsetX);
				}
			}
			break;
		case CustomTile::DOORNIGHT:
			if (collisionManager->checkCollision(player->getBoundingBox(), map.tiles.at(i)->m_CustomTileSprite->getBoundingBox()))
			{
				map.initialise(10, 10, currentLevel++);
				for (int i = 0; i < map.tiles.size(); i++)
				{
					this->addChild(map.tiles.at(i)->m_CustomTileSprite);
				}
				for (int i = 0; i < map.tiles.size(); i++)
				{
					map.tiles.at(i)->m_CustomTileSprite->setVisible(true);
				}
				if (currentLevel > 5)
				{
					activateGameWonScene(this);
				}
			}
			break;
		default:
			break;
		}
	}
	
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	moving = true;
	notMoving = false;
	//get location of my touch event for player movement
	float x = touch->getLocation().x - player->getPosition().x;
	float y = touch->getLocation().y - player->getPosition().y;
	float magnitude = sqrtf(powf(x, 2) + powf(y, 2));
	x /= magnitude;
	y /= magnitude;

	player->move(x, y);
	player->movingTrue();

	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	moving = false;
	notMoving = true;
	player->idle();
}

void GameScene::activatePauseScene(Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	//auto scene = GameOver::createScene();
	Director::getInstance()->pushScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("GameMusic.wav");
}

void GameScene::activateGameOverScene(Ref *pSender)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void GameScene::activateGameWonScene(Ref *pSender)
{
	auto scene = GameWon::createScene();
	Director::getInstance()->replaceScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	return true;
}