#include "PCH.h"
#include "EnemyHelpImage.h"
#include "JsonManager.h"

CEnemyHelpImage::CEnemyHelpImage()
{
}


CEnemyHelpImage::~CEnemyHelpImage()
{
}

bool CEnemyHelpImage::init(HelpIndex _index)
{
	helpIndex = _index;

	if (!generaterHelpImage())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

void CEnemyHelpImage::update(float dt)
{
	stateUpdate();
	moveUpdate();
}

void CEnemyHelpImage::stateUpdate()
{
	if (helpState == eHelpState_Move)
	{
		moveVector = Vec2(1, 0);
	}
	else if (helpState == eHelpState_MoveEnd)
	{
		helpState = eHelpState_Null;
	}
}

void CEnemyHelpImage::moveUpdate()
{
	moveVector.x *= 10 + (PlayerData->getStageCount() * 2);
	if (getPosition().x <= -400)
		helpState = eHelpState_MoveEnd;
	else 
		setPosition(getPosition().x - moveVector.x, getPosition().y);
}

bool CEnemyHelpImage::generaterHelpImage()
{
	if (helpIndex == eHelp_Knife)
	{
		if (!Sprite::initWithFile(JSON_MGR->getFilePathRootWithTag("HelpImage")["HelpKnife"].asString()))
		{
			return false;
		}
	}
	else if (helpIndex == eHelp_Torch)
	{
		if (!Sprite::initWithFile(JSON_MGR->getFilePathRootWithTag("HelpImage")["HelpFire"].asString()))
		{
			return false;
		}
	}
	else if (helpIndex == eHelp_Rope)
	{
		if (!Sprite::initWithFile(JSON_MGR->getFilePathRootWithTag("HelpImage")["HelpRope"].asString()))
		{
			return false;
		}
	}
	helpState = eHelpState_Move;

	return true;
}