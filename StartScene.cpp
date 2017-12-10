#include "StartScene.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene4.h"
#include "GameScene3.h"
#include "PersonalAudioEngine.h"
#include "StaticData.h"
#include "Fish.h"
#include "FishingJoyData.h"
#include "SelectScene.h"
//extern CCAnimation* Puffer_BAnimation;
USING_NS_CC;
//using namespace CocosDenshion;
char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS",	"Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout","GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};
int  maxFrame[]={4,5,10,6,6,9,9,9,10,9,10,6,9,10,10,5,10,6};
CCScene* StartLayer::scene()
{
    CCScene* scene = CCScene::create();
    StartLayer* layer = StartLayer::create();
    scene->addChild(layer);;
    return scene;
}
bool StartLayer::init()
{
    if(CCLayer::init()){
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* background = CCSprite::create(STATIC_DATA_STRING("game_menu_background"));
		//float sca=(background->getScaleY())/winSize.height;
		background->setScale(0.5);
        background->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
        this->addChild(background);
        
        CCSprite* title = CCSprite::create(STATIC_DATA_STRING("title"));
		title->setScale(0.4);
        title->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.75));
        this->addChild(title);

		/*CCSprite* menu1 = CCSprite::create(STATIC_DATA_STRING("main_ui_button_03_1.png"));
        *menu1->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
        *this->addChild(menu1);*/
        if(CCDirector::sharedDirector()->getTotalFrames()<10){
           CCTextureCache::sharedTextureCache()->addImageAsync(STATIC_DATA_STRING("fishingjoy_texture"), this, callfuncO_selector(StartLayer::loading));
            
            CCSprite* progressBg = CCSprite::create(STATIC_DATA_STRING("progress_bg"));
            _progressFg = CCLabelTTF::create("0/100", "Thonburi", 16);
            _progressFg->setColor(ccc3(0, 0, 0));
            
            _progressBar = ProgressBar::create(this, CCSprite::create(STATIC_DATA_STRING("progress_bar")));
            _progressBar->setBackground(progressBg);
            _progressBar->setForeground(_progressFg);
            _progressBar->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
            _progressBar->setSpeed(100.0);
            this->addChild(_progressBar);
			this->audioAndUserDataInit();
			
        }
	else{
            this->initializationCompleted();
			CCLOG("%s\n","string");
        }
        return true;
    }
    return false;
}

void StartLayer::audioAndUserDataInit()
{
    FishingJoyData::sharedFishingJoyData();
    PersonalAudioEngine::sharedEngine();
}
void StartLayer::loading(CCObject* pObj)
{
    _progressBar->progressTo(100.0);
}
void StartLayer::transition(CCObject* pSender)
{
    CCScene* scene = CCTransitionFadeDown::create(1.0f, GameScene::create());
    CCDirector::sharedDirector()->replaceScene(scene);
}
void StartLayer::transitionSelectScene(CCObject* pSender)
{
	CCScene* scene = CCTransitionShrinkGrow::create(1.0f, SelectScene::create());
    CCDirector::sharedDirector()->replaceScene(scene);
}
void StartLayer::cacheInit()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("FishActor-Small-ipadhd.plist");
   CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("FishActor-Mid-ipadhd.plist");
   CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("FishActor-Large-ipadhd.plist");
   CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("FishActor-Shark-ipadhd.plist");
   CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("FishActor-Marlin-ipadhd.plist");
    int frameCount =16 /*STATIC_DATA_INT("fish_frame_count")*/;
	int type=1;
   for (int type = k_Fish_Type_SmallFish; type < k_Fish_Type_Count; type++) {
	   CCArray* spriteFrames = CCArray::createWithCapacity(frameCount);
	   CCString* fishName=CCString::createWithFormat(str[type]);
	   frameCount=maxFrame[type];
       // CCArray* spriteFrames = CCArray::createWithCapacity(frameCount);
        for(int i = 1;i < frameCount;i++){
			CCString* filename = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"),fishName->getCString(),i);
            CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
            spriteFrames->addObject(spriteFrame);	
        }
	
        CCAnimation* fishAnimation = CCAnimation::createWithSpriteFrames(spriteFrames);
        fishAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));
        CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), type);
       /* if(type==18)
		{
			Puffer_BAnimation=CCAnimation::createWithSpriteFrames(spriteFrames);
			Puffer_BAnimation->retain();
		}*/
		CCAnimationCache::sharedAnimationCache()->addAnimation(fishAnimation, animationName->getCString());
		
   }
}
void StartLayer::initializationCompleted()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI_GameStartMenuLayer-ipadhd.plist");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
   CCMenuItemSprite* start = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_normal")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_selected")), this, menu_selector(StartLayer::transition));
   CCMenuItemSprite* select = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_normal")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_selected")), this, menu_selector(StartLayer::transitionSelectScene));
   select->setPosition(CCPointMake(0, -winSize.height*0.5));
   CCMenu* menu = CCMenu::create(start,select,NULL);
    menu->setScale(0.4);
	menu->setPosition(CCPointMake(winSize.width*0.2, winSize.height*0.08)); 
    this->removeChild(_progressBar, true);
    this->addChild(menu);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("UI_GameStartMenuLayer-ipadhd.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI_GameMenuText_cn-ipadhd.plist");
	CCSprite* start_text = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_text"));	
    start_text->setScale(0.4);
	start_text->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.4));    
    this->addChild(start_text);
	CCSprite* start_text2 = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_other_014"));	
    start_text2->setScale(0.5);
	start_text2->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.2));    
    this->addChild(start_text2);
/*    PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"));*/
}
void StartLayer::loadingFinished()
{
    this->cacheInit();
    this->initializationCompleted();
}
void StartLayer::progressPercentageSetter(float percentage)
{
    CCString* str = CCString::createWithFormat("%d/100",(int)percentage);
    _progressFg->setString(str->getCString());
}
