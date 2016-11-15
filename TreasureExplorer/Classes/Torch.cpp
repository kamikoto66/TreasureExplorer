#include "PCH.h"
#include "Torch.h"
#include "Button.h"
//#include "ButtonData.h"
#include "Player.h"
#include "PlayerData.h"
#include "JsonManager.h"

CTorch::CTorch()
{
	isSelect = false;
}


CTorch::~CTorch()
{
}

bool CTorch::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto torch = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["torch_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["torch_1"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["torch_2"].asString(), CC_CALLBACK_0(CTorch::enterTorch, this));
	torch->setAnchorPoint(Point::ZERO);
	torch->setPosition(Point(150, 0));
	torch->setTag(TAG_TORCH);

	torchMenu = Menu::create(torch, NULL);
	torchMenu->setPosition(Point::ZERO);
	this->addChild(torchMenu);

	return true;
}

void CTorch::enterTorch()
{
	isSelect = true;
}