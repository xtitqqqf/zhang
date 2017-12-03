#include "Fish.h"
#include "StaticData.h"
#include "StartScene.h"

USING_NS_CC;
extern CCAnimation* Puffer_BAnimation;
enum{
    k_Action_Animate = 0,
    k_Action_MoveTo
};
Fish* Fish::create(FishType type)
{
    Fish* fish = new Fish();
    fish->init(type);
    fish->autorelease();
    return fish;
}
bool Fish::init(FishType type)
{
    _type = type;
	CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), _type);
    CCAnimation* fishAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
	CCAnimate* fishAnimate = CCAnimate::create(fishAnimation);
	fishAnimate->retain();
    fishAnimate->setTag(k_Action_Animate);
    _fishSprite = CCSprite::create();
	this->addChild(_fishSprite);
    _fishSprite->runAction(CCRepeatForever::create(fishAnimate));
	_fishSprite->setFlipX(true);
    _fishSprite->setScale(0.5);
	return true;
}
CCRect Fish::getCollisionArea()
{
    CCAssert(this->getParent(), "You Should Call This After Add it as a child");
    CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
    CCSize size = _fishSprite->getContentSize();
    return CCRectMake(origin.x, origin.y, size.width, size.height);
}
void Fish::beCaught()
{
	//CCAnimation* fishAnimation;
	//CCAnimate* fishAnimate;
	this->stopAllActions();
	/*switch(this->getType()){
	case 4:
		fishAnimation=CCAnimationCache::sharedAnimationCache()->animationByName(STATIC_DATA_STRING("fish_animation_18"));
		fishAnimate=CCAnimate::create(fishAnimation);
		this->runAction(fishAnimate);
		break;
	default:
		break;
	}	*/
    
    CCDelayTime* delayTime = CCDelayTime::create(1.0);
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fish::beCaught_CallFunc));
    CCFiniteTimeAction* seq = CCSequence::create(delayTime, callFunc, NULL);
    
    CCBlink* blink = CCBlink::create(1.0, 8);
    CCFiniteTimeAction *spawn = CCSpawn::create(seq, blink, NULL);
    this->runAction(spawn);
}
void Fish::beCaught_CallFunc()
{
    this->getParent()->removeChild(this, false);
}
void Fish::moveTo(CCPoint destination)
{
    CCPoint start = this->getParent()->convertToWorldSpace(this->getPosition());
    float speed = ccpDistance(destination, start) / CCRANDOM_0_1()*100;
    CCMoveTo* moveTo = CCMoveTo::create(speed ,destination);
    CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));    
    CCFiniteTimeAction* seq = CCSequence::create(moveTo, callfunc, NULL);
    seq->setTag(k_Action_MoveTo);
    this->runAction(seq);
}
void Fish::moveIn(int direction){
	//CCPoint fishPoint=this->getPosition;
	CCFiniteTimeAction* in;
	if(direction){
	in=CCMoveBy::create(10,ccp(10,0));
	}
	else{
	in=CCMoveBy::create(10,ccp(-10,0));
	}
	this->runAction(in);
}
void Fish::moveBezier(CCPoint destination){
	CCPoint start = this->getParent()->convertToWorldSpace(this->getPosition());
	float speed = ccpDistance(destination, start) / 20;
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    ccBezierConfig bezier1;
	ccBezierConfig bezier2;
	bezier1.controlPoint_1=bezier2.controlPoint_2=ccp(CCRANDOM_0_1()*winSize.width/2,CCRANDOM_0_1()*winSize.height/2);
	bezier1.controlPoint_2=bezier2.controlPoint_1=ccp(CCRANDOM_0_1()*winSize.width/2,CCRANDOM_0_1()*winSize.height/2);
	if(destination.x){
	bezier1.endPosition=ccp(destination.x/2,destination.y/2);
	bezier2.endPosition=ccp(destination.x,destination.y);
	}else{
		bezier1.endPosition=ccp((winSize.width-destination.x)/2,destination.y/2);
	bezier2.endPosition=ccp(destination.x,destination.y);
	}

	CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));

    CCActionInterval* beizerAction1=CCBezierTo::create(speed/CCRANDOM_0_1()*0.1,bezier1);
	CCActionInterval* beizerAction2=CCBezierTo::create(speed/CCRANDOM_0_1()*0.1,bezier2);
	CCActionInterval* seq = CCSequence::create(CCSpawn::create(beizerAction1,CCRotateBy::create(speed/CCRANDOM_0_1()*4,90)), CCSpawn::create(beizerAction2,CCRotateBy::create(speed/CCRANDOM_0_1()*4,-90)),callfunc, NULL);
	this->runAction(RotateWithAction::create(seq));	
    Fish::moveEnd();	
}
void Fish::moveEnd(){
	//this->runAction(CCFadeIn::create(1));
 this->removeChild(this, false);
}
void Fish::reset()
{
    this->setRotation(0);
    this->setVisible(true);
}
