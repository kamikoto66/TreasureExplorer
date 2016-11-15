#pragma once
#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;

class CStage3 : public CMainLogic
{
public:
	CStage3();
	~CStage3();

	virtual bool init();
	void update(float dt);
	CREATE_FUNC_ARGS(CStage3);
};