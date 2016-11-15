#include "PCH.h"
#include "Coin.h"
#include "Player.h"
#include "PlayerData.h"
#include "CollisionManager.h"

CCoin::CCoin()
{
	coin = 0;
	score = 0;
	moveVector = Vec2(0, 0);
}


CCoin::~CCoin()
{
}

bool CCoin::init()
{
	bool isFalseAndTrue = generatorCoin();

	this->scheduleUpdate();

	return true;
}

void CCoin::update(float dt)
{
	stateUpdate();
	collisionUpdate();
	moveUpdate();
}

void CCoin::stateUpdate()
{
	if (coinState == CoinState::eCoinState_Stay)
	{
		moveVector = Vec2(-1, 0);
	}
	else if (coinState == CoinState::eCoinState_Drop)
	{	
		auto fade = FadeOut::create(0.2f);
		auto callFuncN = CallFuncN::create(CC_CALLBACK_1(CCoin::setCoinStateForNode, this, CoinState::eCoinState_FadeOut));
		auto seq = Sequence::create(fade, callFuncN, NULL);
		this->runAction(seq);
	}
}

void CCoin::collisionUpdate()
{
	if (PlayerData->getPlayer() != nullptr)
	{
		if (this->getPositionX() <= PlayerData->getPlayer()->getPositionX() + 200)
		{
			if (CollisionManager::getInstance()->CircleCheck(PlayerData->getPlayer()->getPosition(), this->getPosition(), 70) && coinState == CoinState::eCoinState_Stay)
			{
				coinState = CoinState::eCoinState_Drop;
				moveVector = Vec2(0, 0);
				PlayerData->setScore(PlayerData->getScore() + score);
				PlayerData->setCoin(PlayerData->getCoin() + coin);
			}
		}
	}
}

void CCoin::moveUpdate()
{
	moveVector.x *= 10 + (PlayerData->getStageCount() * 2);
	setPosition(getPositionX() + moveVector.x, getPositionY());
}

bool CCoin::generatorCoin()
{
	if (!Sprite::initWithFile("coin/coin.png"))
	{
		return false;
	}

	coin = 1;
	score = 100;
	coinState = CoinState::eCoinState_Stay;

	return true;
}