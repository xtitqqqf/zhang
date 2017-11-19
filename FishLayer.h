#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class FishLayer :
	public CCLayer
{
public:
	FishLayer(void);
	/*static FishLayer *create()
	{
		FishLayer *layer = new FishLayer();
		if (layer && layer->init())
		{
			layer->autorelease();
			return layer;
		}
		else
		{
			delete layer;
			layer = NULL;
			return NULL;
		}
	}*/
	CREATE_FUNC(FishLayer)
	virtual bool init();
	virtual ~FishLayer(void);
};
