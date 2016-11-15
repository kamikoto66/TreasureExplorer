#include "PCH.h"
#include "TreasureRoomScene.h"
#include "Treasure.h"
#include "JsonManager.h"
#include "TreasureUpgrade.h"
#include "soundManager.h"

CTreasureRoomScene::CTreasureRoomScene()
{
	for (int i = 0; i < 9; i++)
	{
		treasureRoomImage[i] = nullptr;
	}
}


CTreasureRoomScene::~CTreasureRoomScene()
{
}

bool CTreasureRoomScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	generaterBackImage();
	generaterTreasure();
	generaterUi();

	return true;
}

Scene* CTreasureRoomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CTreasureRoomScene::create();
	scene->addChild(layer, 0,"CTreasureRoomScene");
	return scene;
}

void CTreasureRoomScene::generaterTreasure()
{
	if (UserDefault::getInstance()->getBoolForKey("RunisAccessoryBool"))
	{
		treasureRoomImage[0] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("RunisAccessory"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[0]->setXMLTag("RunisAccessory");
		treasureRoomImage[0]->setTreasureName("Accessory");
		this->addChild(treasureRoomImage[0], 2);
	}

	if (UserDefault::getInstance()->getBoolForKey("SiteAccessoryBool"))
	{
		treasureRoomImage[1] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("SiteAccessory"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[1]->setXMLTag("SiteAccessory");
		treasureRoomImage[1]->setTreasureName("Accessory");
		this->addChild(treasureRoomImage[1], 2);
	}

	if (UserDefault::getInstance()->getBoolForKey("ForestAccessoryBool"))
	{
		treasureRoomImage[2] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("ForestAccessory"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[2]->setXMLTag("ForestAccessory");
		treasureRoomImage[2]->setTreasureName("Accessory");
		this->addChild(treasureRoomImage[2], 2);
	}

	if (UserDefault::getInstance()->getBoolForKey("RunisCapBool"))
	{
		treasureRoomImage[3] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("RunisCap"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[3]->setXMLTag("RunisCap");
		treasureRoomImage[3]->setTreasureName("Cap");
		this->addChild(treasureRoomImage[3], 2);
	}

	if (UserDefault::getInstance()->getBoolForKey("SiteCapBool"))
	{
		treasureRoomImage[4] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("SiteCap"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[4]->setXMLTag("SiteCap");
		treasureRoomImage[4]->setTreasureName("Cap");
		this->addChild(treasureRoomImage[4], 2);
	}

	if (UserDefault::getInstance()->getBoolForKey("ForestCapBool"))
	{
		treasureRoomImage[5] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("ForestCap"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[5]->setXMLTag("ForestCap");
		treasureRoomImage[5]->setTreasureName("Cap");
		this->addChild(treasureRoomImage[5], 2);
	}

	if (UserDefault::getInstance()->getBoolForKey("RunisWearBool"))
	{
		treasureRoomImage[6] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("RunisWear"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[6]->setXMLTag("RunisWear");
		treasureRoomImage[6]->setTreasureName("Wear");
		this->addChild(treasureRoomImage[6], 2);
	}

	if (UserDefault::getInstance()->getBoolForKey("SiteWearBool"))
	{
		treasureRoomImage[7] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("SiteWear"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[7]->setXMLTag("SiteWear");
		treasureRoomImage[7]->setTreasureName("Wear");
		this->addChild(treasureRoomImage[7], 2);
	}

	if (UserDefault::getInstance()->getBoolForKey("ForestWearBool"))
	{
		treasureRoomImage[8] = CTreasure::create((TreasureIndex)UserDefault::getInstance()->getIntegerForKey("ForestWear"), CC_CALLBACK_1(CTreasureRoomScene::enterTreasure, this));
		treasureRoomImage[8]->setXMLTag("ForestWear");
		treasureRoomImage[8]->setTreasureName("Wear");
		this->addChild(treasureRoomImage[8], 2);
	}
}

void CTreasureRoomScene::generaterBackImage()
{
	std::string backImagePath;
	backImagePath.append("background/");
	backImagePath.append(JSON_MGR->getFilePathRootWithTag("TreasureManagerScene")["StageName"].asString() + "/");
	backImagePath.append(JSON_MGR->getFilePathRootWithTag("TreasureManagerScene")["FileName"].asString());

	treasureRoomBackImage = Sprite::create("background/TreasureManagerScene/backGround.png");
	treasureRoomBackImage->setAnchorPoint(Vec2(0.5, 0.5));
	treasureRoomBackImage->setPosition(Vec2(winSize.width/2, winSize.height/2));
	this->addChild(treasureRoomBackImage, TAG_BACKIMAGE);
}

void CTreasureRoomScene::generaterUi()
{
	auto exitButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["Upgrade_back_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["Upgrade_back_1"].asString(), CC_CALLBACK_1(CTreasureRoomScene::enterExit, this));
	exitButton->setPosition(winSize.width - 50, winSize.height - 50);
	exitButton->setTag(TAG_EXIT);

	backMenu = Menu::create(exitButton, NULL);
	backMenu->setPosition(Vec2(0, 0));
	this->addChild(backMenu, TAG_UI);
}

void CTreasureRoomScene::enterExit(Ref* sender)
{
	auto button = (MenuItem*)sender;

	if(button->getTag() == TAG_EXIT)
	{
		CSoundManager::getInstance()->playEffect("sound/button_1.mp3");
		Director::getInstance()->replaceScene(CTitleScene::createScene());
	}
}

void CTreasureRoomScene::enterTreasure(CTreasure* treasure)
{

		treasurePause();
		std::string xmlTag = treasure->getXMLTag();
		std::string treasureName = treasure->getTreasureName();
		TreasureIndex index = treasure->getTreasureIndex();
		TreasureType type = treasure->getTreasureType();

		auto test = CTreasureUpgrade::create(index, type, xmlTag, treasureName);
		test->setPosition(Vec2(0, -500));
		this->addChild(test, 99);
		test->runAction(MoveBy::create(0.3f, Vec2(0, 500)));
	
}

void CTreasureRoomScene::treasurePause()
{
	for (int i = 0; i < 9; i++)
	{
		if (treasureRoomImage[i] != nullptr)
			treasureRoomImage[i]->pause();
	}
}

void CTreasureRoomScene::treasureResume()
{
	for (int i = 0; i < 9; i++)
	{
		if (treasureRoomImage[i] != nullptr)
		{
			this->removeChild(treasureRoomImage[i], true);
			treasureRoomImage[i] = nullptr;
		}
	}
	generaterTreasure();
}