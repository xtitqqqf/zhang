
#include "StaticData.h"
USING_NS_CC;
using namespace std;
#define STATIC_DATA_PATH "static_data.plist"
static StaticData* _sharedStaticData = NULL;

StaticData* StaticData::sharedStaticData() 
{

	if (_sharedStaticData == NULL) {
		_sharedStaticData = new StaticData();
		_sharedStaticData->init();
	}
	return _sharedStaticData;
}

void StaticData::purge()
{
    CC_SAFE_RELEASE_NULL(_sharedStaticData);
}

StaticData::StaticData(){

	_staticDataPath = STATIC_DATA_PATH;
}
StaticData::~StaticData(){

	CC_SAFE_RELEASE_NULL(_dictionary);
}

bool StaticData::init(){

	_dictionary = CCDictionary::createWithContentsOfFile(_staticDataPath.c_str());
    CC_SAFE_RETAIN(_dictionary);
    return true;
}

const char* StaticData::stringFromKey(const string &key) {

	return _dictionary->valueForKey(key)->getCString();;
}

//根据键值得到bool类型数据
float StaticData::floatFromKey(const string &key) {

	return _dictionary->valueForKey(key)->floatValue();
}

bool StaticData::booleanFromKey(const string &key)
{
    return _dictionary->valueForKey(key)->boolValue();
}

cocos2d::CCPoint StaticData::pointFromKey(const string &key)
{
    return CCPointFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::CCRect StaticData::rectFromKey(const string &key)
{
    return CCRectFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::CCSize StaticData::sizeFromKey(const string &key)
{
    return CCSizeFromString(_dictionary->valueForKey(key)->getCString());
}


