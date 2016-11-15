#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CPauseCount : public Sprite
{
private:
	float pauseDelayTime;
	bool isThreeCountImageChange;
	bool isTwoCountImageChange;
	bool isOneCountImageChange;

private:
	bool generaterPauseCount();

public:
	CPauseCount();
	~CPauseCount();

	virtual bool init();
	void update(float dt);
	CREATE_FUNC_ARGS(CPauseCount);
};

