#include "PCH.h"
#include "MainLogic.h"
#include "Stage2.h"


CStage2::CStage2()
{

}

CStage2::~CStage2()
{

}

bool CStage2::init()
{
	if (!CMainLogic::init(Stage_Ruins))
	{
		return false;
	}

	this->scheduleUpdate();

	return true;
}

void CStage2::update(float dt)
{
	if (!isGameOver && !isPause )
	{
		CMainLogic::update();

		if (!PlayerData->getisTreasureBoxSpon())
		{
			int rand = cocos2d::random(0, 50000);
			if (rand < 20)
			{
				makeBox(Vec2(2000, 160));
				PlayerData->setisTreasureBoxSpon(true);
			}
		}

		if (isCoinSponDelay)
		{
			coinSponDelayTime += Director::getInstance()->getDeltaTime();

			if (coinSponDelayTime >= COIN_DELAY_RATE)
			{
				coinSponDelayTime = 0.0f;
				isCoinSponDelay = false;
			}
		}
		else if (!isCoinSponDelay)
		{
			makeCoin(Vec2(1350, 220));
			isCoinSponDelay = true;
		}

		if (isEnemySponDelayTime)
		{
			enemySponDelayTime += Director::getInstance()->getDeltaTime();
			if (enemySponDelayTime >= enemySponDelayTimeRate)
			{
				enemySponDelayTime = 0.0f;
				enemySponDelayTimeRate -= 0.5f;
				isEnemySponDelayTime = false;

				if (enemySponDelayTimeRate <= 3.0f)
					enemySponDelayTimeRate = 3.0f;
			}
		}
		else if (!isEnemySponDelayTime)
		{
			int Rand = cocos2d::random(0, 300);

			if (Rand % 3 == 0)
			{
				sponKnife(MoushRoom, Vec2(2000, 220), true);
			}
			else if (Rand % 3 == 1)
			{
				sponFire(Moss, Vec2(2000, 220), true);
			}
			else if (Rand % 3 == 2)
			{
				sponRope(Swamp, Vec2(2000, -220), false);
			}

			isEnemySponDelayTime = true;
		}
	}
}