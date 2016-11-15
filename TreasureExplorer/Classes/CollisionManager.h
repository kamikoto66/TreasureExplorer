#pragma once
#include "SingleTon.h"
#include "cocos2d.h"

USING_NS_CC;

class CollisionManager : public SingleTon<CollisionManager>
{
public:
	CollisionManager();
	~CollisionManager();

	bool Circle_Check(float x1, float y1, float x2, float y2, float size);
	bool CircleCheck(Vec2 targetPos, Vec2 attackPos, float size);
	bool LIneToDot(Vec2 linePos, float dot);

};
#define Collision_MGR CollisionManager::getInstance()
