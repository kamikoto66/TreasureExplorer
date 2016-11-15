#pragma once

#include "cocos2d.h"
#include "Macro.h"

class CThornBush;
class CMoushRoom;
class CPoisonPlant;
class CBottom;

USING_NS_CC;

#define TAG_BACKGROUND_AIR 0
#define TAG_BACKGROUND_B 1
#define TAG_BACKGROUND_C 2
#define TAG_BACKGROUND_D 3

class CBackGround : public Node
{
private:
	Size winSize; //화면 사이즈
	cocos2d::Vector<Sprite*> backGroundVector;


	Vec2 originPos;
	Sprite* backGround_Air_0;
	Sprite* backGround_Air_1;

	Sprite* backGround_B_0;
	Sprite* backGround_B_1;

	Sprite* backGround_C_0;
	Sprite* backGround_C_1;

	Sprite* backGround_D_0;
	Sprite* backGround_D_1;

	std::string stageName;  //현재 스테이지 이미지 이름
	int stageCount;

private:
	void generaterBackGround();

public:
	CBackGround();
	~CBackGround();

	virtual bool init(std::string _stageName, int _stageCount);
	void update(float dt);
	void backGroundMoveUpdate();
	CREATE_FUNC_ARGS(CBackGround);
	void scrollCount();  //스크롤 카운트를 세서 배경이미지를 바꿔준다
	static Sprite* createBackGround(std::string _path, int _tag, Point _pos); //스크롤 배경을 만들어서 배경레이어에 추가

public:
	void setStageCount(int _stageCount) { stageCount = _stageCount; }

	int getStageCount() const { return stageCount; }
};

