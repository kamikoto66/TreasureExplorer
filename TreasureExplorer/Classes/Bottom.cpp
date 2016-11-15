#include "PCH.h"
#include "Bottom.h"
#include "PlayerData.h"

USING_NS_CC;

CBottom::CBottom()
{
	winSize = Size(0,0);
	bottomName.clear();
	bottomLayer = NULL;
	bottom_0 = nullptr;
	bottom_1 = nullptr;
}


CBottom::~CBottom()
{
} 

bool CBottom::init(std::string StageName)
{
	if (!Node::init())
	{
		return false;
	}

	bottomName = StageName;

	gneraterBottom();
	scheduleUpdate();

	return true;
}

void CBottom::update(float dt)
{
	for (Sprite* pSprite : bottomImage)
	{
		Vec2 pos = pSprite->getPosition();
		pos.x -= 10 + (PlayerData->getStageCount()*2);
		pSprite->setPosition(pos);

		if (pos.x <= -2000)
		{
			pos.x = 2000;
			pSprite->setPosition(pos);
		}
	}
}

void CBottom::gneraterBottom()
{
	bottomLayer = Layer::create();
	this->addChild(bottomLayer);

	Vec2 FirstPos;
	FirstPos = Vec2::ZERO;
	Vec2 SecondPos;
	SecondPos = Vec2(2000, 0);

	if (bottomName == "Forest_Bottom")
	{
		bottom_0 = createBottom("Forest/Forest_bottom.png", FirstPos);
		bottom_1 = createBottom("Forest/Forest_bottom.png", SecondPos);
	}
	else if (bottomName == "Ruins_Bottom")
	{
		bottom_0 = createBottom("Ruins/Ruins_bottom.png", FirstPos);
		bottom_1 = createBottom("Ruins/Ruins_bottom.png", SecondPos);
	}
	else if (bottomName == "Site_Bottom")
	{
		bottom_0 = createBottom("Site/Site_bottom.png", FirstPos);
		bottom_1 = createBottom("Site/Site_bottom.png", SecondPos);
	}

	this->addChild(bottom_0, 0);
	this->addChild(bottom_1, 1);

	bottomImage.pushBack(bottom_0);
	bottomImage.pushBack(bottom_1);
}

Sprite* CBottom::createBottom(std::string _bottomName, Vec2 _pos) //바닥 배경을 더해준다
{
	std::string temp;
	temp.append("background/");
	temp += _bottomName;

	auto spr = Sprite::create(temp.c_str());
	spr->setAnchorPoint(Point::ZERO);
	spr->setPosition(_pos);

	return spr;
}