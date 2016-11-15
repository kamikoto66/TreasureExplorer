#include "PCH.h"
#include "LineBar.h"
#include "enumData.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "GameScene.h"
#include "JsonManager.h"
#include "Button.h"
#include "ButtonData.h"
#include "Player.h"
#include "PlayerData.h"

CLineBar::CLineBar() :
lineBarIndex((LineBarIndex)-1),
lineBarState((LineBarState)-1),
lineBarStartImage(nullptr),
lineBarEndImage(nullptr),
lineBarImage(nullptr),
playerImage(nullptr),
startPos(0, 0),
endPos(0, 0),
moveLength(0),
movePersent(0),
isSceneChange(false),
finishLength(0)
{
}


CLineBar::~CLineBar()
{
}

bool CLineBar::init(LineBarIndex _index)
{
	if (!Node::init())
	{
		return false;
	}

	lineBarIndex = _index;
	generaterLineBar();

	scheduleUpdate();

	return true;
}

void CLineBar::update(float dt)
{
	moveLength += 2.5f;
	Vec2 pos = playerImage->getPosition();

	float persent = 0;
	persent = (moveLength / finishLength) * 100;

	float addPosX = (LINEBARIMAGE_WIDTH*0.7f / 100) * persent;
	pos.x = lineBarImage->getPositionX() + addPosX;

	//마지막 위치까지 왔으면
	if (pos.x >= endPos.x &&isSceneChange == false)
	{
		//데이터 받아옴
		PlayerState playerState = PlayerData->getPlayerState();
		int playerNowAniCount = PlayerData->getPlayer()->getNowAnimation()->getCurFrame();
		ButtonState buttonState = ButtonData->getButtonState();
		
		if (playerState == Player_Action_Rope_Down || playerState == Player_Action_Rope_Shot || playerState == Player_Action_Rope_Up)
		{
			playerState = Player_Run_Rope;
		}

		if (lineBarIndex == Line_Forest)
		{
			//화면 전환 효과 오른쪽에서 왼쪽으로
			auto scene = TransitionFade::create(1.0f, CGameScene::createStage2());
			Director::getInstance()->replaceScene(scene);
		}
		else if (lineBarIndex == Line_Ruins)
		{
			//화면 전환 효과 오른쪽에서 왼쪽으로
			auto scene = TransitionFade::create(1.0f, CGameScene::createStage3());
			Director::getInstance()->replaceScene(scene);
		}
		else if (lineBarIndex == Line_Site)
		{
			//화면 전환 효과 오른쪽에서 왼쪽으로
			auto scene = TransitionFade::create(1.0f, CGameScene::createStage1());
			Director::getInstance()->replaceScene(scene);
		}

		//데이터 적용
		PlayerData->getPlayer()->setNowAnimation(playerState, playerNowAniCount);
		PlayerData->getPlayer()->getPlayerBody()->setTexture(PlayerData->getPlayer()->getNowAnimation()->getAnimationFrame(playerNowAniCount)->getTexture());
		ButtonData->getButton()->setButtonState(buttonState);
		int stageCount = PlayerData->getStageCount();
		stageCount++;
		PlayerData->setStageCount(stageCount);

		isSceneChange = true;
	}
	//아니면
	else
	{
		playerImage->setPosition(pos);
	}
}

void CLineBar::generaterLineBar()
{
	if (lineBarIndex == Line_Forest)
	{
		lineBarStartImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Forest_Right"].asString());
		lineBarEndImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Ruins_Left"].asString());
		lineBarImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Forest_Ruins"].asString());
		playerImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Minji"].asString());
	}
	else if (lineBarIndex == Line_Ruins)
	{
		lineBarStartImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Ruins_Right"].asString());
		lineBarEndImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Site_Left"].asString());
		lineBarImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Ruins_Site"].asString());
		playerImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Minji"].asString());
	}
	else if (lineBarIndex == Line_Site)
	{
		lineBarStartImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Site_Right"].asString());
		lineBarEndImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Forest_Left"].asString());
		lineBarImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Site_Forest"].asString());
		playerImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("LineBarImage")["Minji"].asString());
	}

	lineBarStartImage->setScale(0.7f);
	lineBarEndImage->setScale(0.7f);
	lineBarImage->setScale(0.7f);
	playerImage->setScale(0.7f);

	//라인바 이미지
	Vec2 lineBarImagePos;
	lineBarImagePos.x = 10;
	lineBarImagePos.y = winSize.height - 60;
	lineBarImage->setAnchorPoint(Vec2(0, 0));
	lineBarImage->setPosition(lineBarImagePos);

	//라인바 시작점 이미지
	Vec2 lineBarStartImagePos;
	lineBarStartImagePos.x = lineBarImage->getPositionX() + ((lineBarStartImage->getTextureRect().size.width * 0.7f) / 3);
	lineBarStartImagePos.y = (lineBarImage->getPositionY() + ((lineBarImage->getTextureRect().size.height*0.7f) / 3));
	lineBarStartImage->setAnchorPoint(Vec2(0.5, 0.5));
	lineBarStartImage->setPosition(lineBarStartImagePos);

	//라인바 도착점 이미지
	Vec2 lineBarEndImagePos;
	lineBarEndImage->setAnchorPoint(Vec2(0.5, 0.5));
	lineBarEndImagePos.x = (lineBarImage->getTextureRect().size.width*0.7f) - lineBarImage->getPositionX();
	lineBarEndImagePos.y = (lineBarImage->getPositionY() + ((lineBarImage->getTextureRect().size.height * 0.7f) / 3));
	lineBarEndImage->setPosition(lineBarEndImagePos);

	//민지 이미지
	Vec2 playerImagePos;
	playerImagePos.x = lineBarStartImage->getPositionX();
	playerImagePos.y = lineBarStartImage->getPositionY()+25;
	playerImage->setAnchorPoint(Vec2(0.5, 0.5));
	playerImage->setPosition(playerImagePos);

	this->addChild(lineBarStartImage, 1);
	this->addChild(lineBarEndImage, 1);
	this->addChild(lineBarImage, 0);
	this->addChild(playerImage, 2);

	startPos = lineBarStartImage->getPosition();
	endPos = lineBarEndImage->getPosition();

	finishLength = 4000 + 200 * PlayerData->getStageCount();

	if (finishLength >= MAX_MOVE_LENGTH)
		finishLength = MAX_MOVE_LENGTH;
}