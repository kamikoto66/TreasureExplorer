#pragma once
#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"
USING_NS_CC;

#define TAG_GAMEOVERIMAGE 0
#define TAG_SCORELABEL 1
#define TAG_COINIMAGE 2
#define TAG_COINLABEL 3
#define TAG_OKMENU 4

class CGameOverScene : public Layer
{
private:
	CREATEWINSIZE;
	Sprite* gameOverBackImage;
	Label* scoreLabel;
	Label* highScore;
	Sprite* coinImage;
	Label* coinLabel;
	Menu* okButtonMenu;
	bool isTreasureBoxGet;
	BoxIndex boxIndex;
	Label* treasureLabel;

private:
	void enterOkButton();
	void generaterGameOverScene();
	void generaterTouch();
	virtual bool onTouchBegan(Touch * touch, Event * unused_event);
	virtual void onTouchEnded(Touch * touch, Event * unused_event);
public:
	CGameOverScene();
	~CGameOverScene();

	virtual bool init();
	void update();
	CREATE_FUNC_ARGS(CGameOverScene);
	static CGameOverScene* createScene();
};

