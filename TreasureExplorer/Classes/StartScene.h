#pragma once
#include "cocos2d.h"
#include "Macro.h"
#define TAG_STARTSCENE_BACKIMAGE 0
#define TAG_LOGOIMAGE 1

USING_NS_CC;

//==========================================
//class name: StartScene
//이 게임시작전에 보여주는 화면 씬
class StartScene : public Layer
{
private:
	CREATEWINSIZE;
	bool isFirstStart;
	Label* touchToScreenLabel;
	Sprite* backImage;
	Sprite* logoImage;

public:
	StartScene();
	~StartScene();

	//재정의
	virtual bool init();
	//재정의
	virtual bool onTouchBegan(Touch * touch, Event * unused_event);
	virtual void onTouchEnded(Touch * touch, Event * unused_event);
	void generaterLabel();
	void generaterTouch();
	void generaterBackGround();
public:
	static Scene * createScene();
	CREATE_FUNC(StartScene);
};

