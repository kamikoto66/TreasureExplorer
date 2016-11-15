#include "PCH.h"
#include "PauseScene.h"
#include "ButtonData.h"
#include "JsonManager.h"
#include "PauseCount.h"
#include "soundManager.h"

CPauseScene::CPauseScene()
{
}


CPauseScene::~CPauseScene()
{
}

bool CPauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto backLayer = CCLayerColor::create(ccc4(0, 0, 0, 50), winSize.width, winSize.height);
	backLayer->setAnchorPoint(ccp(0, 0));
	backLayer->setPosition(ccp(0, 0));
	this->addChild(backLayer);

	makeMenuItem();

	return true;
}

void CPauseScene::makeMenuItem()
{
	auto resumeButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["resume_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["resume_1"].asString(), CC_CALLBACK_1(CPauseScene::menuCallBack, this));
	auto exitButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["exit_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["exit_1"].asString(), CC_CALLBACK_1(CPauseScene::menuCallBack, this));
	resumeButton->setScale(0.3f);
	exitButton->setScale(0.3f);
	resumeButton->setTag(TAG_RESUME);
	exitButton->setTag(TAG_EXIT);

	pauseMenu = Menu::create(resumeButton, exitButton, NULL);
	pauseMenu->alignItemsVertically();
	this->addChild(pauseMenu);
}

void CPauseScene::menuCallBack(Ref* pSender)
{
	auto item = (MenuItemImage*)pSender;

	if (item->getTag() == TAG_RESUME)
	{
		ButtonData->getButton()->sceneResume();
		this->removeFromParentAndCleanup(true);
		auto pauseCount = CPauseCount::create();
		auto stage = static_cast<CMainLogic*>(Director::getInstance()->getRunningScene()->getChildByName("Stage"));
		stage->setIsPause(true);
		stage->coustemPause();
		stage->addChild(pauseCount, 20);
	}
	else if (item->getTag() == TAG_EXIT)
	{
		CSoundManager::getInstance()->stopAllBgms();
		CSoundManager::getInstance()->stopAllEffects();
		ButtonData->getButton()->sceneResume();
		this->removeFromParentAndCleanup(true);
		//게임오버
		auto stage = static_cast<CMainLogic*>(Director::getInstance()->getRunningScene()->getChildByName("Stage"));
		stage->gameOverSceneChange();
	}
}

