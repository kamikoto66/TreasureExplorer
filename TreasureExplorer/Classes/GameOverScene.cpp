#include "PCH.h"
#include "GameOverScene.h"
#include "PlayerData.h"
#include "ButtonData.h"
#include "JsonManager.h"


CGameOverScene::CGameOverScene()
{
	gameOverBackImage = nullptr;
	scoreLabel = nullptr;
	highScore = nullptr;
	isTreasureBoxGet = PlayerData->getIsTreasureBox();
	boxIndex = PlayerData->getBoxIndex();
	coinImage = nullptr;
	coinLabel = nullptr;
	okButtonMenu = nullptr;
}


CGameOverScene::~CGameOverScene()
{
}

bool CGameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	generaterGameOverScene();
	generaterTouch();

	return true;
}

void CGameOverScene::generaterGameOverScene()
{
	auto stage = static_cast<CMainLogic*>(Director::getInstance()->getRunningScene()->getChildByName("Stage"));
	stage->coustemPause();

	auto backLayer = LayerColor::create(ccc4(0, 0, 0, 50), winSize.width, winSize.height);
	backLayer->setAnchorPoint(ccp(0, 0));
	backLayer->setPosition(ccp(0, 0));
	this->addChild(backLayer);

	std::string gameOverBackImagePath;
	gameOverBackImagePath.append("background/");
	gameOverBackImagePath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["gameOverSceneBackGround"]["StageName"].asString() + "/");
	gameOverBackImagePath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["gameOverSceneBackGround"]["FileName"].asString());
	gameOverBackImage = Sprite::create(gameOverBackImagePath);
	gameOverBackImage->setAnchorPoint(Vec2(0.5, 0.5));
	gameOverBackImage->setPosition(Vec2(winSize.width/2, winSize.height/2));
	this->addChild(gameOverBackImage, TAG_GAMEOVERIMAGE);

	std::string scoreString;
	scoreString.append(StringUtils::toString(PlayerData->getScore()));
	Vec2 scorePos;
	scorePos.x = gameOverBackImage->getPosition().x;
	scorePos.y = gameOverBackImage->getPosition().y;

	scoreLabel = Label::createWithTTF("", "fonts/MoebiusBold.ttf", 40);
	scoreLabel->setAnchorPoint(Vec2(1,0));
	scoreLabel->setPosition(scorePos);
	scoreLabel->setString(scoreString);
	this->addChild(scoreLabel, TAG_SCORELABEL);

	if (isTreasureBoxGet)
	{
		Vec2 treasureLabelPos;
		treasureLabelPos.x = gameOverBackImage->getPosition().x + 100;
		treasureLabelPos.y = gameOverBackImage->getPosition().y - 100;
		treasureLabel = Label::createWithTTF("TreasureBoxGet!!", "fonts/MoebiusBold.ttf", 40);
		treasureLabel->setPosition(treasureLabelPos);
		treasureLabel->setColor(Color3B(255, 255, 255));
		this->addChild(treasureLabel, 99);
		switch (PlayerData->getBoxIndex())
		{
		case    eBoxForestAccessoryShabby:	UserDefault::getInstance()->setIntegerForKey("ForestAccessory", 0);	break;
		case 	eBoxRunisAccessoryShabby:	UserDefault::getInstance()->setIntegerForKey("RunisAccessory",1); 	break;
		case 	eBoxSiteAccessoryShabby:	UserDefault::getInstance()->setIntegerForKey("SiteAccessory",2); 	break;
		case 	eBoxForestCapShabby:		UserDefault::getInstance()->setIntegerForKey("ForestCap",3); 	break;
		case 	eBoxRunisCapShabby:			UserDefault::getInstance()->setIntegerForKey("RunisCap",4); 	break;
		case 	eBoxSiteCapShabby:			UserDefault::getInstance()->setIntegerForKey("SiteCap",5); 	break;
		case 	eBoxForestWearShabby:		UserDefault::getInstance()->setIntegerForKey("ForestWear",6); 	break;
		case 	eBoxRunisWearShabby:		UserDefault::getInstance()->setIntegerForKey("RunisWear",7); 	break;
		case 	eBoxSiteWearShabby:			UserDefault::getInstance()->setIntegerForKey("SiteWear",8); 	break;
		}
	}


	if (PlayerData->getScore() > UserDefault::getInstance()->getIntegerForKey("HighScore"))
	{
		highScore = Label::createWithTTF("HighScore", "fonts/MoebiusBold.ttf", 40);
		highScore->setAnchorPoint(Vec2(1, 0));
		highScore->setPosition(scoreLabel->getPosition().x - 200, scoreLabel->getPosition().y);
		this->addChild(highScore, TAG_SCORELABEL);
	}

	Vec2 coinImagePos;
	coinImagePos.x = gameOverBackImage->getPositionX()-350;
	coinImagePos.y = gameOverBackImage->getPositionY()-100;

	coinImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("Coin")["gameOverCoinScore"].asString());
	coinImage->setScale(1.5f);
	coinImage->setAnchorPoint(Vec2(0.5, 0.5));
	coinImage->setPosition(coinImagePos);
	this->addChild(coinImage, TAG_COINIMAGE);

	std::string coinLabelString;
	coinLabelString.append("x ");
	coinLabelString.append(StringUtils::toString(PlayerData->getCoin()));
	Vec2 coinLabelPos;
	coinLabelPos.x = coinImage->getPosition().x + 100;
	coinLabelPos.y = coinImage->getPositionY();
	coinLabel = Label::createWithTTF("", "fonts/MoebiusBold.ttf", 40);
	coinLabel->setString(coinLabelString);
	coinLabel->setAnchorPoint(Vec2(0.5, 0.5));
	coinLabel->setPosition(coinLabelPos);
	this->addChild(coinLabel, TAG_COINLABEL);

	auto okButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["btnOk_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["btnOk_1"].asString(), CC_CALLBACK_0(CGameOverScene::enterOkButton, this));
	Vec2 okButtonPos;
	okButtonPos.x = gameOverBackImage->getPosition().x;
	okButtonPos.y = winSize.height / 4;
	okButton->setAnchorPoint(Vec2(0.5, 0.5));
	okButton->setPosition(okButtonPos);

	okButtonMenu = Menu::create(okButton, NULL);
	okButtonMenu->setPosition(Vec2(0, 0));
	this->addChild(okButtonMenu, TAG_OKMENU);
}

void CGameOverScene::enterOkButton()
{
	int score = PlayerData->getScore();
	//coin
	int coin = PlayerData->getCoin();
	coin += UserDefault::getInstance()->getIntegerForKey("Coin");
	UserDefault::getInstance()->setIntegerForKey("Coin", coin);
	UserDefault::getInstance()->flush();

	if (score > UserDefault::getInstance()->getIntegerForKey("HighScore")/*JSON_MGR->getPlayerDataWithTag("PlayerHighScore")["Score"].asInt()*/)
	{
		//최고스코어 갱신
		UserDefault::getInstance()->setIntegerForKey("HighScore", score);
		UserDefault::getInstance()->flush();
	}

	Director::getInstance()->replaceScene(CTitleScene::createScene());
	Director::getInstance()->getTextureCache()->removeAllTextures();
	PlayerData->destroyInstance();
	ButtonData->destroyInstance();
}

void CGameOverScene::generaterTouch()
{
	auto listener = EventListenerTouchOneByOne::create();

	// 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미이다.
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CGameOverScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CGameOverScene::onTouchEnded, this);

	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool CGameOverScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	CCLOG("onTouchBegan");

	return true;
}

void CGameOverScene::onTouchEnded(Touch * touch, Event * unused_event)
{
	int score = PlayerData->getScore();
	//coin
	int coin = PlayerData->getCoin();
	coin += UserDefault::getInstance()->getIntegerForKey("Coin");
	UserDefault::getInstance()->setIntegerForKey("Coin", coin);
	UserDefault::getInstance()->flush();

	if (score > UserDefault::getInstance()->getIntegerForKey("HighScore"))
	{
		//최고스코어 갱신
		UserDefault::getInstance()->setIntegerForKey("HighScore", score);
		UserDefault::getInstance()->flush();
	}

	Director::getInstance()->replaceScene(CTitleScene::createScene());
	Director::getInstance()->getTextureCache()->removeAllTextures();
	PlayerData->destroyInstance();
	ButtonData->destroyInstance();
}