#pragma once
#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;
#define TAG_RESUME 0
#define TAG_EXIT 1

class CPauseScene : public Layer
{
private:
	Menu * pauseMenu;
	CREATEWINSIZE;

private:
	void makeMenuItem();

public:
	CPauseScene();
	~CPauseScene();

	virtual bool init();
	CREATE_FUNC_ARGS(CPauseScene);
	static Scene* createScene();

public:
	void menuCallBack(Ref* pSender);
};

