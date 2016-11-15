#pragma once
#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;

#define TAG_TITLE_BACKGROUND 0
#define TAG_BUTTON_MENU 1

#define TAG_GAME_START 2
#define TAG_TREASURE_ROOM 3
#define TAG_OPTION 4
#define TAG_TUTORIAL 5
#define TAG_GAME_EXIT 6

class CTitleScene : public Layer
{
private:
	Label* coinLabel;
	Sprite* coinImage;
	Label* scoreLabel;

	Sprite* titleBackGround;
	Menu*	titleButtonMenu;
	CREATEWINSIZE;


private:

	void generaterHowToPlay();
	void generaterBackGround();
	void generaterButton();
	void generaterLabel();
	void enterTitleButton(Ref* sender);

public:
	CTitleScene();
	~CTitleScene();

	virtual bool init();
	CREATE_FUNC_ARGS(CTitleScene);
	static Scene* createScene();

public:

	Menu* getTitleButtonMenu() const { return titleButtonMenu; }
};

