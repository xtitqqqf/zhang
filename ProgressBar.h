#ifndef __FishingJoy__ProgressBar__
#define __FishingJoy__ProgressBar__
#include "cocos2d.h"
#include "ProgressProtocol.h"
class ProgressBar : public cocos2d::CCProgressTimer
{
public:
  
    static ProgressBar* create(ProgressDelegate* target, cocos2d::CCSprite *sprite);
    bool init(ProgressDelegate* target, cocos2d::CCSprite *sprite);

    void progressBy(float delta);
    void progressTo(float destination);
   
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(ProgressDelegate*, _target, Target);
    CC_PROPERTY(cocos2d::CCNode*, _background, Background);
    CC_PROPERTY(cocos2d::CCNode*, _foreground, Foreground);

protected:
    void updatePercentage();
    void loadingFinished();
};

#endif 
