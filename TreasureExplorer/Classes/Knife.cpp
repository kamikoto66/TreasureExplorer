#include "PCH.h"
#include "Knife.h"
#include "Button.h"
//#include "ButtonData.h"
#include "Player.h"
#include "PlayerData.h"
#include "JsonManager.h"
#include "soundManager.h"

CKnife::CKnife()
{
	isSelect = false;
}


CKnife::~CKnife()
{
}

bool CKnife::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto knife = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["knife_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["knife_1"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["knife_2"].asString(), CC_CALLBACK_0(CKnife::enterKnife, this));
	knife->setAnchorPoint(Point::ZERO);
	knife->setPosition(Point(0, 0));
	knife->setTag(TAG_KNIFE);

	knifeMenu = Menu::create(knife, NULL);
	knifeMenu->setPosition(Point::ZERO);
	this->addChild(knifeMenu);

	return true;
}

void CKnife::enterKnife()
{
	CSoundManager::getInstance()->playEffect("sound.button_1.mp3", false, 2.0f);
	isSelect = true;
}