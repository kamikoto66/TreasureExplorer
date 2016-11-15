#pragma once
#include "cocos2d.h"

class CMainLogic;
class CStage1;
class CStage2;
class CStage3;
USING_NS_CC;

class CGameScene
{
public:
	CGameScene();
	~CGameScene();

	static Scene* createStage1();
	static Scene* createStage2();
	static Scene* createStage3();
	static Scene* createTutoria();
};

