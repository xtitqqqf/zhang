#ifndef __FishingJoy__FishingNet__
#define __FishingJoy__FishingNet__
#include "cocos2d.h"
class FishingNet : public cocos2d::CCNode
{
public:
    CREATE_FUNC(FishingNet);
    bool init();
    void showAt(cocos2d::CCPoint pos);
    cocos2d::CCRect getCollisionArea();

protected:
    cocos2d::CCSprite *_fishingNetSprite;
    cocos2d::CCAction* netAction();
};
#endif
