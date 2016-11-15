#include "PCH.h"
#include "Enemy.h"
#include "Player.h"
#include "JsonManager.h"

CEnemy::CEnemy()
{
	enemyIndex = (EnemyIndex)-1;
	enemyType = (EnemyType)-1;
	enemyState = (EnemyState)-1;
	moveVector = Vec2(0, 0);
	isDie = false;
	enemyDieAni = nullptr;
}


CEnemy::~CEnemy()
{
}

bool CEnemy::init(EnemyIndex _index, EnemyType _type, bool _isAni)
{
	if (!Node::init())
	{
		return false;
	}
	enemyIndex = _index;
	enemyType = _type;
	isAni = isAni;

	generaterEnemy();

	this->scheduleUpdate();
	return true;
}

void CEnemy::update(float dt)
{
	if (isDie)
		aniUpdate(dt);
	stateUpdate();
	moveUpdate();
}

void CEnemy::stateUpdate()
{
	if (enemyState == Enemy_Move)
	{
		if (getPosition().x <= -200)
		{
			enemyState = Enemy_Die;
			isDie = true;
		}

		moveVector = Vec2(1, 0);
	}
	else if (enemyState == Enemy_Die)
	{
		moveVector = Vec2(1, 0);
		if (enemyDieAni->getAniEnd() == false)
		{
			enemyState = Enemy_Null;
		}
	}
}

void CEnemy::moveUpdate()
{
	moveVector.x *= 10 + (PlayerData->getStageCount() * 2);
	setPosition(getPosition().x - moveVector.x, getPosition().y);
}

void CEnemy::aniUpdate(float dt)
{
	auto spr = enemyDieAni->run(dt);
	if (spr == LOOPACTIVE)
		return;
	else if (spr == LOOPEND)
		return;
	else
		this->setTexture(spr->getTexture());
}

void CEnemy::generaterEnemy()
{
	std::string UnitBasePath;
	std::string dieAniName;

	switch (enemyIndex)
	{
	case	Bush:				UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["Bush"].asString();			dieAniName = "Bush";		break;
	case	Moss:				UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["Moss"].asString();			dieAniName = "Moss";		break;
	case 	MoushRoom:			UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["MoushRoom"].asString();	dieAniName = "MoushRoom";	break;
	case 	PoisonPlant:		UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["PoisonPlant"].asString();	dieAniName = "PoisonPlant";	break;
	case 	Tree:				UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["Tree"].asString();			dieAniName = "Tree";		break;
	case 	ThornBush:			UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["ThornBush"].asString();	dieAniName = "ThornBush";	break;
	case 	Swamp:				UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["Swamp"].asString();		dieAniName = "Swamp";		break;
	case 	Puddle:				UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["Puddle"].asString();		dieAniName = "Puddle";		break;
	case 	Trap:				UnitBasePath = JSON_MGR->getFilePathRootWithTag("UnitBase")["Trap"].asString();			dieAniName = "Trap";		break;
	}

	Sprite::initWithFile(UnitBasePath);
	enemyState = EnemyState::Enemy_Move;
	enemyDieAni = createAnimation(dieAniName);
}

CAnimation* CEnemy::createAnimation(std::string jsonName)
{
	std::string AniBasepath;
	AniBasepath.append("Unit/" + jsonName + "/");


	auto ani = CAnimation::create(JSON_MGR->getFilePathRootWithTag("UnitDieAni")[jsonName]["AniRate"].asFloat(), JSON_MGR->getFilePathRootWithTag("PlayerAni")[jsonName]["AniLoop"].asBool());

	for (int i = 0; i < JSON_MGR->getFilePathRootWithTag("UnitDieAni")[jsonName]["AniCount"].asInt(); i++)
	{
		std::string aniPath;
		aniPath.append(AniBasepath);
		aniPath.append(JSON_MGR->getFilePathRootWithTag("UnitDieAni")[jsonName]["AniName"].asString() + "/");
		aniPath.append(StringUtils::toString(i) + ".png");
		ani->addFrame(aniPath);
	}

	return ani;
}