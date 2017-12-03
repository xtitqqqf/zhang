#ifndef __FishingJoy__Cannon__
#define __FishingJoy__Cannon__
#include "cocos2d.h"
#include "Bullet.h"
typedef enum{
    k_Cannon_Type_1 = 0,
    k_Cannon_Type_2,
	k_Cannon_Type_3,
	k_Cannon_Type_4,
    k_Cannon_Type_Count,
    k_Cannon_Type_Invalid
}CannonType;
class Cannon : public cocos2d::CCNode
{
public:
    Cannon();
    ~Cannon();
    static Cannon* create(CannonType type = k_Cannon_Type_1);
    bool init(CannonType type = k_Cannon_Type_1);
    
    void aimAt(cocos2d::CCPoint target);
    CC_PROPERTY(CannonType, _type, Type);
    //»ñÈ¡µ±Ç°µÄcannonSprite
    cocos2d::CCSprite* getCurCannonSprite();
protected:
    cocos2d::CCArray* _cannonSprites;
};

#endif
