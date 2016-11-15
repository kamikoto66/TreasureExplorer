#include "PCH.h"
#include "TutorialScene.h"
#include "JsonManager.h"
#include "TitleScene.h"
#include "soundManager.h"

CTutorialScene::CTutorialScene()
{
	curImageCount = 0;
	howToPlayCurImage = nullptr;
}


CTutorialScene::~CTutorialScene()
{
}

bool CTutorialScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	generaterHowToPlay();
	generaterTouch();

	return true;
}

void CTutorialScene::generaterHowToPlay()
{
	howToPlayCurImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("HowToPlay")["Image_0"].asString());
	howToPlayCurImage->setScale(0.5f);
	howToPlayCurImage->setAnchorPoint(Vec2(0.5, 0.5));
	howToPlayCurImage->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(howToPlayCurImage, 1);

	for (Json::Value& pRet : JSON_MGR->getFilePathRootWithTag("HowToPlay"))
	{
		auto spr = Sprite::create(pRet.asString());
		spr->setScale(0.5f);
		spr->retain();
		howToPlayImageVector.push_back(spr);
	}
}

void CTutorialScene::generaterTouch()
{
	auto listener = EventListenerTouchOneByOne::create();

	// 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미이다.
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CTutorialScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CTutorialScene::onTouchEnded, this);

	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool CTutorialScene::onTouchBegan(Touch * touch, Event * unused_event)
{

	return true;
}

void CTutorialScene::onTouchEnded(Touch * touch, Event * unused_event)
{
	curImageCount++;

	if (curImageCount >= MAX_IMAGE_COUNT)
	{
		CSoundManager::getInstance()->playBgm("sound/main.mp3");
		Director::getInstance()->replaceScene(CTitleScene::createScene());
	}
	else
	{
		howToPlayCurImage->setTexture(howToPlayImageVector[curImageCount]->getTexture());
	}
}

Scene* CTutorialScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CTutorialScene::create();
	scene->addChild(layer);
	return scene;
}