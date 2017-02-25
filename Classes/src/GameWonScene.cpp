#include "GameWonScene.h"

USING_NS_CC;

Scene* GameWon::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameWon::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameWon::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(220, 220, 220, 255)))
	{
		return false;
	}

	auto menuTitle =
		MenuItemImage::create("GameOverScreen/Game_Won.png",
			"GameOverScreen/Game_Won.png");
	auto retryItem =
		MenuItemImage::create("GameOverScreen/Retry_Button.png",
			"GameOverScreen/Retry_Button(Click).png",
			CC_CALLBACK_1(GameWon::activateGameScene, this));
	auto mainMenuItem =
		MenuItemImage::create("GameOverScreen/Menu_Button.png",
			"GameOverScreen/Menu_Button(Click).png",
			CC_CALLBACK_1(GameWon::activateMainMenuScene, this));
	auto menu = Menu::create(menuTitle, retryItem, mainMenuItem,
		NULL);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 20);
	this->addChild(menu);

	return true;
}


void GameWon::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameWon::activateGameScene(Ref *pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameWon::activatePauseScene(Ref *pSender)
{
	//auto scene = PauseMenu::createScene();
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
}

void GameWon::activateMainMenuScene(Ref *pSender)
{
	//auto scene = PauseMenu::createScene();
	auto scene = MainMenu::createScene();
	Director::getInstance()->pushScene(scene);
}