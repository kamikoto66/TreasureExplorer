#pragma once
#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"

USING_NS_CC;

class CEnemyHelpImage : public Sprite
{
private:
	HelpIndex helpIndex;
	HelpState helpState;
	Vec2 moveVector;

private:
	bool generaterHelpImage();

public:
	CEnemyHelpImage();
	~CEnemyHelpImage();

	virtual bool init(HelpIndex _index);
	void update(float dt);
	void stateUpdate();
	void moveUpdate();
	CREATE_FUNC_ARGS(CEnemyHelpImage);
};

