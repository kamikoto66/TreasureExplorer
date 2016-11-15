#pragma once

#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"

USING_NS_CC;

class CBox : public Sprite
{
private:
	BoxIndex boxIndex;
	BoxState boxState;
	Vec2 moveVector;

private:
	void generaterBox();
	void setBoxStateNull(Node* _box, int _BoxState) { auto Coin = static_cast<CBox*>(_box); Coin->setBoxState(static_cast<BoxState>(_BoxState)); }

public:
	CBox();
	~CBox();

	virtual bool init();
	void update(float dt);
	void stateUpdate();
	void moveUpdate();
	void collisionUpdate();

	CREATE_FUNC_ARGS(CBox);

public:
	void setBoxState(BoxState _boxState) { boxState = _boxState; }

	BoxState getBoxState() const { return boxState;}
};

