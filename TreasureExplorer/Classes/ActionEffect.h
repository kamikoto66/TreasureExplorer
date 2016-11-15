#pragma once
#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"

USING_NS_CC;
#define TAG_FIRE_ACTION 0

class CAnimation;

class CActionEffect : public Sprite
{
private:
	EffectState effectState;
	EffectIndex effectIndex;
	EnemyType tergetEnemyType;
	float ropeEffectRotationDelayTime;
	bool isRopeEffectRotation;
	Vec2 basePos;

private:
	void generaterEffect();
	void knifeEffectAction();
	void fireEffectAction();

public:
	CActionEffect();
	~CActionEffect();

	virtual bool init(EffectIndex _index, Vec2 _pos);
	void update(float dt);
	void actionUpdate();

	CREATE_FUNC_ARGS(CActionEffect);

public:
	void setEffectState(EffectState _effectState) { effectState = _effectState; }
	void setEffectIndex(EffectIndex _effectIndex) { effectIndex = _effectIndex; }
	void setIsRopeEffectRotation(bool _isRopeEffectRotation) { isRopeEffectRotation = _isRopeEffectRotation; }

	EffectState getEffectState() const { return effectState; }
	EffectIndex getEffectIndex() const { return effectIndex; }
	EnemyType   getTergetEnemyType() const { return tergetEnemyType; }
};

