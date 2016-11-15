#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CBottom : public Node
{
private:
	cocos2d::Vector<Sprite*> bottomImage;
	Size winSize;
	Layer* bottomLayer;
	std::string bottomName;
	Sprite* bottom_0;
	Sprite* bottom_1;

private:
	void gneraterBottom();

public:
	CBottom();
	~CBottom();

	virtual bool init(std::string _StageName);
	void update(float dt);
	CREATE_FUNC_ARGS(CBottom);
public:
	static Sprite* createBottom(std::string _bottomName, Vec2 _pos); //바닥 배경을 더해준다
};

