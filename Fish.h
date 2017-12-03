#ifndef __FishingJoy__Fish__
#define __FishingJoy__Fish__
#include "cocos2d.h"
#include "RotateWithAction.h"
typedef enum{
    //k_Fish_Type_Red = 0,
    //k_Fish_Type_Yellow=1,
	//k_Fish_Type_Count
	k_Fish_Type_SmallFish = 0,
	    k_Fish_Type_Croaker,
	    //鱼的数量，可以根据测试的需要调整位置，在这里值是2
	    k_Fish_Type_AngelFish,
		k_Fish_Type_Amphiprion,	//小丑鱼
		k_Fish_Type_PufferS,	//刺豚
		k_Fish_Type_Bream,		//蓝色
		k_Fish_Type_Progy,		//红色
		k_Fish_Type_Chelonian,	//乌龟
		k_Fish_Type_Lantern,	//灯笼鱼
		k_Fish_Type_Ray,		//魔鬼鱼
		k_Fish_Type_Shark,		//蓝色鲨鱼
		k_Fish_Type_GoldenTrout,
		k_Fish_Type_GShark,		//金色鲨鱼
		k_Fish_Type_GMarlineFish,
		k_Fish_Type_GrouperFish,
		k_Fish_Type_JadePerch,	//宝石鱼
		k_Fish_Type_MarlineFish,
		k_Fish_Type_PufferB,	//刺豚受到攻击
		k_Fish_Type_Count,//k_Fish_Type_Count    
}FishType;

class Fish : public cocos2d::CCNode
{
public:
    static Fish* create(FishType type = k_Fish_Type_SmallFish);
    bool init(FishType type = k_Fish_Type_SmallFish);
    CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, _fishSprite, FishSprite);
    CC_SYNTHESIZE_READONLY(int, _type, Type);
	cocos2d::CCRect getCollisionArea();
	void beCaught();
	void moveTo(cocos2d::CCPoint destination);
	void moveEnd();
	void reset();
	void moveBezier(cocos2d::CCPoint destination);
	void Fish::moveIn(int direction);
	CC_SYNTHESIZE_READONLY(RotateWithAction*,_RotateWithAction,RotateWithAction);
protected:
	void beCaught_CallFunc();
};

#endif
