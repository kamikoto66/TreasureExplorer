#pragma once
#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;
#define TAG_BACKIMAGE 0
#define TAG_UI 1

class CTreasure;

class CTreasureRoomScene : public Layer
{
private:
	CREATEWINSIZE;
	Sprite* treasureRoomBackImage;
	CTreasure* treasureRoomImage[9];
	Menu* backMenu;

private:
	void generaterBackImage();
	void generaterUi();
	void generaterTreasure();
	void enterTreasure(CTreasure* treasure);
	void enterExit(Ref* sender);
	void treasurePause();

public:
	CTreasureRoomScene();
	~CTreasureRoomScene();

	virtual bool init();
	CREATE_FUNC_ARGS(CTreasureRoomScene);
	static Scene* createScene();
	void treasureResume();

public:

};

