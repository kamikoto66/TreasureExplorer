#pragma once
#include "cocos2d.h"
#include "Macro.h"
#define TAG_STARTSCENE_BACKIMAGE 0
#define TAG_LOGOIMAGE 1

USING_NS_CC;

//==========================================
//class name: StartScene
//�� ���ӽ������� �����ִ� ȭ�� ��
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

	//������
	virtual bool init();
	//������
	virtual bool onTouchBegan(Touch * touch, Event * unused_event);
	virtual void onTouchEnded(Touch * touch, Event * unused_event);
	void generaterLabel();
	void generaterTouch();
	void generaterBackGround();
public:
	static Scene * createScene();
	CREATE_FUNC(StartScene);
};

