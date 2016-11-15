#include "PCH.h"
#include "OptionScene.h"
#include "JsonManager.h"
#include "soundManager.h"

COptionScene::COptionScene()
{
	helpImage = nullptr;
	soundImage = nullptr;
	optionBackImage = nullptr;
	optionButton = nullptr;
	isSound = false;
	isHelp = false;
	credit = nullptr;
}


COptionScene::~COptionScene()
{
}

bool COptionScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	isSound = UserDefault::getInstance()->getBoolForKey("Sound");
	isHelp = UserDefault::getInstance()->getBoolForKey("Help");

	generaterOptionButton();
	generaterOptionLabel();

	return true;
}

void COptionScene::generaterOptionButton()
{
	optionBackImage = Sprite::create("background/OptionScene/optionBackImage.png");
	optionBackImage->setAnchorPoint(Vec2(0.5, 0.5));
	optionBackImage->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(optionBackImage, TAG_BACKIMAGE);
	
	std::string soundImagePath;
	soundImagePath.append("background/");
	soundImagePath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["OptionSceneSound"]["StageName"].asString() + "/");
	soundImagePath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["OptionSceneSound"]["FileName"].asString());

	soundImage = Sprite::create(soundImagePath);
	soundImage->setPosition(optionBackImage->getPosition().x - 300, optionBackImage->getPosition().y + 50);
	this->addChild(soundImage, TAG_SOUNDIMAGE);

	std::string helpImagePath;
	helpImagePath.append("background/");
	helpImagePath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["OptionSceneHelp"]["StageName"].asString() + "/");
	helpImagePath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["OptionSceneHelp"]["FileName"].asString());

	helpImage = Sprite::create(helpImagePath);
	helpImage->setPosition(optionBackImage->getPosition().x - 300, optionBackImage->getPosition().y- 50);
	this->addChild(helpImage, TAG_HELPIMAGE);

	auto soundOffButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["sound_off_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["sound_off_1"].asString());
	auto soundOnButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["sound_on_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["sound_on_1"].asString());

	MenuItemToggle* soundButton;

	if (isSound)
		soundButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(COptionScene::enterUiButton, this), soundOnButton, soundOffButton, NULL);
	else 
		soundButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(COptionScene::enterUiButton, this), soundOffButton, soundOnButton, NULL);

	auto helpImageButton_0 = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["help_off_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["help_off_1"].asString());
	auto helpImageButton_1 = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["help_on_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["help_on_1"].asString());
	MenuItemToggle* helpButton;

	if (isHelp)
		helpButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(COptionScene::enterUiButton, this), helpImageButton_1, helpImageButton_0, NULL);
	else 
		helpButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(COptionScene::enterUiButton, this), helpImageButton_0, helpImageButton_1, NULL);

	MenuItemImage* exitButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["option_back_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["option_back_1"].asString(), CC_CALLBACK_1(COptionScene::enterUiButton, this));

	Vec2 soundButtonPos;
	soundButtonPos.x = soundImage->getPosition().x + 150;
	soundButtonPos.y = soundImage->getPosition().y;
	soundButton->setPosition(soundButtonPos);

	Vec2 helpButtonPos;
	helpButtonPos.x = helpImage->getPosition().x + 150;
	helpButtonPos.y = helpImage->getPosition().y;
	helpButton->setPosition(helpButtonPos);

	Vec2 exitButtonPos;
	exitButtonPos.x = optionBackImage->getPosition().x + 400;
	exitButtonPos.y = optionBackImage->getPosition().y + 190;
	exitButton->setPosition(exitButtonPos);

	soundButton->setTag(TAG_SOUND);
	helpButton->setTag(TAG_HELP);
	exitButton->setTag(TAG_EXIT);

	optionButton = Menu::create(soundButton, helpButton, exitButton, NULL);
	optionButton->setAnchorPoint(Vec2(0, 0));
	optionButton->setPosition(Vec2(0, 0));
	this->addChild(optionButton, TAG_OPTION);
}

void COptionScene::generaterOptionLabel()
{
	std::string creditPath;
	creditPath.append("background/");
	creditPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["OptionCredit"]["StageName"].asString() + "/");
	creditPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["OptionCredit"]["FileName"].asString());
	credit = Sprite::create(creditPath);
	credit->setScale(0.5f);
	credit->setAnchorPoint(Vec2(0, 1));
	credit->setPosition(optionBackImage->getPosition().x + 50, optionBackImage->getPosition().y + 130);
	this->addChild(credit, 3);
}

void COptionScene::enterUiButton(Ref* sender)
{
	CSoundManager::getInstance()->playEffect("sound/button_1.mp3");

	auto item = (MenuItem*)sender;

	if (item->getTag() == TAG_SOUND)
	{
		isSound = !isSound;
		UserDefault::getInstance()->setBoolForKey("Sound",isSound);
		UserDefault::getInstance()->flush();

		CSoundManager::getInstance()->setBgmOn(isSound);
		CSoundManager::getInstance()->setEffectOn(isSound);

		if (isSound)
			CSoundManager::getInstance()->playBgm("sound/main.mp3");
	}
	else if (item->getTag() == TAG_HELP)
	{
		isHelp = !isHelp;
		UserDefault::getInstance()->setBoolForKey("Help", isHelp);
		UserDefault::getInstance()->flush();
	}
	else if (item->getTag() == TAG_EXIT)
	{
		auto scaleTo_0 = ScaleTo::create(0.2f, 1.1f);
		auto scaleTo_1 = ScaleTo::create(0.2f, 0.0f);
		auto callFunc = CallFunc::create(CC_CALLBACK_0(COptionScene::enterRemove, this));
		auto seq = Sequence::create(scaleTo_0, scaleTo_1, callFunc, NULL);
		runAction(seq);
	}
}

void COptionScene::enterRemove()
{
	auto scene = static_cast<CTitleScene*>(Director::getInstance()->getRunningScene()->getChildByName("CTitleScene"));
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(scene->getTitleButtonMenu());
	this->removeFromParentAndCleanup(true);
}