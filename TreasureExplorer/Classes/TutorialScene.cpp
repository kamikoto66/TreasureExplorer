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

	// �ڵ鸵�� ��ġ �̺�Ʈ�� ��ġ �̺�Ʈ array���� ����ڴٴ� �ǹ��̴�.
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CTutorialScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CTutorialScene::onTouchEnded, this);

	// ��ġ�������� �켱������ (��尡) ȭ�鿡 �׷��� ������� �Ѵ�.
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