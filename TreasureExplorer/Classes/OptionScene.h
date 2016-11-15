#pragma once
#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;

#define TAG_BACKIMAGE 0
#define TAG_SOUNDIMAGE 1
#define TAG_HELPIMAGE 1
#define TAG_OPTIONBUTTON 2
#define TAG_LABEL 3

#define TAG_SOUND 0
#define TAG_HELP 1
#define TAG_EXIT 2

class COptionScene : public Layer
{
private:
	CREATEWINSIZE;
	Menu* optionButton;
	Sprite* optionBackImage;
	Sprite* soundImage;
	Sprite* helpImage;
	bool isSound;
	bool isHelp;
	Sprite* credit;

private:
	void enterRemove();
	void generaterOptionLabel();
	void generaterOptionButton();
	void enterUiButton(Ref* sender);


public:
	COptionScene();
	~COptionScene();

	virtual bool init();
	CREATE_FUNC_ARGS(COptionScene);
};

