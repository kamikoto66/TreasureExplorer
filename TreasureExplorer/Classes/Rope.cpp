#include "PCH.h"
#include "Rope.h"
#include "Button.h"
//#include "ButtonData.h"
#include "Player.h"
#include "PlayerData.h"
#include "JsonManager.h"

CRope::CRope()
{
	isSelect = false;
}


CRope::~CRope()
{
}

bool CRope::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto Rope = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["rope_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["rope_1"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["rope_2"].asString(), CC_CALLBACK_0(CRope::enterRope, this));
	Rope->setAnchorPoint(Point::ZERO);
	Rope->setPosition(Point(300, 0));
	Rope->setTag(TAG_ROPE);

	ropeMenu = Menu::create(Rope, NULL);
	ropeMenu->setPosition(Point::ZERO);
	this->addChild(ropeMenu);

	return true;
}

void CRope::enterRope()
{
	isSelect = true;
}