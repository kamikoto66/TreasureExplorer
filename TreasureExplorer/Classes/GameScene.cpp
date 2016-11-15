#include "PCH.h"
#include "GameScene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"


CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
}

Scene* CGameScene::createStage1()
{
	auto scene = Scene::create();
	auto layer = CStage1::create();
	scene->addChild(layer, 0, "Stage");
	return scene;
}

Scene* CGameScene::createStage2()
{
	auto scene = Scene::create();
	auto layer = CStage2::create();
	scene->addChild(layer, 0, "Stage");
	return scene;
}

Scene* CGameScene::createStage3()
{
	auto scene = Scene::create();
	auto layer = CStage3::create();
	scene->addChild(layer, 0, "Stage");
	return scene;
}