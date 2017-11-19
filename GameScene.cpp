#include "GameScene.h"



GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	CC_SAFE_RELEASE_NULL(_menuLayer);
	/*if (menuLayer)
	{
		menuLayer->release();
		menuLayer = NULL;
	}*/
}

bool GameScene::init()
{
	/*if (!GameScene::init())
	{
		return false;
	}
	backgroundLayer = BackgroundLayer::create();
	if (!backgroundLayer)
	{
		return false;
	}
	return true;*/
	do
	{
		if (!GameScene::init())
		{
			break;
		}
		_backgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(!_backgroundLayer);
		/*if (!backgroundLayer)
		{
			break;
		}*/
		this->addChild(_backgroundLayer);
		_fishLayer = FishLayer::create();
		CC_BREAK_IF(!_fishLayer);
		this->addChild(_fishLayer);

		_menuLayer = MenuLayer::create();
		CC_BREAK_IF(!_menuLayer);
		//menuLayer->retain();

		CC_SAFE_RETAIN(_menuLayer);

		return true;
	} while (0);

	return false;

	
}
