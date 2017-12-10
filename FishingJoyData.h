
#ifndef __FishingJoy__FishingJoyData__
#define __FishingJoy__FishingJoyData__
#include "cocos2d.h"
typedef enum{
    k_Operate_Pause = 0,
    k_Operate_Resume=1,
}OperateFlag;
class FishingJoyData : public cocos2d::CCObject
{
public:
    static FishingJoyData* sharedFishingJoyData();
    CC_SYNTHESIZE(int , _gold, Gold);
    CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
    CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
    CC_SYNTHESIZE(float, _musicVolume, MusicVolume);
    
    void purge();
    void flush();
    void alterGold(int delta);
    void reset();
protected:
    FishingJoyData();
    ~FishingJoyData();
    bool init();
};

#endif /* defined(__FishingJoy__FishingJoyData__) */
