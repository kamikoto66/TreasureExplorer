#include "PCH.h"
#include "ActionEffect.h"
#include "Player.h"
#include "PlayerData.h"
#include "soundManager.h"

CActionEffect::CActionEffect()
{
	effectState = (EffectState)-1;
	effectIndex = (EffectIndex)-1;
	tergetEnemyType = (EnemyType)-1;
	ropeEffectRotationDelayTime = 0.0f;
	isRopeEffectRotation = false;
	basePos = Vec2(0, 0);
}

CActionEffect::~CActionEffect()
{

}


bool CActionEffect::init(EffectIndex _index, Vec2 _pos)
{
	if (!Node::init())
	{
		return false;
	}
	effectIndex = _index;
	basePos = _pos;
	effectState = Effect_On;
	generaterEffect();
	this->scheduleUpdate();

	return true;
}

void CActionEffect::update(float dt)
{
	actionUpdate();
}

void CActionEffect::actionUpdate()
{
	if (effectIndex == Effect_Knife)
	{
		if (getOpacity() == 0)
		{
			effectState = Effect_Off;
		}
	}
	else if (effectIndex == Effect_Fire)
	{
		if (getActionByTag(TAG_FIRE_ACTION) == nullptr)
		{
			effectState = Effect_Off;
		}
		else
		{
			float rotate = getRotation();
			rotate += 10;
			setRotation(rotate);
		}
	}
	else if (effectIndex == Effect_Rope)
	{
		if (isRopeEffectRotation)
		{
			ropeEffectRotationDelayTime += Director::getInstance()->getDeltaTime();
			if (ropeEffectRotationDelayTime >= 1.0f)
			{
				effectState = Effect_Off;
				PlayerData->getPlayer()->setPlayerState(Player_Action_Rope_Down);
			}
		}
		else
		{
			float rotation = getRotationX();
			rotation -= 5;
			if (rotation == 15)
			{
				isRopeEffectRotation = true;
			}
			else
			{
				setRotationX(rotation);
			}
		}
	}
}

void CActionEffect::generaterEffect()
{
	if (effectIndex == Effect_Knife)
	{
		tergetEnemyType = EnemyType::Type_Knife;
		effectState = Effect_On;
		Sprite::initWithFile(JSON_MGR->getFilePathRootWithTag("ActionEffect")["knife_effect"]["basePath"].asString());
		setScale(0.7f);
		setAnchorPoint(Vec2(0.5, 0.5));
		setPosition(basePos);
		knifeEffectAction();
	}
	else if (effectIndex == Effect_Fire)
	{
		tergetEnemyType = Type_Fire;
		effectState = Effect_On;
		Sprite::initWithFile(JSON_MGR->getFilePathRootWithTag("ActionEffect")["fire_effect"]["basePath"].asString());
		setAnchorPoint(Vec2(0.5, 0.5));
		setScale(0.7f);
		setPosition(basePos);
		fireEffectAction();
	}
	else if (effectIndex == Effect_Rope)
	{
		tergetEnemyType = Type_Rope;
		effectState = Effect_On;
		Sprite::initWithFile(JSON_MGR->getFilePathRootWithTag("ActionEffect")["rope_effect"]["basePath"].asString());
		setAnchorPoint(Vec2(0, 0));
		setPosition(basePos);
		setRotationX(45);
	}
}

void CActionEffect::knifeEffectAction()
{
	auto fade_Out = FadeOut::create(0.3f);
	auto seq = Sequence::create(fade_Out, NULL);
	runAction(seq);
	CSoundManager::getInstance()->playEffect("sound/knife.mp3");
}

void CActionEffect::fireEffectAction()
{
	ccBezierConfig bezierConfig;
	Vec2 endPos;
	endPos.x = basePos.x + 800;
	endPos.y = 140;
	Vec2 control2Pos;
	control2Pos.x = basePos.x + 650;
	control2Pos.y = basePos.y + 150;

	bezierConfig.controlPoint_1 = basePos;
	bezierConfig.controlPoint_2 = control2Pos;
	bezierConfig.endPosition = endPos;
	auto action = BezierTo::create(1.5f, bezierConfig);
	action->setTag(TAG_FIRE_ACTION);
	runAction(action);
	CSoundManager::getInstance()->playEffect("sound/torch.mp3", false, 1.0f);
}