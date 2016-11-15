#pragma once
#include "cocos2d.h"
#include "Macro.h"
#include "enumData.h"

USING_NS_CC;

class CCoin : public Sprite
{
private:
	int score;
	int coin;
	CoinState coinState;
	Vec2 moveVector;

private:
	bool generatorCoin();
	void setCoinStateForNode(Node* _coin, CoinState _CoinState) { auto Coin = static_cast<CCoin*>(_coin); Coin->setCoinState(_CoinState); }
	
public:
	CCoin();
	~CCoin();

	virtual bool init();
	void update(float dt);
	void stateUpdate();
	void moveUpdate();
	void collisionUpdate();

	CREATE_FUNC_ARGS(CCoin);

public:
	void setScore(int _score) { score = _score; }
	void setCoinState(CoinState _coinState) { coinState = _coinState; }
	void setCoin(int _coin) { coin = _coin; }

	int getScore() const { return score; }
	CoinState getCoinState() const { return coinState; }
	int getCoin() const{ return coin; }
};

