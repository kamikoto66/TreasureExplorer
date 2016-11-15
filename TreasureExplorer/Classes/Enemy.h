#pragma once
#include "cocos2d.h"
#include "enumData.h"
#include "Animation.h"

USING_NS_CC;

class CEnemy : public Sprite
{
private:
	Sprite* helpImage;
	EnemyType enemyType;
	EnemyIndex enemyIndex;
	EnemyState enemyState;
	Vec2 moveVector;
	bool isDie;
	CAnimation* enemyDieAni;
	bool isAni;

private:

	void generaterEnemy();
	static CAnimation* createAnimation(std::string jsonName);

public:
	CEnemy();
	~CEnemy();

	virtual bool init(EnemyIndex _index, EnemyType _type, bool _isAni);
	void update(float dt);
	void aniUpdate(float dt);
	void stateUpdate();
	void moveUpdate();

	CREATE_FUNC_ARGS(CEnemy);
public:
	void setEnemyType(EnemyType _enemyType) { enemyType = _enemyType; }
	void setEnemyState(EnemyState _enemyState) { enemyState = _enemyState; }
	void setsDie(bool _isDie) { isDie = _isDie; };

	EnemyType getEnemyType() const { return enemyType; }
	EnemyState getEnemyState() const { return enemyState; }
	bool getDie() const { return isDie; }
};

