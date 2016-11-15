#pragma once
#include "cocos2d.h"
#include "json.h"
#include "Macro.h"

USING_NS_CC;

class CLodingScene : public Layer
{
private:
	CREATEWINSIZE;
	int _numberOfLoadedSprites;
	int _numberOfSprites;
	Label* _labelPercent;
	Label* _labelLoading;

private:
	void generaterLabelAndBackGround();
	void generaterBackGround();
	void generaterButton();
	void generaterUnitBase();
	void gneraterUnitAnimation();
	void gneraterLineBar();
	void gneraterEffect();
	void gneraterTreasure();
	void gneraterHelpImage();
	void gneraterTreasureRoomStateNameImage();
	void gneraterPauseStartDelay();
	void gneraterHpImage();
	void gneraterCoin();

public:
	CLodingScene();
	~CLodingScene();

	virtual bool init();
	CREATE_FUNC(CLodingScene);
	void loadingCallBack(cocos2d::Texture2D *texture);
	void loadFrameImage(std::string charName, std::string aniName, int Frame);
	static Scene* createScene();
};

