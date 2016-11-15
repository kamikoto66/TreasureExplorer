#include "PCH.h"
#include "Button.h"
#include "Player.h"
#include "PlayerData.h"
#include "Knife.h"
#include "Torch.h"
#include "Rope.h"
#include "PauseScene.h"
#include "soundManager.h"
#include "Button.h"
#include "ButtonData.h"

CButton::CButton()
{
	buttonState = (ButtonState)-1;
	actionAndPauseButton = nullptr;
	knifeDelay.isDelayTime = false;
	knifeDelay.delayTime = 0.0f;
	fireDelay.isDelayTime = false;
	fireDelay.delayTime = 0.0f;
	isRopeDelay = false;
	knife = nullptr;
	torch = nullptr;
	rope = nullptr;
}

CButton::~CButton()
{

}

bool CButton::init()
{
	if (!Node::init())
	{
		return false;
	}
	generaterButton();
	this->scheduleUpdate();

	return true;
}

void CButton::generaterButton()
{
	knife = CKnife::create();
	this->addChild(knife);
	torch = CTorch::create();
	this->addChild(torch);
	rope = CRope::create();
	this->addChild(rope);

	auto actionButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["action_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["action_1"].asString(), CC_CALLBACK_0(CButton::selectButton, this));
	auto pauseButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["pause_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["pause_1"].asString(), CC_CALLBACK_0(CButton::pauseButton, this));

	Vec2 actionButtonPos;
	actionButtonPos.x = winSize.width - 150;
	actionButtonPos.y = 0;
	actionButton->setAnchorPoint(Vec2(0, 0));
	actionButton->setPosition(actionButtonPos);

	Vec2 pauseButtonPos;
	pauseButtonPos.x = winSize.width - 30;
	pauseButtonPos.y = winSize.height - 30;
	pauseButton->setScale(0.5f);
	pauseButton->setPosition(pauseButtonPos);


	actionAndPauseButton = Menu::create(actionButton, pauseButton, NULL);
	actionAndPauseButton->setPosition(Vec2(0, 0));
	this->addChild(actionAndPauseButton);
}

void CButton::update(float dt)
{
	delayUpdate();

	if (knife->getIsSelect() && buttonState != Button_Knife)
	{
		buttonState = Button_Knife;
		torch->setIsSelect(false);
		rope->setIsSelect(false);
		PlayerData->getPlayer()->setPlayerState(Player_Run_Knife);
	}
	else if (torch->getIsSelect() && buttonState != Button_Torch)
	{
		buttonState = Button_Torch;
		knife->setIsSelect(false);
		rope->setIsSelect(false);
		PlayerData->getPlayer()->setPlayerState(Player_Run_Fire);
	}
	else if (rope->getIsSelect() && buttonState != Button_Rope)
	{
		buttonState = Button_Rope;
		torch->setIsSelect(false);
		knife->setIsSelect(false);
		PlayerData->getPlayer()->setPlayerState(Player_Run_Rope);
	}
	ButtonData->setButtonState(buttonState);
}

void CButton::delayUpdate()
{
	if (knifeDelay.isDelayTime)
	{
		knifeDelay.delayTime += Director::getInstance()->getDeltaTime();
		if (knifeDelay.delayTime >= BUTTON_DELAY)
		{
			knifeDelay.isDelayTime = false;
			knifeDelay.delayTime = 0.0f;
			static_cast<MenuItemImage*>(knife->getMenu()->getChildByTag(TAG_KNIFE))->setEnabled(true);
		}
	}

	if (fireDelay.isDelayTime)
	{
		fireDelay.delayTime += Director::getInstance()->getDeltaTime();
		if (fireDelay.delayTime >= BUTTON_DELAY)
		{
			fireDelay.isDelayTime = false;
			fireDelay.delayTime = 0.0f;
			static_cast<MenuItemImage*>(torch->getMenu()->getChildByTag(TAG_TORCH))->setEnabled(true);
		}
	}

	if (isRopeDelay)
	{
		if (PlayerData->getPlayerState() == Player_Run_Rope)
		{
			isRopeDelay = false;
			static_cast<MenuItemImage*>(rope->getMenu()->getChildByTag(TAG_ROPE))->setEnabled(true);
			static_cast<MenuItemImage*>(torch->getMenu()->getChildByTag(TAG_TORCH))->setEnabled(true);
			static_cast<MenuItemImage*>(knife->getMenu()->getChildByTag(TAG_KNIFE))->setEnabled(true);
		}
	}
}

void CButton::selectButton()
{
	if (!knifeDelay.isDelayTime && buttonState == Button_Knife)
	{
		PlayerData->getPlayer()->setPlayerState(Player_Action_Knife);
		static_cast<MenuItemImage*>(knife->getMenu()->getChildByTag(TAG_KNIFE))->setEnabled(false);
		knifeDelay.isDelayTime = true;
		PlayerData->getPlayer()->setPlayerActionStart(true);
	}
	else if (!fireDelay.isDelayTime && buttonState == Button_Torch)
	{
		PlayerData->getPlayer()->setPlayerState(Player_Action_Fire);
		static_cast<MenuItemImage*>(torch->getMenu()->getChildByTag(TAG_TORCH))->setEnabled(false);
		fireDelay.isDelayTime = true;
		PlayerData->getPlayer()->setPlayerActionStart(true);
	}	
	else if (!isRopeDelay && buttonState == Button_Rope)
	{
		CSoundManager::getInstance()->playEffect("sound/rope.mp3");
		PlayerData->getPlayer()->setPlayerState(Player_Action_Rope_Shot);
		static_cast<MenuItemImage*>(rope->getMenu()->getChildByTag(TAG_ROPE))->setEnabled(false);
		static_cast<MenuItemImage*>(torch->getMenu()->getChildByTag(TAG_TORCH))->setEnabled(false);
		static_cast<MenuItemImage*>(knife->getMenu()->getChildByTag(TAG_KNIFE))->setEnabled(false);
		isRopeDelay = true;
		PlayerData->getPlayer()->setPlayerActionStart(true);
	}
}

void CButton::pauseButton()
{
	//CSoundManager::getInstance()->pauseAllBgm();
	Layer* layer = CPauseScene::create();
	scenePause();
	this->addChild(layer);
}

void CButton::scenePause()
{
	Director::getInstance()->pause();
	buttonPause();
}

void CButton::sceneResume()
{
	Director::getInstance()->resume();  
	buttonResume();
	//auto stage = static_cast<CMainLogic*>(Director::getInstance()->getRunningScene()->getChildByName("Stage"));
	//stage->coustemPause();
	//stage->setStartDelay(true);
}

void CButton::buttonPause()
{
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(knife->getMenu());
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(torch->getMenu());
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(rope->getMenu());
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(actionAndPauseButton);
}

void CButton::buttonResume()
{
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(knife->getMenu());
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(torch->getMenu());
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(rope->getMenu());
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(actionAndPauseButton);
}