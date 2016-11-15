#pragma once

#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"

USING_NS_CC;
#define MAX_MOVE_LENGTH 5000
#define LINEBARIMAGE_WIDTH 1000

class CLineBar : public Node
{
private:
	CREATEWINSIZE;
	LineBarIndex lineBarIndex;
	LineBarState lineBarState;
	Sprite* lineBarStartImage;
	Sprite* lineBarEndImage;
	Sprite* lineBarImage;
	Sprite* playerImage;
	Vec2 startPos;
	Vec2 endPos;
	float moveLength;
	float finishLength;
	float movePersent;
	bool isSceneChange;


private:
	void generaterLineBar();

public:
	CLineBar();
	~CLineBar();

	virtual bool init(LineBarIndex _index);
	void update(float dt);
	CREATE_FUNC_ARGS(CLineBar);
public:
	void setLineBarState(LineBarState _state) { lineBarState = _state; }

	LineBarState getLineBarState() const { return lineBarState; }
	bool getIsSceneChange() const { return isSceneChange; }
	float getLength() const { return moveLength; }
};

