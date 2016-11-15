#pragma once

#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;
#define MAX_IMAGE_COUNT 6

class CTutorialScene : public Layer
{
private:
	CREATEWINSIZE;
	int curImageCount;
	Sprite* howToPlayCurImage;
	std::vector<Sprite*> howToPlayImageVector;

private:
	void generaterHowToPlay();
	void generaterTouch();
public:
	CTutorialScene();
	~CTutorialScene();

	virtual bool init();
	CREATE_FUNC_ARGS(CTutorialScene);

	virtual bool onTouchBegan(Touch * touch, Event * unused_event);
	virtual void onTouchEnded(Touch * touch, Event * unused_event);
	static Scene* createScene();
};

