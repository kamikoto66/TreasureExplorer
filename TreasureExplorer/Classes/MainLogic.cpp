#include "PCH.h"
#include "MainLogic.h"
#include "BackGround.h"
#include "Bottom.h"
#include "PlayerData.h"
#include "Player.h"
#include "Box.h"
#include "Coin.h"
#include "HpBar.h"
#include "Enemy.h"
#include "Button.h"
#include "ButtonData.h"
#include "ActionEffect.h"
#include "CollisionManager.h"
#include "GameOverScene.h"
#include "LineBar.h"
#include "soundManager.h"
#include "EnemyHelpImage.h"
#include "enumData.h"

CMainLogic::CMainLogic()
{
	isPause = false;
	isGameOver = false;
	score = 0;
	player = nullptr;
	button = nullptr;
	backGround = nullptr;
	bottom = nullptr;
	//enemy
	isEnemySponDelayTime = false;
	enemySponDelayTime = 0.0f;
	enemySponDelayTimeRate = 4.0f;
	//coin
	coin = 0;
	isCoinSponDelay = false;
	coinSponDelayTime = 0.0f;
	hpBar = nullptr;
	coinImage = nullptr;
	coinLabel = nullptr;
	lineBar = nullptr;
	isTutorial = false;
}


CMainLogic::~CMainLogic()
{
}

bool CMainLogic::init(StageIndex _index)
{
	if (!Layer::init())
	{
		return false;
	}

	stageIndex = _index;
	score = PlayerData->getScore();
	coin = PlayerData->getCoin();
	generaterScoreLabel();
	generaterBackGround();
	generaterBottom();
	generaterPlayer();
	generaterButton();
	generaterHpBar();
	generaterCoin();
	generaterLineBar();
	generaterSound();

	return true;
}

void CMainLogic::update()
{
	scoreUpdate();
	coinUpdate();
	actionEffectUpdate();
	enemyUpdate();
	playerUpdate();
}

void CMainLogic::playerUpdate()
{
	if (hpBar->getHpCount() <= 0 && isGameOver != true)
	{
		CSoundManager::getInstance()->stopAllBgms();
		CSoundManager::getInstance()->stopAllEffects();
		gameOverSceneChange();
		isGameOver = true;
	}

	if (player->getPlayerState() == Player_Action_Rope_Up || player->getPlayerState() == Player_Action_Rope_Down)
		return;

	if (player->getPlayerState() == Player_Action_Knife && player->getPlayerActionStart() == true && player->getNowAnimation()->getCurFrame() == 1)
	{
		Vec2 effectPos;
		effectPos.x = player->getPosition().x + 150;
		effectPos.y = player->getPosition().y - 25;
		makeEffect(Effect_Knife, effectPos); 
		player->setPlayerActionStart(false);
	}
	else if (player->getPlayerState() == Player_Action_Fire && player->getPlayerActionStart() == true && player->getNowAnimation()->getCurFrame() == 1)
	{
		Vec2 effectPos;
		effectPos.x = player->getPosition().x + 100;
		effectPos.y = player->getPosition().y - 50;
		makeEffect(Effect_Fire, effectPos);
		player->setPlayerActionStart(false);
	}
	else if (player->getPlayerState() == Player_Action_Rope_Shot && player->getPlayerActionStart() == true && player->getNowAnimation()->getCurFrame() == 1)
	{
		Vec2 effectPos;
		effectPos.x = player->getPosition().x+5;
		effectPos.y = player->getPosition().y+10;
		makeEffect(Effect_Rope, effectPos);
		player->setPlayerActionStart(false);
	}
}

void CMainLogic::enemyUpdate()
{
	for (auto Enemy : enemyVector)
	{
		if (Enemy->getPositionX() < -200)
		{
			Enemy->setEnemyState(Enemy_Null);
		}

		if (!actionEffectVector.empty())
		{
			for (CActionEffect* ActionEffect : actionEffectVector)
			{
				if (ActionEffect->getTergetEnemyType() != Type_Rope && Enemy->getDie() == false)
				{
					//충돌 한다면
					if (Collision_MGR->CircleCheck(Enemy->getPosition(), ActionEffect->getPosition(), 110))
					{
						//이펙트와 에너미 타입을 확인
						if (ActionEffect->getTergetEnemyType() == Enemy->getEnemyType())
						{
							//점수를 준다
							int score = PlayerData->getScore();
							score += 50;
							PlayerData->setScore(score);
							Enemy->setEnemyState(Enemy_Die);
							Enemy->setsDie(true);
							ActionEffect->setEffectState(Effect_Off);
						}
					}
				}
			}
		}

		if (Enemy->getPosition().x <= player->getPosition().x + 200)
		{
			//로프
			if (Enemy->getEnemyType() == Type_Rope)
			{
				if (Collision_MGR->LIneToDot(Enemy->getPosition(), player->getPositionX()) && player->getPlayerState() != Player_Action_Rope_Up)
				{
					player->setAttackedStartTime(Director::getInstance()->getDeltaTime());
					player->setIsAttacked(true);
					player->getPlayerBody()->setColor(Color3B(255, 0, 0));
					hpBar->attackedPlayer();
				}
			}
			//다른것들
			else
			{
				if (Collision_MGR->CircleCheck(player->getPosition(), Enemy->getPosition(), 100) && player->getIsAttacked() == false && Enemy->getDie() == false)
				{
					player->setAttackedStartTime(Director::getInstance()->getDeltaTime());
					player->setIsAttacked(true);
					player->getPlayerBody()->setColor(Color3B(255, 0, 0));
					hpBar->attackedPlayer();
				}
			}
		}

		if (Enemy->getEnemyState() == Enemy_Null)
		{
			this->removeChild(Enemy);
			enemyVector.eraseObject(Enemy);
			continue;
		}
	}
}

void CMainLogic::actionEffectUpdate()
{
	for (CActionEffect* actionEffect : actionEffectVector)
	{
		if (actionEffect->getEffectState() == Effect_Off)
		{
			this->removeChild(actionEffect);
			actionEffectVector.eraseObject(actionEffect);
			continue;
		}
	}
}

void CMainLogic::scoreUpdate()
{
	score += 1;
	PlayerData->setScore(score);
	std::string scoreStr;
	scoreStr.append("Score:");
	scoreStr.append(StringUtils::toString(score));
	scoreLabel->setString(scoreStr);
}

void CMainLogic::coinUpdate()
{
	coin = PlayerData->getCoin();
	coinLabel->setString(std::string("x " + StringUtils::toString(coin)));
}

//사운드 생성
void CMainLogic::generaterSound()
{
	if (stageIndex == Stage_Forest)
	{
		CSoundManager::getInstance()->stopBgm("sound/temple.mp3");
		CSoundManager::getInstance()->playBgm("sound/Forest.mp3");
	}
	else if (stageIndex == Stage_Ruins)
	{
		CSoundManager::getInstance()->stopBgm("sound/Forest.mp3");
		CSoundManager::getInstance()->playBgm("sound/cave.mp3");
	}
	else if (stageIndex == Stage_Site)
	{
		CSoundManager::getInstance()->stopBgm("sound/cave.mp3");
		CSoundManager::getInstance()->playBgm("sound/temple.mp3");
	}
}
//스코어 라벨 생성
void CMainLogic::generaterScoreLabel()
{
	scoreLabel = Label::createWithTTF("Scroe:0", "fonts/MoebiusBold.ttf", 30);
	scoreLabel->setAnchorPoint(Vec2(0, 0));
	scoreLabel->setColor(Color3B(0, 0, 0));
	scoreLabel->setPosition(winSize.width - 450, winSize.height - 70);
	this->addChild(scoreLabel, 10);
}
//라인바 생성
void CMainLogic::generaterLineBar()
{
	if (stageIndex == StageIndex::Stage_Forest)
	{
		lineBar = CLineBar::create(Line_Forest);
		this->addChild(lineBar, TAG_LINEBAR);
	}
	else if (stageIndex == StageIndex::Stage_Ruins)
	{
		lineBar = CLineBar::create(Line_Ruins);
		this->addChild(lineBar, TAG_LINEBAR);
	}
	else if (stageIndex == StageIndex::Stage_Site)
	{
		lineBar = CLineBar::create(Line_Site);
		this->addChild(lineBar, TAG_LINEBAR);
	}
	else if (stageIndex == Stage_Tutorial)
	{
		lineBar = CLineBar::create(Line_Forest);
		this->addChild(lineBar, TAG_LINEBAR);
	}
}
//버튼 생성
void CMainLogic::generaterButton()
{
	button = CButton::create();
	this->addChild(button, TAG_BUTTON);
	ButtonData->setButton(button);
}
//hp바 생성
void CMainLogic::generaterHpBar()
{
	hpBar = CHpBar::create(PlayerData->getHp());
	this->addChild(hpBar, TAG_HPBAR);
}
//플레이어 생성
void CMainLogic::generaterPlayer()
{
	player = CPlayer::create();
	player->setAnchorPoint(Vec2(1, 0));
	player->setPosition(Vec2(200, 275));
	this->addChild(player, TAG_PLAYER);
	PlayerData->setPlayer(player);
}
//배경 생성
void CMainLogic::generaterBackGround()
{
	if (stageIndex == Stage_Forest)
	{
		backGround = CBackGround::create("Forest", PlayerData->getStageCount());
	}
	else if (stageIndex == Stage_Ruins)
	{
		backGround = CBackGround::create("Ruins", PlayerData->getStageCount());
	}
	else if (stageIndex == Stage_Site)
	{
		backGround = CBackGround::create("Site", PlayerData->getStageCount());
	}

	this->addChild(backGround, TAG_BACKGROUND);
}
//바닥 생성
void CMainLogic::generaterBottom()
{
	if (stageIndex == Stage_Forest)
	{
		bottom = CBottom::create("Forest_Bottom");
	}
	else if (stageIndex == Stage_Ruins)
	{
		bottom = CBottom::create("Ruins_Bottom");
	}
	else if (stageIndex == Stage_Site)
	{
		bottom = CBottom::create("Site_Bottom");
	}
	else if (stageIndex == Stage_Tutorial)
	{
		bottom = CBottom::create("Forest_Bottom");
	}
	this->addChild(bottom, TAG_BOTTOM);
}

void CMainLogic::generaterCoin()
{
	coinImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("Coin")["IngameCoinScore"].asString());
	coinImage->setAnchorPoint(Vec2(0.5, 0.5));
	coinImage->setPosition(Vec2(scoreLabel->getPosition().x+20, scoreLabel->getPosition().y-40));
	this->addChild(coinImage, TAG_COINIMAGE);

	std::string coinString;
	coinString.append("x " + StringUtils::toString(coin));
	coinLabel = Label::createWithTTF("", "fonts/MoebiusBold.ttf", 30);
	coinLabel->setString(coinString);
	coinLabel->setAnchorPoint(Vec2(0, 0));
	coinLabel->setColor(Color3B(0, 0, 0));
	coinLabel->setPosition(Vec2(coinImage->getPosition().x + 30, coinImage->getPosition().y-25));
	this->addChild(coinLabel, TAG_COINLABEL);
}

void CMainLogic::makeCoin(Vec2 _pos)
{
	auto coin = CCoin::create();
	coin->setAnchorPoint(Vec2(0, 0));
	coin->setPosition(_pos);
	this->addChild(coin, 10);
	coinVector.pushBack(coin);
}

void CMainLogic::makeBox(Vec2 _pos)
{
	auto box = CBox::create();
	box->setAnchorPoint(Vec2(0.5, 0.5));
	box->setPosition(_pos);
	this->addChild(box, TAG_BOX);
	boxVector.pushBack(box);
}

void CMainLogic::makeEffect(EffectIndex _index, Vec2 _pos)
{
	auto actionEffect = CActionEffect::create(_index, _pos);
	actionEffect->setPosition(_pos);
	this->addChild(actionEffect, TAG_ACTION_EFFECT);
	actionEffectVector.pushBack(actionEffect);
}

void CMainLogic::sponKnife(EnemyIndex _index, Vec2 _pos, bool isAni)
{
	auto enemy = CEnemy::create(_index, Type_Knife, isAni);
	enemy->setScale(0.7f);
	enemy->setAnchorPoint(Vec2(0.5, 0.5));
	enemy->setPosition(_pos);
	this->addChild(enemy, TAG_Enemy_Ground);
	enemyVector.pushBack(enemy);

	if (UserDefault::getInstance()->getBoolForKey("Help"))
	{
		CEnemyHelpImage* enemyHelp = CEnemyHelpImage::create(eHelp_Knife);
		enemyHelp->setScale(1.0f);
		enemyHelp->setAnchorPoint(Vec2(0, 0));
		enemyHelp->setPosition(enemy->getPosition().x, enemy->getPosition().y + 100);
		this->addChild(enemyHelp, TAG_HELPIMAGE);
		enemyHelpImageVector.pushBack(enemyHelp);
	}
}

void CMainLogic::sponFire(EnemyIndex _index, Vec2 _pos, bool isAni)
{
	auto enemy = CEnemy::create(_index, Type_Fire, isAni);
	enemy->setScale(0.7f);
	enemy->setAnchorPoint(Vec2(0.5, 0.5));
	enemy->setPosition(_pos);
	this->addChild(enemy, TAG_Enemy_Ground);
	enemyVector.pushBack(enemy);
	if (UserDefault::getInstance()->getBoolForKey("Help"))
	{
		CEnemyHelpImage* enemyHelp = CEnemyHelpImage::create(eHelp_Torch);
		enemyHelp->setScale(1.0f);
		enemyHelp->setAnchorPoint(Vec2(0, 0));
		enemyHelp->setPosition(enemy->getPosition().x, enemy->getPosition().y + 100);
		this->addChild(enemyHelp, TAG_HELPIMAGE);
		enemyHelpImageVector.pushBack(enemyHelp);
	}
}

void CMainLogic::sponRope(EnemyIndex _index, Vec2 _pos, bool isAni)
{
	auto enemy = CEnemy::create(_index, Type_Rope, isAni);
	enemy->setScale(0.7f);
	enemy->setAnchorPoint(Vec2(0, 0));
	enemy->setPosition(_pos);
	this->addChild(enemy, TAG_Enemy_Trap);
	enemyVector.pushBack(enemy);
	if (UserDefault::getInstance()->getBoolForKey("Help"))
	{
		CEnemyHelpImage* enemyHelp = CEnemyHelpImage::create(eHelp_Rope);
		enemyHelp->setScale(1.0f);
		enemyHelp->setAnchorPoint(Vec2(0, 0));
		enemyHelp->setPosition(enemy->getPosition().x + 50, enemy->getPosition().y + 400);
		this->addChild(enemyHelp, TAG_HELPIMAGE);
		enemyHelpImageVector.pushBack(enemyHelp);
	}
}

void CMainLogic::gameOverSceneChange()
{
	Layer* layer = CGameOverScene::create();
	isGameOver = true;
	coustemPause();
	this->addChild(layer, 999);
}

void CMainLogic::coustemPause()
{
	backGround->pause();
	bottom->pause();
	player->pause();
	button->buttonPause();
	lineBar->pause();
	hpBar->pause();

	for (CCoin*coin : coinVector)
		coin->pause();
	for (CActionEffect* actionEffect : actionEffectVector)
		actionEffect->pause();
	for (CEnemy* enemy : enemyVector)
		enemy->pause();
	for (CBox* box : boxVector)
		box->pause();
	for (CEnemyHelpImage* helpImage : enemyHelpImageVector)
		helpImage->pause();
}

void CMainLogic::coustemResume()
{
	backGround->resume();
	bottom->resume();
	player->resume();
	button->buttonResume();
	lineBar->resume();
	hpBar->resume();

	for (CCoin*coin : coinVector)
		coin->resume();
	for (CActionEffect* actionEffect : actionEffectVector)
		actionEffect->resume();
	for (CEnemy* enemy : enemyVector)
		enemy->resume();
	for (CBox* box : boxVector)
		box->resume();
	for (CEnemyHelpImage* helpImage : enemyHelpImageVector)
		helpImage->resume();
}