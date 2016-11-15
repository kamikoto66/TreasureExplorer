#pragma once
#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;

class CHpBar : public Node
{
private:
	int hpCount;
	Sprite* hpBarImageFront;
	Sprite* hpBarImage;
	Sprite* hpImage[5];
	bool isHpImageRender[5];

private:
	void generaterHpBar();

public:
	CHpBar();
	~CHpBar();

	virtual bool init(int hpSize);
	CREATE_FUNC_ARGS(CHpBar);
	void attackedPlayer();

public:
	void setHpCount(int _count) { hpCount = _count; }

	int getHpCount() const { return hpCount; }
};

