#include "PCH.h"
#include "StartScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "soundManager.h"
#include "JsonManager.h"

USING_NS_CC;

StartScene::StartScene()
{
	isFirstStart = true;
	touchToScreenLabel = nullptr;
	backImage = nullptr;
	logoImage = nullptr;
}


StartScene::~StartScene()
{
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (UserDefault::getInstance()->getBoolForKey("FirstStart") == false)
	{
		UserDefault::getInstance()->setBoolForKey("FirstStart", true);
		UserDefault::getInstance()->setBoolForKey("Sound", true);
		UserDefault::getInstance()->setBoolForKey("Help", true);
		//UserDefault::getInstance()->setIntegerForKey("RunisAccessory", -2);
		//UserDefault::getInstance()->setIntegerForKey("SiteAccessory", -2);
		//UserDefault::getInstance()->setIntegerForKey("ForestAccessory", -2);
		//UserDefault::getInstance()->setIntegerForKey("RunisCap", -2);
		//UserDefault::getInstance()->setIntegerForKey("SiteCap", -2);
		//UserDefault::getInstance()->setIntegerForKey("ForestCap", -2);
		//UserDefault::getInstance()->setIntegerForKey("RunisWear", -2);
		//UserDefault::getInstance()->setIntegerForKey("SiteWear", -2);
		//UserDefault::getInstance()->setIntegerForKey("ForestWear", -2);
		//UserDefault::getInstance()->setBoolForKey("RunisAccessoryBool", false);
		//UserDefault::getInstance()->setBoolForKey("SiteAccessoryBool", false);
		//UserDefault::getInstance()->setBoolForKey("ForestAccessoryBool", false);
		//UserDefault::getInstance()->setBoolForKey("RunisCapBool", false);
		//UserDefault::getInstance()->setBoolForKey("SiteCapBool", false);
		//UserDefault::getInstance()->setBoolForKey("ForestCapBool", false);
		//UserDefault::getInstance()->setBoolForKey("RunisWearBool", false);
		//UserDefault::getInstance()->setBoolForKey("SiteWearBool", false);
		//UserDefault::getInstance()->setBoolForKey("ForestWearBool", false);
	}

	CSoundManager::getInstance()->setBgmOn(UserDefault::getInstance()->getBoolForKey("Sound"));
	CSoundManager::getInstance()->playBgm("sound/main.mp3");

	generaterTouch();
	generaterLabel();
	generaterBackGround();

	return true;
}

void StartScene::generaterLabel()
{
	touchToScreenLabel = Label::createWithTTF("TAP TO START", "fonts/MoebiusBold.ttf", 40, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	touchToScreenLabel->setPosition(Point(winSize.width / 1.2, winSize.height / 10));
	this->addChild(touchToScreenLabel, 2);

	touchToScreenLabel->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.75f), FadeOut::create(0.75f), NULL)));
}

void StartScene::generaterTouch()
{
	auto listener = EventListenerTouchOneByOne::create();

	// 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미이다.
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded, this);

	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void StartScene::generaterBackGround()
{
	std::string backGroundPath = "background/";
	backGroundPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["LodingAndStart"]["StageName"].asString() + "/");
	backGroundPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["LodingAndStart"]["FileName"].asString());

	auto backImage = Sprite::create(backGroundPath);
	backImage->setAnchorPoint(Vec2(0.5, 0.5));
	backImage->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(backImage, TAG_STARTSCENE_BACKIMAGE);

	std::string logoPath;
	logoPath.append("background/");
	logoPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["StartSceneLogo"]["StageName"].asString() + "/");
	logoPath.append(JSON_MGR->getFilePathRootWithTag("BackGround")["StartSceneLogo"]["FileName"].asString());
	logoImage = Sprite::create(logoPath);
	logoImage->setAnchorPoint(Vec2(0.5f, 0.5f));
	logoImage->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(logoImage, TAG_LOGOIMAGE);
}

Scene * StartScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StartScene::create();

	scene->addChild(layer);

	return scene;
}

bool StartScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	CCLOG("onTouchBegan");

	return true;
}

void StartScene::onTouchEnded(Touch * touch, Event * unused_event)
{
	Scene* scene = TransitionFade::create(1.0, CTitleScene::createScene());
	Director::getInstance()->replaceScene(scene);
	//CSoundManager::getInstance()->stopBgm("sound/001-Title.mp3");

	CCLOG("onTouchEnded");
}