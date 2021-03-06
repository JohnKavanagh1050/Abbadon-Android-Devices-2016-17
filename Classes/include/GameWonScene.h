#ifndef __GAMEWON_SCENE_H__
#define __GAMEWON_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "MainMenuScene.h"

class GameWon : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// Called when retry is selected 
	void activateGameScene(Ref *pSender);
	// Called when main menu is selected 
	void activateMainMenuScene(Ref *pSender);

	void activatePauseScene(Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameWon);
};
#endif 