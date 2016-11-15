#include "PCH.h"
#include "BackGround.h"
//#include "Stage1.h"
//#include "Stage2.h"
//#include "defineValue.h"

USING_NS_CC;

CBackGround::CBackGround()
{
	winSize = Director::getInstance()->getWinSize();   
	originPos = Vec2::ZERO;
	stageName.clear();
	backGroundVector.clear();
	backGround_Air_0 = nullptr;
	backGround_Air_1 = nullptr;

	backGround_B_0 = nullptr;
	backGround_B_1 = nullptr;

	backGround_C_0 = nullptr;
	backGround_C_1 = nullptr;

	backGround_D_0 = nullptr;
	backGround_D_1 = nullptr;
	stageCount = 0;
}

CBackGround ::~CBackGround()
{

}

bool CBackGround::init(std::string _stageName, int _stageCount)
{
	if (!Node::init())
	{
		return false;
	}

	//배경 이름
	stageCount = _stageCount;
	if (stageCount >= 3)
		stageCount = 3;

	stageName = _stageName;
	generaterBackGround();
	scheduleUpdate();

	return true;
}

void CBackGround::update(float dt)
{
	backGroundMoveUpdate();
} 

void CBackGround::backGroundMoveUpdate()
{
	auto itr = backGroundVector.begin();
	for (itr; itr != backGroundVector.end(); itr++)
	{
		Vec2 pos = (*itr)->getPosition();
		if ((*itr)->getName() == "Air")
			pos.x -= 4 + (stageCount * 2);
		else if ((*itr)->getName() == "B")
			pos.x -= 6 + (stageCount * 2);
		else if ((*itr)->getName() == "C")
			pos.x -= 8 + (stageCount * 2);
		else if ((*itr)->getName() == "D")
			pos.x -= 10 + (stageCount * 2);

		(*itr)->setPosition(pos);

		if (pos.x <= -2000)
		{
			(*itr)->setPosition(Vec2(2000, pos.y));
		}
	}
}

void CBackGround::generaterBackGround()
{
	Vec2 FirstPos;
	Vec2 SecondPos;
	FirstPos.x = 0;
	FirstPos.y = Director::getInstance()->getWinSize().height / 3 - 100;
	SecondPos.x = 2000;
	SecondPos.y = Director::getInstance()->getWinSize().height / 3 - 100;

	//배경 만들어줌
	if (stageName == "Forest")
	{
		backGround_Air_0 = createBackGround(std::string(stageName + "/" + "Forest_Air.png"), TAG_BACKGROUND_AIR, FirstPos);
		backGround_Air_1 = createBackGround(std::string(stageName + "/" + "Forest_Air.png"), TAG_BACKGROUND_AIR, SecondPos);

		backGround_B_0 = createBackGround(std::string(stageName + "/" + "Forest_B.png"), TAG_BACKGROUND_B, FirstPos);
		backGround_B_1 = createBackGround(std::string(stageName + "/" + "Forest_B.png"), TAG_BACKGROUND_B, SecondPos);

		backGround_C_0 = createBackGround(std::string(stageName + "/" + "Forest_C.png"), TAG_BACKGROUND_C, FirstPos);
		backGround_C_1 = createBackGround(std::string(stageName + "/" + "Forest_C.png"), TAG_BACKGROUND_C, SecondPos);

		backGround_D_0 = createBackGround(std::string(stageName + "/" + "Forest_D.png"), TAG_BACKGROUND_D, FirstPos);
		backGround_D_1 = createBackGround(std::string(stageName + "/" + "Forest_D.png"), TAG_BACKGROUND_D, SecondPos);
	}
	else if (stageName == "Ruins")
	{
		backGround_Air_0 = createBackGround(std::string(stageName + "/" + "Ruins_Air.png"), TAG_BACKGROUND_AIR, FirstPos);
		backGround_Air_1 = createBackGround(std::string(stageName + "/" + "Ruins_Air.png"), TAG_BACKGROUND_AIR, SecondPos);

		backGround_B_0 = createBackGround(std::string(stageName + "/" + "Ruins_B.png"), TAG_BACKGROUND_B, FirstPos);
		backGround_B_1 = createBackGround(std::string(stageName + "/" + "Ruins_B.png"), TAG_BACKGROUND_B, SecondPos);

		backGround_C_0 = createBackGround(std::string(stageName + "/" + "Ruins_C.png"), TAG_BACKGROUND_C, FirstPos);
		backGround_C_1 = createBackGround(std::string(stageName + "/" + "Ruins_C.png"), TAG_BACKGROUND_C, SecondPos);

		backGround_D_0 = createBackGround(std::string(stageName + "/" + "Ruins_D.png"), TAG_BACKGROUND_D, FirstPos);
		backGround_D_1 = createBackGround(std::string(stageName + "/" + "Ruins_D.png"), TAG_BACKGROUND_D, SecondPos);
	}
	else if (stageName == "Site")
	{
		backGround_Air_0 = createBackGround(std::string(stageName + "/" + "Site_Air.png"), TAG_BACKGROUND_AIR, FirstPos);
		backGround_Air_1 = createBackGround(std::string(stageName + "/" + "Site_Air.png"), TAG_BACKGROUND_AIR, SecondPos);

		backGround_B_0 = createBackGround(std::string(stageName + "/" + "Site_B.png"), TAG_BACKGROUND_B, FirstPos);
		backGround_B_1 = createBackGround(std::string(stageName + "/" + "Site_B.png"), TAG_BACKGROUND_B, SecondPos);

		backGround_C_0 = createBackGround(std::string(stageName + "/" + "Site_C.png"), TAG_BACKGROUND_C, FirstPos);
		backGround_C_1 = createBackGround(std::string(stageName + "/" + "Site_C.png"), TAG_BACKGROUND_C, SecondPos);
	}

	if (backGround_Air_0 != nullptr)
	{
		this->addChild(backGround_Air_0, 0, "Air");
		backGroundVector.pushBack(backGround_Air_0);
	}
	
	if (backGround_Air_1 != nullptr)
	{
		this->addChild(backGround_Air_1, 1, "Air");
		backGroundVector.pushBack(backGround_Air_1);
	}
	
	if (backGround_B_0 != nullptr)
	{
		this->addChild(backGround_B_0, 2, "B");
		backGroundVector.pushBack(backGround_B_0);
	}
	if (backGround_B_1 != nullptr)
	{
		this->addChild(backGround_B_1, 3, "B");
		backGroundVector.pushBack(backGround_B_1);
	}
	
	if (backGround_C_0 != nullptr)
	{
		this->addChild(backGround_C_0, 4, "C");
		backGroundVector.pushBack(backGround_C_0);
	}
	
	if (backGround_C_1 != nullptr)
	{
		this->addChild(backGround_C_1, 5, "C");
		backGroundVector.pushBack(backGround_C_1);
	}
	
	if (backGround_D_0 != nullptr)
	{
		this->addChild(backGround_D_0, 6, "D");
		backGroundVector.pushBack(backGround_D_0);
	}
	
	if (backGround_D_1 != nullptr)
	{
		this->addChild(backGround_D_1, 7, "D");
		backGroundVector.pushBack(backGround_D_1);
	}
}

Sprite* CBackGround::createBackGround(std::string _path, int _tag, Point _pos)
{
	std::string backGroundPath;
	backGroundPath.append("background/");
	backGroundPath.append(_path);

	auto backGround = Sprite::create(backGroundPath);
	backGround->setAnchorPoint(Vec2(0, 0));
	backGround->setPosition(_pos);
	backGround->setTag(_tag);
	return backGround;
}