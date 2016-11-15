#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define BUTTON_DELAY 1.0f
#define TAG_KNIFE 0
#define TAG_TORCH 1
#define TAG_ROPE 2

struct ButtonDelay
{
	bool isDelayTime;
	float delayTime;
};
class CKnife;
class CTorch;
class CRope;

class CButton : public Node
{
private:
	CREATEWINSIZE;
	ButtonState buttonState;
	Menu* actionAndPauseButton;
	ButtonDelay knifeDelay;
	ButtonDelay fireDelay;
	bool isRopeDelay;

	CKnife* knife;
	CTorch* torch;
	CRope* rope;

private:
	void generaterButton();
	void selectButton();
	void pauseButton();


public:
	CButton();
	~CButton();

	virtual bool init();
	void update(float dt);
	void delayUpdate();
	void scenePause();
	void sceneResume();

	CREATE_FUNC_ARGS(CButton);

	void buttonPause();
	void buttonResume();

public:
	void setButtonState(ButtonState _state) { buttonState = _state; }

	ButtonState getButtonState() const { return buttonState; }
};

