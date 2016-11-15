#include "PCH.h"
#include "Box.h"
#include "JsonManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "PlayerData.h"

CBox::CBox()
{
	moveVector = Vec2(0, 0);
	boxIndex = (BoxIndex)-1;
	boxState = (BoxState)-1;
}

CBox::~CBox()
{

}

bool CBox::init()
{
	if (!Node::init())
	{
		return false;
	}

	int _boxIndex = cocos2d::random(0, 300);
	_boxIndex %= 8;
	boxIndex = (BoxIndex)_boxIndex;
	generaterBox();
	this->scheduleUpdate();

	return true;
}

void CBox::update(float dt)
{
	stateUpdate();
	collisionUpdate();
	moveUpdate();
}

void CBox::stateUpdate()
{
	if (boxState == eBoxStateMove)
	{
		moveVector = Vec2(-1, 0);
	}
	else if (boxState == eBoxStateDrop)
	{
		auto fade = FadeOut::create(0.5f);
		auto callFuncN = CallFuncN::create(CC_CALLBACK_1(CBox::setBoxStateNull,this, BoxState::eBoxStateFade));
		auto seq = Sequence::create(fade, callFuncN, NULL);
		this->runAction(seq);
		boxState = BoxState::eBoxStateFade;
	}
}

void CBox::moveUpdate()
{
	moveVector.x *= 10 + (PlayerData->getStageCount() * 2);
	setPosition(getPositionX() + moveVector.x, getPositionY());
}

void CBox::collisionUpdate()
{
	if (PlayerData->getPlayer() != nullptr)
	{
		if (this->getPositionX() <= PlayerData->getPlayer()->getPositionX() + 200)
		{
			if (CollisionManager::getInstance()->CircleCheck(PlayerData->getPlayer()->getPosition(), this->getPosition(), 120) && boxState == eBoxStateMove)
			{
				boxState = eBoxStateDrop;
				moveVector = Vec2(0, 0);
				bool isGet = false;

				switch (boxIndex)
				{
				case    eBoxForestAccessoryShabby:	if (!UserDefault::getInstance()->getBoolForKey("ForestAccessoryBool")) { isGet = true;	UserDefault::getInstance()->setBoolForKey("ForestAccessoryBool", isGet); }	break;
				case 	eBoxRunisAccessoryShabby:	if (!UserDefault::getInstance()->getBoolForKey("RunisAccessoryBool"))  { isGet = true;	UserDefault::getInstance()->setBoolForKey("RunisAccessoryBool", isGet); }	break;
				case 	eBoxSiteAccessoryShabby:	if (!UserDefault::getInstance()->getBoolForKey("SiteAccessoryBool"))   { isGet = true;	UserDefault::getInstance()->setBoolForKey("SiteAccessoryBool", isGet); }	break;
				case 	eBoxForestCapShabby:		if (!UserDefault::getInstance()->getBoolForKey("ForestCapBool"))       { isGet = true;	UserDefault::getInstance()->setBoolForKey("ForestCapBool", isGet); }	break;
				case 	eBoxRunisCapShabby:			if (!UserDefault::getInstance()->getBoolForKey("RunisCapBool"))        { isGet = true;	UserDefault::getInstance()->setBoolForKey("RunisCapBool", isGet); }	break;
				case 	eBoxSiteCapShabby:			if (!UserDefault::getInstance()->getBoolForKey("SiteCapBool"))         { isGet = true;	UserDefault::getInstance()->setBoolForKey("SiteCapBool", isGet); }	break;
				case 	eBoxForestWearShabby:		if (!UserDefault::getInstance()->getBoolForKey("ForestWearBool"))      { isGet = true;	UserDefault::getInstance()->setBoolForKey("ForestWearBool", isGet); }	break;
				case 	eBoxRunisWearShabby:		if (!UserDefault::getInstance()->getBoolForKey("RunisWearBool"))       { isGet = true;	UserDefault::getInstance()->setBoolForKey("RunisWearBool", isGet); }	break;
				case 	eBoxSiteWearShabby:			if (!UserDefault::getInstance()->getBoolForKey("SiteWearBool"))        { isGet = true;	UserDefault::getInstance()->setBoolForKey("SiteWearBool", isGet); }	break;
				}

				if (isGet)
				{
					PlayerData->setBoxIndex(boxIndex);
					PlayerData->setIsTreasureBox(true);
				}
			}
		}
	}
}

void CBox::generaterBox()
{
	Sprite::initWithFile(JSON_MGR->getFilePathRootWithTag("Treasure")["TreasureBox"]["FileName"].asString());
	boxState = BoxState::eBoxStateMove;
}