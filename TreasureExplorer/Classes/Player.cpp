#include "PCH.h"
#include "Player.h"
#include "PlayerData.h"
#include "JsonManager.h"


CPlayer::CPlayer()
{
	oldPlayerState = (PlayerState)-1;
	playerState = (PlayerState)-1;
	nowPlayerAni = nullptr;
	runNomal = nullptr;
	runKnife = nullptr;
	runFire = nullptr;
	runRope = nullptr;
	actionKnife = nullptr;
	actionFire = nullptr;
	actionRopeShot = nullptr;
	actionRopeUp = nullptr;
	actionRopeDown = nullptr;
	playerBody = nullptr;
	runFrameCount = 0;
	playerActionStart = false;
	baseColor = Color3B(0, 0, 0);
	attackedStartTime = 0.0f;
	isAttacked = false;
}

CPlayer::~CPlayer()
{

}

bool CPlayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	generaterPlayer();

	this->scheduleUpdate();
	return true;
}

void CPlayer::update(float dt)
{
	aniUpdate(dt);
	stateUpdate();
	attackedUpdate();
}

void CPlayer::aniUpdate(float dt)
{
	if (oldPlayerState != playerState)
	{
		if (playerState == Player_Run || playerState == Player_Run_Knife || playerState == Player_Run_Fire || playerState == Player_Run_Rope)
		{
			runFrameCount = nowPlayerAni->getCurFrame();
		}

		switch (playerState)
		{
		case Player_Run_Knife:	nowPlayerAni = runKnife;	nowPlayerAni->setCurFrame(runFrameCount);	playerBody->setTexture(nowPlayerAni->getAnimationFrame(runFrameCount)->getTexture()); break;
		case Player_Run_Fire:	nowPlayerAni = runFire;		nowPlayerAni->setCurFrame(runFrameCount);	playerBody->setTexture(nowPlayerAni->getAnimationFrame(runFrameCount)->getTexture()); break;
		case Player_Run_Rope:	nowPlayerAni = runRope;		nowPlayerAni->setCurFrame(runFrameCount);	playerBody->setTexture(nowPlayerAni->getAnimationFrame(runFrameCount)->getTexture()); break;
		case Player_Action_Knife:	nowPlayerAni = actionKnife;	break;
		case Player_Action_Fire:	nowPlayerAni = actionFire;	break;
		case Player_Action_Rope_Shot:	nowPlayerAni = actionRopeShot;	break;
		case Player_Action_Rope_Up:		nowPlayerAni = actionRopeUp;	break;
		case Player_Action_Rope_Down:	nowPlayerAni = actionRopeDown;	break;
		}
	}
	else
	{
		auto spr = nowPlayerAni->run(dt);

		if (spr == LOOPACTIVE)
			return;
		else if (spr == LOOPEND)
		{
			if (playerState == Player_Action_Knife)
			{
				playerState = Player_Run_Knife;
				actionKnife->setAniEnd(true);
				nowPlayerAni = runKnife;
				nowPlayerAni->setCurFrame(runFrameCount);
				playerBody->setTexture(nowPlayerAni->getAnimationFrame(runFrameCount)->getTexture());
			}
			else if (playerState == Player_Action_Fire)
			{
				playerState = Player_Run_Fire;
				actionFire->setAniEnd(true);
				nowPlayerAni = runFire;
				nowPlayerAni->setCurFrame(runFrameCount);
				playerBody->setTexture(nowPlayerAni->getAnimationFrame(runFrameCount)->getTexture());
			}
			else if (playerState == Player_Action_Rope_Shot)
			{
				playerState = Player_Action_Rope_Up;
				actionRopeShot->setAniEnd(true);
				nowPlayerAni = actionRopeUp;
				playerBody->setTexture(nowPlayerAni->getAnimationFrame(0)->getTexture());
			}
			else if (playerState == Player_Action_Rope_Down)
			{
				playerState = Player_Run_Rope;
				actionRopeDown->setAniEnd(true);
				nowPlayerAni = runRope;
				nowPlayerAni->setCurFrame(runFrameCount);
				playerBody->setTexture(nowPlayerAni->getAnimationFrame(runFrameCount)->getTexture());
			}
		}
		else
			playerBody->setTexture(spr->getTexture());
	}
}

void CPlayer::stateUpdate()
{
	PlayerData->setPlayerState(playerState);
	oldPlayerState = playerState;
}

void CPlayer::attackedUpdate()
{
	if (isAttacked)
	{
		attackedStartTime += Director::getInstance()->getDeltaTime();
		if (attackedStartTime >= ATTACKEDENDTIME)
		{
			isAttacked = false;
			attackedStartTime = 0.0f;
			playerBody->setColor(baseColor);
		}
	}
}

void CPlayer::generaterPlayer()
{
	playerBody = Sprite::create(JSON_MGR->getFilePathRootWithTag("UnitBase")["Player"].asString());
	playerBody->setScale(0.3f);
	this->addChild(playerBody);

	runNomal = createAnimation("run_nomal");
	runKnife = createAnimation("run_knife");
	runFire = createAnimation("run_fire");
	runRope = createAnimation("run_rope");
	actionKnife = createAnimation("knife_action");
	actionFire = createAnimation("fire_action");
	actionRopeShot = createAnimation("rope_action_shot");
	actionRopeUp = createAnimation("rope_action_up");
	actionRopeDown = createAnimation("rope_action_down");
	nowPlayerAni = runNomal;
	baseColor = playerBody->getColor();
}

CAnimation* CPlayer::createAnimation(std::string jsonName)
{
	std::string AniBasepath;
	AniBasepath.append("Unit/Player/");

	auto ani = CAnimation::create(JSON_MGR->getFilePathRootWithTag("PlayerAni")[jsonName]["AniRate"].asFloat(), JSON_MGR->getFilePathRootWithTag("PlayerAni")[jsonName]["AniLoop"].asBool());

	for (int i = 0; i < JSON_MGR->getFilePathRootWithTag("PlayerAni")[jsonName]["AniCount"].asInt(); i++)
	{
		std::string aniPath;
		aniPath.append(AniBasepath);
		aniPath.append(JSON_MGR->getFilePathRootWithTag("PlayerAni")[jsonName]["AniName"].asString() + "/");
		aniPath.append(StringUtils::toString(i) + ".png");
		ani->addFrame(aniPath);
	}
	
	return ani;
}

void CPlayer::setNowAnimation(PlayerState _state, int _curFrame)
{
	playerState = _state;
	switch (playerState)
	{
	case Player_Run:
		nowPlayerAni = runNomal;
		break;
	case Player_Run_Knife:
		nowPlayerAni = runKnife;
		break;
	case Player_Run_Fire:
		nowPlayerAni = runFire;
		break;
	case Player_Run_Rope:
		nowPlayerAni = runRope;
		break;
	default:
		break;
	}
	nowPlayerAni->setCurFrame(_curFrame);
}
