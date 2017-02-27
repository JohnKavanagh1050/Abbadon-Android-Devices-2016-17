#include "GameOverScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(220, 220, 220, 255)))
	{
		return false;
	}

	auto menuTitle =
		MenuItemImage::create("GameOverScreen/Game_Over.png",
		"GameOverScreen/Game_Over.png");
	auto retryItem =
		MenuItemImage::create("GameOverScreen/Retry_Button.png",
		"GameOverScreen/Retry_Button(Click).png",
		CC_CALLBACK_1(GameOver::activateGameScene, this));
	auto mainMenuItem =
		MenuItemImage::create("GameOverScreen/Menu_Button.png",
		"GameOverScreen/Menu_Button(Click).png",
		CC_CALLBACK_1(GameOver::activateMainMenuScene, this));
	auto menu = Menu::create(menuTitle, retryItem, mainMenuItem,
		NULL);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 20);
	this->addChild(menu);

    return true;
}


void GameOver::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameOver::activateGameScene(Ref *pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("MenuMusic.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameMusic.wav", true);
}

void GameOver::activatePauseScene(Ref *pSender)
{
	//auto scene = PauseMenu::createScene();
	auto scene = GameOver::createScene();
	Director::getInstance()->pushScene(scene);
}

void GameOver::activateMainMenuScene(Ref *pSender)
{
	//auto scene = PauseMenu::createScene();
	auto scene = MainMenu::createScene();
	Director::getInstance()->pushScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("GameMusic.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("MenuMusic.wav", true);
}