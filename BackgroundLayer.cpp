#include "BackgroundLayer.h"
#include "StaticData.h"
USING_NS_CC;

bool BackgroundLayer::init()
{
	if(CCLayer::init()){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* background;
		// CCSprite* background = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_background_01"));
		if(CCLayer::init()){
			background = CCSprite::create(STATIC_DATA_STRING("game_background_0%s",&SelectScene::transition()));
		}
		else
			background = CCSprite::create(STATIC_DATA_STRING("game_background_01"));

		background->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
		this->addChild(background);
		return true;
	}
	
	return false;
}

