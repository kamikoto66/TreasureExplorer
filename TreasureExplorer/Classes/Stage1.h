#pragma once
#include"cocos2d.h"
#include "Macro.h"

USING_NS_CC;
class CMainLogic;

class CStage1 : public CMainLogic
{

public:
	CStage1();
	~CStage1();

	virtual bool init();
	void update(float dt);
	CREATE_FUNC_ARGS(CStage1);
};

