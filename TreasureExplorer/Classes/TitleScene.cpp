#include "PCH.h"
#include "TitleScene.h"
#include "JsonManager.h"
#include "GameScene.h"
#include "LodingScene.h"
#include "TreasureRoomScene.h"
#include "OptionScene.h"
#include "TutorialScene.h"
#include "soundManager.h"

CTitleScene::CTitleScene()
{
	titleBackGround = nullptr;
	coinImage = nullptr;
	coinLabel = nullptr;
	scoreLabel = nullptr;
}


CTitleScene::~CTitleScene()
{
}

bool CTitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	generaterHowToPlay();
	generaterBackGround();
	generaterButton();
	generaterLabel();

	return true;
}

void CTitleScene::generaterHowToPlay()
{
	for (Json::Value& pRet : JSON_MGR->getFilePathRootWithTag("HowToPlay"))
	{
		auto spr = Sprite::create(pRet.asString());
	}
}

void CTitleScene::generaterBackGround()
{
	std::string backGroundPath;
	backGroundPath.append("background/");
	backGroundPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["TitleSceneBackGround"]["StageName"].asString() + "/");
	backGroundPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["TitleSceneBackGround"]["FileName"].asString());
	titleBackGround = Sprite::create(backGroundPath);
	titleBackGround->setAnchorPoint(Vec2(0.5, 0.5));
	titleBackGround->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(titleBackGround, TAG_TITLE_BACKGROUND);
}

void CTitleScene::generaterButton()
{
	auto gameStartButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["game_start_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["game_start_1"].asString(), CC_CALLBACK_1(CTitleScene::enterTitleButton, this));
	auto TreasureRoomButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["treasure_room_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["treasure_room_1"].asString(), CC_CALLBACK_1(CTitleScene::enterTitleButton, this));
	auto optionButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["option_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["option_1"].asString(), CC_CALLBACK_1(CTitleScene::enterTitleButton, this));
	auto howToPlayButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["howToPlay_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["howToPlay_1"].asString(), CC_CALLBACK_1(CTitleScene::enterTitleButton, this));
	auto gameExitButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["game_exit_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["game_exit_1"].asString(), CC_CALLBACK_1(CTitleScene::enterTitleButton, this));

	gameStartButton->setTag(TAG_GAME_START);
	TreasureRoomButton->setTag(TAG_TREASURE_ROOM);
	optionButton->setTag(TAG_OPTION);
	howToPlayButton->setTag(TAG_TUTORIAL);
	gameExitButton->setTag(TAG_GAME_EXIT);

	TreasureRoomButton->setAnchorPoint(Vec2(0, 1));
	optionButton->setAnchorPoint(Vec2(0, 1));
	gameExitButton->setAnchorPoint(Vec2(0, 1));

	Vec2 gameStartButtonPos;
	gameStartButtonPos.x = winSize.width / 2;
	gameStartButtonPos.y = winSize.height / 2 + 50;
	gameStartButton->setScale(0.7f);
	gameStartButton->setPosition(gameStartButtonPos);

	Vec2 TreasureRoomButtonPos;
	TreasureRoomButtonPos.x = 0;
	TreasureRoomButtonPos.y = winSize.height - 50;
	TreasureRoomButton->setScale(0.5f);
	TreasureRoomButton->setPosition(TreasureRoomButtonPos);

	Vec2 optionButtonPos;
	optionButtonPos.x = gameStartButtonPos.x + 100;
	optionButtonPos.y = gameStartButtonPos.y - 170;
	optionButton->setScale(0.7f);
	optionButton->setPosition(optionButtonPos);

	Vec2 tutorlalButtonPos;
	tutorlalButtonPos.x = gameStartButtonPos.x+450;
	tutorlalButtonPos.y = gameStartButtonPos.y;
	howToPlayButton->setScale(0.7f);
	howToPlayButton->setPosition(tutorlalButtonPos);

	Vec2 gameExitButtonPos;
	gameExitButtonPos.x = 100;
	gameExitButtonPos.y = winSize.height / 3;
	gameExitButton->setScale(0.6f);
	gameExitButton->setPosition(gameExitButtonPos);

	titleButtonMenu = Menu::create(gameStartButton, TreasureRoomButton, optionButton, howToPlayButton, gameExitButton, NULL);
	titleButtonMenu->setAnchorPoint(Vec2(0, 0));
	titleButtonMenu->setPosition(Vec2(0, 0));
	this->addChild(titleButtonMenu, TAG_BUTTON_MENU);
}

void CTitleScene::enterTitleButton(Ref* sender)
{
	CSoundManager::getInstance()->playEffect("sound/button_1.mp3");

	auto item = (MenuItem*)sender;

	if (item->getTag() == TAG_GAME_START)
	{
		CSoundManager::getInstance()->stopBgm("sound/main.mp3");
		Director::getInstance()->replaceScene(CLodingScene::createScene());
	}
	else if (item->getTag() == TAG_TREASURE_ROOM)
	{
		Director::getInstance()->replaceScene(CTreasureRoomScene::createScene());
	}
	else if (item->getTag() == TAG_OPTION)
	{
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(titleButtonMenu);
		auto optionScene = COptionScene::create();
		optionScene->setScale(0.0f);
		auto scaleTo = ScaleTo::create(0.3f, 1.0f);
		optionScene->runAction(scaleTo);
		this->addChild(optionScene,999);
	}
	else if (item->getTag() == TAG_TUTORIAL)
	{
		Director::getInstance()->replaceScene(CTutorialScene::createScene());
	}
	else if (item->getTag() == TAG_GAME_EXIT)
	{
		Director::getInstance()->end();
	}
}

void CTitleScene::generaterLabel()
{
	std::string scoreString;
	scoreString.append("highScore: ");
	scoreString.append(StringUtils::toString(UserDefault::getInstance()->getIntegerForKey("HighScore")));
	scoreLabel = Label::createWithTTF("highScore: ", "fonts/MoebiusBold.ttf", 25);
	scoreLabel->setColor(Color3B(0, 0, 0));
	scoreLabel->setString(scoreString);
	scoreLabel->setAnchorPoint(Vec2(0, 0));
	scoreLabel->setPosition(Vec2(winSize.width - 400, winSize.height - 100));
	this->addChild(scoreLabel, 10);

	coinImage = Sprite::create("coin/coin.png");
	coinImage->setAnchorPoint(Vec2(0.5, 0.5));
	coinImage->setPosition(Vec2(winSize.width - 400, winSize.height - 50));
	this->addChild(coinImage, 11);

	std::string coinString;
	coinString.append("x: ");
	coinString.append(StringUtils::toString(UserDefault::getInstance()->getIntegerForKey("Coin")));
	coinLabel = Label::createWithTTF("", "fonts/MoebiusBold.ttf", 30);
	coinLabel->setColor(Color3B(0, 0, 0));
	coinLabel->setString(coinString);
	coinLabel->setAnchorPoint(Vec2(0, 0));
	coinLabel->setPosition(Vec2(coinImage->getPosition().x + 25, coinImage->getPosition().y-25));
	this->addChild(coinLabel, 10);
}

Scene* CTitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CTitleScene::create();
	scene->addChild(layer, 0, "CTitleScene");
	return scene;
}