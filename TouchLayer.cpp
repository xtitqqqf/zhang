#include "StaticData.h"
#include "TouchLayer.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "GameScene4.h"
USING_NS_CC;
bool TouchLayer::init()
{
    this->setTouchEnabled(true);
    return true;
}
GameScene* TouchLayer::getGameScene()
{
    return (GameScene*)this->getParent();
}
bool TouchLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    this->getGameScene()->cannonAimAt(this->locationFromTouch(touch));
    return true;
}
void TouchLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    this->getGameScene()->cannonAimAt(this->locationFromTouch(touch));
}
void TouchLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    this->getGameScene()->cannonShootTo(this->locationFromTouch(touch));
}
void TouchLayer::setTouchEnabled(bool flag)
{
    if (m_bTouchEnabled != flag){
        m_bTouchEnabled = flag;
        if(flag){
            CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        }else{
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
    }
}
CCPoint TouchLayer::locationFromTouch(CCTouch* touch)
{
    //把点从UI坐标系转到GL坐标系
    return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}

