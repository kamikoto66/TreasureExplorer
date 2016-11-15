#include "PCH.h"
#include "PauseCount.h"
#include "JsonManager.h"
#include "Player.h"
#include "MainLogic.h"

CPauseCount::CPauseCount()
{
	isThreeCountImageChange = false;
	isTwoCountImageChange = false;
	isOneCountImageChange = false;
	pauseDelayTime = 0.0f;
}


CPauseCount::~CPauseCount()
{
}

bool CPauseCount::init()
{
	bool isReturn = generaterPauseCount();
	this->scheduleUpdate();
	return isReturn;
}

void  CPauseCount::update(float dt)
{
	pauseDelayTime += Director::getInstance()->getDeltaTime();
	if (pauseDelayTime >= 1.0f && pauseDelayTime <= 2.0f && isThreeCountImageChange == false)
	{
		setTexture(Sprite::create(JSON_MGR->getFilePathRootWithTag("PauseStartDelay")["Count_2"].asString())->getTexture());
		isThreeCountImageChange = true;
	}
	else if (pauseDelayTime >= 2.0f && pauseDelayTime <= 3.0f && isTwoCountImageChange == false)
	{
		setTexture(Sprite::create(JSON_MGR->getFilePathRootWithTag("PauseStartDelay")["Count_1"].asString())->getTexture());
		isTwoCountImageChange = true;
	}
	else if (pauseDelayTime >= 3.2f)
	{
		CMainLogic* stage = static_cast<CMainLogic*>(Director::getInstance()->getRunningScene()->getChildByName("Stage"));
		stage->coustemResume();
		stage->setIsPause(false);
		this->removeFromParentAndCleanup(true);
	}
}

bool CPauseCount::generaterPauseCount()
{
	if (!Sprite::initWithFile(JSON_MGR->getFilePathRootWithTag("PauseStartDelay")["Count_3"].asString()))
	{
		return false;
	}

	Vec2 pauseCountPos;
	pauseCountPos.x = PlayerData->getPlayer()->getPosition().x - 50;
	pauseCountPos.y = PlayerData->getPlayer()->getPosition().y + 100;
	setAnchorPoint(Vec2(0.5, 0.5));
	setPosition(pauseCountPos);

	return true;
}