#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "FishLayer.h"
#include "MenuLayer.h"
USING_NS_CC;


using namespace cocos2d;
class GameScene :
	public CCScene
{
public:
	GameScene(void);
	CREATE_FUNC(GameScene)
	virtual bool init();
	virtual ~GameScene(void);
protected:
	BackgroundLayer *_backgroundLayer;
	FishLayer *_fishLayer;
	MenuLayer *_menuLayer;
};
