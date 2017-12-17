#include "GameScene4.h"
#include "StaticData.h"
#include "FishingJoyData.h"
#include "StartScene.h"
#include "GoldCounterLayer.h"
#include "PersonalAudioEngine.h"
USING_NS_CC;

void GameScene4::onEnterTransitionDidFinish()
{
    CCScene::onEnterTransitionDidFinish();
    PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"),true);
}
bool GameScene4::init()
{
    //preloadResources();	
    if(CCScene::init()){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();        
        CCSprite* background = CCSprite::create(STATIC_DATA_STRING("game_background_04"));
		background->setScale(1);
        background->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
        this->addChild(background);
        
        _fishLayer = FishLayer::create();
        this->addChild(_fishLayer);
        
        _cannonLayer = CannonLayer::create();
        this->addChild(_cannonLayer);
        
        _panelLayer = PanelLayer::create();
        this->addChild(_panelLayer);

        _menuLayer = MenuLayer::create();
        CC_SAFE_RETAIN(_menuLayer);

		_touchLayer=TouchLayer::create();
		this->addChild(_touchLayer);
        this->scheduleUpdate();
        return true;
    }
    return false;
}
void GameScene4::pause()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Pause);
    this->addChild(_menuLayer);
}
void GameScene4::resume()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Resume);
    this->removeChild(_menuLayer, false);
}
void GameScene4::sound()
{
	bool flag = FishingJoyData::sharedFishingJoyData()->getSoundVolume()>0;
    PersonalAudioEngine::sharedEngine()->setEffectsVolume(!flag);
}
void GameScene4::music()
{
	bool flag = FishingJoyData::sharedFishingJoyData()->getMusicVolume()>0;
    PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(!flag);
}
void GameScene4::reset()
{
	this->removeChild(_menuLayer,false);
	CCDirector::sharedDirector()->replaceScene(GameScene4::create()); 
}
void GameScene4::transToMainMenu()
{
	CCDirector::sharedDirector()->replaceScene(StartLayer::scene()); 
}
GameScene4::~GameScene4()
{
    CC_SAFE_RELEASE(_menuLayer);
}
void GameScene4::alterGold(int delta)
{
    FishingJoyData::sharedFishingJoyData()->alterGold(delta);
    _panelLayer->getGoldCounterLayer()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
}
/*void GameScene4::scheduleTimeUp()
{
    this->alterGold(STATIC_DATA_INT("recovery_gold"));
}
*/
void GameScene4::cannonAimAt(CCPoint target)
{
    _cannonLayer->aimAt(target);
}
void GameScene4::cannonShootTo(CCPoint target)
{
    _cannonLayer->shootTo(target);
}
void GameScene4::update(float delat)
{
    checkOutCollision();
}
void GameScene4::checkOutCollision()
{
    Weapon* weapon = _cannonLayer->getWeapon();
    if(weapon->weaponStatus() == k_Weapon_Status_Bullet){
        bool flag =this->checkOutCollisionBetweenFishesAndBullet();
        if(flag){
           this->checkOutCollisionBetweenFishesAndFishingNet();
        }
    }
}
bool GameScene4::checkOutCollisionBetweenFishesAndBullet()
{
    Weapon* weapon = _cannonLayer->getWeapon();
    CCPoint bulletCollision = weapon->getCollisionPoint();
    CCArray* fishes = _fishLayer->getFishes();
    CCObject* iterator;
    CCARRAY_FOREACH(fishes, iterator){
        Fish* fish = (Fish*)iterator;
        //isRunnning判断fish是否已经在屏幕上显示
        if(fish->isRunning()){
            CCRect fishCollisionArea = fish->getCollisionArea();
            bool isCollision = fishCollisionArea.containsPoint(bulletCollision);
            if(isCollision){
                weapon->end();
                return true;
            }
        }
    }
    return false;
}
void GameScene4::checkOutCollisionBetweenFishesAndFishingNet()
{
    Weapon* weapon = _cannonLayer->getWeapon();
    CCRect bulletCollision = weapon->getCollisionArea();
    CCArray* fishes = _fishLayer->getFishes();
    CCObject* iterator;
    CCARRAY_FOREACH(fishes, iterator){
        Fish* fish = (Fish*)iterator;
        //isRunnning判断fish是否已经在屏幕上显示
        if(fish->isRunning()){
            CCRect fishCollisionArea = fish->getCollisionArea();
            bool isCollision = fishCollisionArea.intersectsRect(bulletCollision);
            if(isCollision){
                this->fishWillBeCaught(fish);
            }
        }
    }
}
void GameScene4::fishWillBeCaught(Fish* fish)
{
    int weaponType = _cannonLayer->getWeapon()->getCannonType();
    int fishType = fish->getType();
    float fish_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("fish_percentage_format"),fishType)->getCString());
    float weapon_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("weapon_percentage_format"),weaponType)->getCString());
    float percentage = weapon_percentage * fish_percentage;
    if(CCRANDOM_0_1() < percentage){
        fish->beCaught();
    }
}
void GameScene4::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
    if(node->isRunning()){
        switch (flag) {
            case k_Operate_Pause:
                node->pauseSchedulerAndActions();
                break;
            case k_Operate_Resume:
                node->resumeSchedulerAndActions();
                break;
            default:
                break;
        }
        CCArray* array = node->getChildren();
        if(array != NULL && array->count()>0){
            CCObject* iterator;
            CCARRAY_FOREACH(array, iterator){
                CCNode* child = (CCNode*)iterator;
                this->operateAllSchedulerAndActions(child, flag);
            }
        }
    }
}
