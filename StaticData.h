
#ifndef __FishingJoy__StaticData__
#define __FishingJoy__StaticData__

#include "cocos2d.h"
#define STATIC_DATA_STRING(key) StaticData::sharedStaticData()->stringFromKey(key)
#define STATIC_DATA_INT(key) StaticData::sharedStaticData()->intFromKey(key)
#define STATIC_DATA_FLOAT(key) StaticData::sharedStaticData()->floatFromKey(key)
#define STATIC_DATA_BOOLEAN(key) StaticData::sharedStaticData()->booleanFromKey(key)
#define STATIC_DATA_POINT(key) StaticData::sharedStaticData()->pointFromKey(key)
#define STATIC_DATA_RECT(key) StaticData::sharedStaticData()->rectFromKey(key)
#define STATIC_DATA_SIZE(key) StaticData::sharedStaticData()->sizeFromKey(key)

class StaticData : public cocos2d::CCObject
{
public:    
    static StaticData* sharedStaticData();

    const char* stringFromKey(const string &key);
    int intFromKey(const string &key);
    float floatFromKey(const string &key);
    bool booleanFromKey(const string &key);
    cocos2d::CCPoint pointFromKey(const string &key);
    cocos2d::CCRect rectFromKey(const string &key);
    cocos2d::CCSize sizeFromKey(const string &key);
    
    void purge();
    
    CC_SYNTHESIZE_READONLY(std::string, _staticDataPath, StaticDataPath);

protected:
    cocos2d::CCDictionary* _dictionary;
private:
    StaticData();
    ~StaticData();
    bool init();
};
#endif 
