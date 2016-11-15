#include "PCH.h"
#include "HpBar.h"
#include "JsonManager.h"

CHpBar::CHpBar()
{
	hpCount = 0;
	hpBarImage = nullptr;
	hpBarImageFront = nullptr;
	for (int i = 0; i < 5; i++)
	{
		hpImage[i] = nullptr;
		isHpImageRender[i] = false;
	}
}


CHpBar::~CHpBar()
{
}

bool CHpBar::init(int hpSize)
{
	if (!Node::init())
	{
		return false;
	}

	hpCount = hpSize;
	generaterHpBar();
	return true;
}


void CHpBar::generaterHpBar()
{
	hpBarImage = Sprite::create(JSON_MGR->getFilePathRootWithTag("HpImage")["HpBar"].asString());
	hpBarImage->setAnchorPoint(Vec2(0, 0));
	hpBarImage->setScale(0.6f);
	hpBarImage->setPosition(Vec2(50, 570));
	this->addChild(hpBarImage, 0);

	hpBarImageFront = Sprite::create(JSON_MGR->getFilePathRootWithTag("HpImage")["HpBarImageFront"].asString());
	hpBarImageFront->setAnchorPoint(Vec2(0, 0));
	hpBarImageFront->setScale(0.6f);
	hpBarImageFront->setPosition(hpBarImage->getPositionX()-10, hpBarImage->getPositionY());
	this->addChild(hpBarImageFront, 2);

	for (int i = 0; i < hpCount; i++)
	{
		Vec2 hpImagePos;

		if (i == 4)
		{
			hpImage[i] = Sprite::create(JSON_MGR->getFilePathRootWithTag("HpImage")["fullHp"].asString());
			hpImagePos.x = hpImage[i - 1]->getPositionX();
			hpImagePos.y = hpImage[i - 1]->getPositionY();
			hpImage[i]->setAnchorPoint(Vec2(0, 0));
			hpImage[i]->setScale(0.6f);
			hpImage[i]->setPosition(hpImagePos);
			this->addChild(hpImage[i], 3);
			isHpImageRender[i] = true;
		}
		else
		{
			hpImage[i] = Sprite::create(JSON_MGR->getFilePathRootWithTag("HpImage")["nomalHp"].asString());
			hpImagePos.x = (hpBarImage->getPosition().x + (30 * i)) + 20;
			hpImagePos.y = hpBarImage->getPosition().y;
			hpImage[i]->setScale(0.6f);
			hpImage[i]->setAnchorPoint(Vec2(0, 0));
			hpImage[i]->setPosition(hpImagePos);
			this->addChild(hpImage[i], 1);
			isHpImageRender[i] = true;
		}
	}

}

void CHpBar::attackedPlayer()
{
	if (hpCount != 0)
	{
		hpImage[hpCount - 1]->setVisible(false);
		isHpImageRender[hpCount - 1] = false;
		hpCount--;
		PlayerData->setHp(hpCount);
	}
	else if (hpCount == 0)
	{
		//게임오버 씬으로 전환
	}
}