#include "PCH.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

bool CollisionManager::Circle_Check(float x1, float y1, float x2, float y2, float size)
{
	if ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) <= size * size)
	{
		// 충돌 일시 true를 리턴
		return true;
	}

	// 충돌이 아닐시 false 리턴
	return false;
}

bool CollisionManager::CircleCheck(Vec2 targetPos, Vec2 attackPos,float size)
{
	if ((attackPos.x - targetPos.x) * (attackPos.x - targetPos.x) + (attackPos.y - targetPos.y) * (attackPos.y - targetPos.y) <= size * size)
	{
		// 충돌 일시 true를 리턴
		return true;
	}

	// 충돌이 아닐시 false 리턴
	return false;
}

//bool CollisionManager::RectByRect(Rect rect1, Rect rect2)
//{
//	if (rect1.origin.x < rect2.origin.x + rect2.size.width &&
//		rect1.origin.x + rect1.size.width > rect2.origin.x &&
//		rect1.origin.y < rect2.origin.y + rect2.size.height &&
//		rect1.size.height + rect1.origin.y > rect2.origin.y) {
//		// collision detected!
//		return true;
//	}
//	return false;
//}

bool CollisionManager::LIneToDot(Vec2 linePos, float dot)
{
	if (linePos.x <= dot && linePos.x >= dot)
	{
		CCLOG("LineToDot");
		return true;
	}

	return false;
}