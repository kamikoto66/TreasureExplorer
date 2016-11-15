#pragma once

#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"
#include "Animation.h"

class CButton;
class CAnimation;

#define ATTACKEDENDTIME 0.5f
USING_NS_CC;

class CPlayer : public Node
{
private:
	PlayerState oldPlayerState;
	PlayerState playerState;
	CAnimation* nowPlayerAni;
	CAnimation* runNomal;
	CAnimation* runKnife;
	CAnimation* runFire;
	CAnimation* runRope;
	CAnimation* actionKnife;
	CAnimation* actionFire;
	CAnimation* actionRopeShot;
	CAnimation* actionRopeUp;
	CAnimation* actionRopeDown;

	Sprite* playerBody;
	int runFrameCount;
	bool playerActionStart;
	Color3B baseColor;

	//asdf
	float attackedStartTime;
	bool isAttacked;

private:
	void generaterPlayer();
	static CAnimation* createAnimation(std::string jsonName);

public:
	CPlayer();
	~CPlayer();
	CREATE_FUNC_ARGS(CPlayer);

	//ÀçÁ¤ÀÇ
	virtual bool init();
	void update(float dt);

	void stateUpdate();
	void attackedUpdate();
	void aniUpdate(float dt);

public:
	//set
	void setPlayerState(PlayerState var) { playerState = var; }
	void setPlayerActionStart(bool _isActionStart) { playerActionStart = _isActionStart; }
	void setNowAnimationFrame(int _frameCount) { nowPlayerAni->setCurFrame(_frameCount); }
	void setNowAnimation(PlayerState _state, int _curFrame);
	void setAttackedStartTime(float _time) { attackedStartTime = _time; }	
	void setIsAttacked(bool _isAttacked) { isAttacked = _isAttacked; }

	//get
	PlayerState getPlayerState() const { return playerState; }
	bool getPlayerActionStart() const { return playerActionStart; }
	CAnimation* getNowAnimation() const { return nowPlayerAni; }
	int getNowAnimationFrame() const { return nowPlayerAni->getCurFrame(); }
	Sprite* getPlayerBody() const { return playerBody; }
	float getAttackedStartTime() const { return attackedStartTime; }
	bool getIsAttacked()const { return isAttacked; }
};
