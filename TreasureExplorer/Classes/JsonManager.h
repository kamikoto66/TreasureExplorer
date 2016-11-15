#pragma once
#include "cocos2d.h"
#include "SingleTon.h"
#include "json.h"
USING_NS_CC;

class CJsonManager : public SingleTon<CJsonManager>
{
private:
	Json::Value filePathRoot;
	FileUtils *fileUtils;
private:
	void gneraterFilePath();

public:
	CJsonManager();
	~CJsonManager();
	
	void init();

public:
	Json::Value getFilePathRoot() const { return filePathRoot; }
	Json::Value getFilePathRootWithTag(std::string _rootTag) { return filePathRoot[_rootTag.c_str()]; }
};

#define JSON_MGR CJsonManager::getInstance()
