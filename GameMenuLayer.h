#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class GameMenuLayer :
	public CCLayer
{
public:
	GameMenuLayer(void);
	CREATE_FUNC(GameMenuLayer);
	static CCScene* scene(void);
	virtual bool init();
	virtual ~GameMenuLayer(void);
protected:
	void createMenu(void);
	void onStartGame(CCObject *sender);
	void onSelectScene(CCObject *sender);
};
