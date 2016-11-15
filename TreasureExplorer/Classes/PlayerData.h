#pragma once
#include "SingleTon.h"
#include "enumData.h"
class CPlayer;

class CPlayerData :public SingleTon<CPlayerData>
{
private:
	int playerHp;
	int playerCoin;
	int stageCount;
	PlayerState playerState;
	int playerNowAniCount;
	int playerScore;
	CPlayer* player;
	bool isTreasureBoxGet;
	BoxIndex boxIndex;
	bool isTreasureBoxSpon;

public:
	CPlayerData() 
	{
		playerHp = 5;
		playerCoin = 0;
		stageCount = 0;
		playerState = (PlayerState)-1;
		playerNowAniCount = 0;
		playerScore = 0;
		player = nullptr;
		isTreasureBoxGet = false;
		boxIndex = (BoxIndex)-1;
		isTreasureBoxSpon = false;
	}
	~CPlayerData() {}

public:
	void setHp(int _hp) { playerHp = _hp; }
	void setCoin(int _coin) { playerCoin = _coin; }
	void setStageCount(int _stageCount) { stageCount = _stageCount; }
	void setPlayerState(PlayerState _playerState) { playerState = _playerState; }
	void setPlayerNowAnimationCount(int _aniCount) { playerNowAniCount = _aniCount; }
	void setScore(int _score) { playerScore = _score; }
	void setPlayer(CPlayer* _player) { player = _player; }
	void setIsTreasureBox(bool _isTreasureBoxGet) { isTreasureBoxGet = _isTreasureBoxGet; }
	void setBoxIndex(BoxIndex _boxIndex) { boxIndex = _boxIndex; }
	void setisTreasureBoxSpon(bool _isTreasureBoxSpon) { isTreasureBoxSpon = _isTreasureBoxSpon; }

	int getHp() const{ return playerHp; }
	int getCoin() const { return playerCoin; }
	int getStageCount() const{ return stageCount; }
	PlayerState getPlayerState() const { return playerState; }
	int getPlayerNowAnimationCount() const { return playerNowAniCount; }
	int getScore() const { return playerScore; }
	CPlayer* getPlayer() const { return player; }
	bool getIsTreasureBox() const { return isTreasureBoxGet; }
	BoxIndex getBoxIndex() const { return boxIndex; }
	bool getisTreasureBoxSpon() const { return isTreasureBoxSpon; }
};

#define PlayerData CPlayerData::getInstance()