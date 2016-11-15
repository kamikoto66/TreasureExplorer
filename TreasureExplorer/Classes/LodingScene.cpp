#include "PCH.h"
#include "LodingScene.h"
#include "StartScene.h"
#include "json.h"
#include "JsonManager.h"
#include "GameScene.h"
#include "Stage1.h"
#include "Rand.h"

CLodingScene::CLodingScene()
{
	_numberOfLoadedSprites = 0;
	_numberOfSprites = 0;
	_labelPercent = nullptr;
	_labelLoading = nullptr;
}


CLodingScene::~CLodingScene()
{
}

bool CLodingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//이미지 최대 사이즈
	_numberOfSprites = JSON_MGR->getFilePathRootWithTag("FileNumber")["Number"].asInt();
	//_numberOfSprites = 999;

	generaterLabelAndBackGround();
	generaterBackGround();
	generaterButton();
	generaterUnitBase();
	gneraterUnitAnimation();
	gneraterLineBar();
	gneraterEffect();
	gneraterTreasure();
	gneraterHelpImage();
	gneraterTreasureRoomStateNameImage();
	gneraterPauseStartDelay();
	gneraterHpImage();
	gneraterCoin();

	return true;
}

void CLodingScene::generaterLabelAndBackGround()
{
	std::string backGroundPath = "background/";
	backGroundPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["LodingAndStart"]["StageName"].asString()+"/");
	backGroundPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["LodingAndStart"]["FileName"].asString());

	auto spr = Sprite::create(backGroundPath);
	spr->setAnchorPoint(Vec2(0.5, 0.5));
	spr->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(spr);

	//로딩중 라벨 출력 
	auto size = Director::getInstance()->getWinSize();
	_labelLoading = Label::createWithTTF("LOADING...", "fonts/MoebiusBold.ttf", 50);
	_labelLoading->setColor(Color3B(255, 255, 255));
	_labelPercent = Label::createWithTTF("%0", "fonts/MoebiusBold.ttf", 50);
	_labelPercent->setColor(Color3B(255, 255, 255));
	_labelLoading->setPosition(Vec2(winSize.width / 1.3f, winSize.height / 5));
	_labelPercent->setPosition(Vec2(winSize.width / 1.3f, winSize.height / 5-50));
	this->addChild(_labelLoading, 2);
	this->addChild(_labelPercent, 2);
}

//배경 생성
void CLodingScene::generaterBackGround()
{
	//4장
	for (Json::Value backGroundPath : CJsonManager::getInstance()->getFilePathRootWithTag("BackGround"))
	{
		std::string Path;
		Path.append("background/");
		Path.append(backGroundPath["StageName"].asString() + "/");
		Path.append(backGroundPath["FileName"].asString());
		Director::getInstance()->getTextureCache()->addImageAsync(Path.c_str(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}
//버튼 생성
void CLodingScene::generaterButton()
{
	//18장
	for (Json::Value buttonPath : CJsonManager::getInstance()->getFilePathRootWithTag("Button"))
	{
		Director::getInstance()->getTextureCache()->addImageAsync(buttonPath.asString(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}
//유닛 베이스 생성
void CLodingScene::generaterUnitBase()
{
	//7장
	for (Json::Value unitBasePath : CJsonManager::getInstance()->getFilePathRootWithTag("UnitBase"))
	{
		Director::getInstance()->getTextureCache()->addImageAsync(unitBasePath.asString(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}
//유닛 애니매이션 생성
void CLodingScene::gneraterUnitAnimation()
{
	for (Json::Value UnitAni : CJsonManager::getInstance()->getFilePathRootWithTag("UnitDieAni"))
	{
		std::string UnitName = UnitAni["UnitName"].asString();
		std::string AniName = UnitAni["AniName"].asString();
		int FrameCount = UnitAni["AniCount"].asInt();
		loadFrameImage(UnitName, AniName, FrameCount);
	}

	for (Json::Value PlayerAni : CJsonManager::getInstance()->getFilePathRootWithTag("PlayerAni"))
	{
		std::string UnitName = PlayerAni["UnitName"].asString();
		std::string AniName = PlayerAni["AniName"].asString();
		int FrameCount = PlayerAni["AniCount"].asInt();
		loadFrameImage(UnitName, AniName, FrameCount);
	}
}

void CLodingScene::gneraterLineBar()
{
	for (Json::Value LineBarImage : CJsonManager::getInstance()->getFilePathRootWithTag("LineBarImage"))
	{
		std::string Path(LineBarImage.asString());
		Director::getInstance()->getTextureCache()->addImageAsync(Path, CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}

void CLodingScene::gneraterEffect()
{
	for (Json::Value& pRet : CJsonManager::getInstance()->getFilePathRootWithTag("PlayerAni"))
	{
		std::string UnitName = pRet["UnitName"].asString();
		std::string AniName = pRet["AniName"].asString();
		int FrameCount = pRet["AniCount"].asInt();
		loadFrameImage(UnitName, AniName, FrameCount);
	}
}

void CLodingScene::gneraterTreasure()
{
	for (Json::Value& pRet : CJsonManager::getInstance()->getFilePathRootWithTag("Treasure"))
	{
		std::string path = pRet["FileName"].asString();
		Director::getInstance()->getTextureCache()->addImageAsync(path, CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}

void CLodingScene::gneraterHelpImage()
{
	for (Json::Value& pRet : CJsonManager::getInstance()->getFilePathRootWithTag("HelpImage"))
	{
		Director::getInstance()->getTextureCache()->addImageAsync(pRet.asString(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}

void CLodingScene::gneraterTreasureRoomStateNameImage()
{
	for (Json::Value& pRet : CJsonManager::getInstance()->getFilePathRootWithTag("TreasureRoomStateNameImage"))
	{
		Director::getInstance()->getTextureCache()->addImageAsync(pRet.asString(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}

void CLodingScene::gneraterPauseStartDelay()
{
	for (Json::Value& pRet : CJsonManager::getInstance()->getFilePathRootWithTag("PauseStartDelay"))
	{
		Director::getInstance()->getTextureCache()->addImageAsync(pRet.asString(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}

void CLodingScene::gneraterHpImage()
{
	for (Json::Value& pRet : CJsonManager::getInstance()->getFilePathRootWithTag("HpImage"))
	{
		Director::getInstance()->getTextureCache()->addImageAsync(pRet.asString(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}

void CLodingScene::gneraterCoin()
{
	for (Json::Value& pRet : CJsonManager::getInstance()->getFilePathRootWithTag("Coin"))
	{
		Director::getInstance()->getTextureCache()->addImageAsync(pRet.asString(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}

void CLodingScene::loadingCallBack(cocos2d::Texture2D *texture)
{
	++_numberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp, "%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_labelPercent->setString(tmp);

	//CCLOG("%d",_numberOfLoadedSprites);
	if (_numberOfLoadedSprites == _numberOfSprites)
	{
		CWellRandom::getInstance()->init();
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->replaceScene(CGameScene::createStage1());
	}
}

void CLodingScene::loadFrameImage(std::string charName, std::string aniName, int Frame)
{
	//기본 경로
	std::string path;
	path.append("Unit/" + charName + "/" + aniName + "/");


	//프레임수만큼 이미지 로딩
	for (int frameCount = 0; frameCount < Frame; frameCount++)
	{
		std::string AniFilePath;
		AniFilePath.append(path + StringUtils::toString(frameCount) + ".png");
		Director::getInstance()->getTextureCache()->addImageAsync(AniFilePath.c_str(), CC_CALLBACK_1(CLodingScene::loadingCallBack, this));
	}
}

Scene* CLodingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CLodingScene::create();

	scene->addChild(layer);
	
	return scene;
}