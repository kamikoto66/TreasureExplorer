#pragma once
#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"

USING_NS_CC;
#define TAG_BACKGROUND 0
#define TAG_Enemy_Ground 2
#define TAG_BOX 2
#define TAG_BOTTOM 3
#define TAG_Enemy_Trap 4
#define TAG_PLAYER 4
#define TAG_BUTTON 5
#define TAG_HPBAR 6
#define TAG_ACTION_EFFECT 7
#define TAG_LINEBAR 8
#define COIN_DELAY_RATE 0.5f
#define TAG_HELPIMAGE 4

class CBackGround;
class CBottom;
class CButton;
class CCoin;
class CBox;
class CPlayer;
class CHpBar;
class CEnemy;
class CActionEffect;
class CLineBar;
class CEnemyHelpImage;

class CMainLogic: public Layer
{
protected:
	bool isTutorial;
	CREATEWINSIZE;
	CBackGround* backGround;
	CBottom* bottom;
	StageIndex stageIndex;
	//score
	int score;
	Label* scoreLabel;

	//player
	CPlayer* player;
	//button
	CButton* button;
	//coin
	int coin;
	Sprite* coinImage;
	Label* coinLabel;
	Vector<CCoin*> coinVector;
	bool isCoinSponDelay;
	float coinSponDelayTime;

	//Enemy
	Vector<CEnemy*> enemyVector;
	Vector<CEnemyHelpImage*> enemyHelpImageVector;
	bool isEnemySponDelayTime;
	float enemySponDelayTime;
	float enemySponDelayTimeRate;
	
	//box
	Vector<CBox*> boxVector;
	//hpk
	CHpBar* hpBar;
	//actionEffect
	Vector<CActionEffect*> actionEffectVector;

	bool isGameOver;
	//pause
	bool isPause;
	CLineBar* lineBar;

private: 
	void generaterScoreLabel();
	void generaterButton();
	void generaterPlayer();
	void generaterBackGround();
	void generaterBottom();
	void generaterHpBar();
	void generaterCoin();
	void generaterLineBar();
	void generaterSound();

public:
	CMainLogic();
	~CMainLogic();

	virtual bool init(StageIndex _index);
	void update();
	void scoreUpdate();
	void playerUpdate();
	void enemyUpdate();
	void actionEffectUpdate();
	void coinUpdate();
	void gameOverSceneChange();
	void coustemPause();
	void coustemResume();

protected:
	void makeCoin(Vec2 _pos);
	void makeBox(Vec2 _pos);
	void makeEffect(EffectIndex _index, Vec2 _pos);
	void sponKnife(EnemyIndex _index, Vec2 _pos, bool isAni);
	void sponFire(EnemyIndex _index, Vec2 _pos, bool isAni);
	void sponRope(EnemyIndex _index, Vec2 _pos, bool isAni);

public:
	void setIsPause(bool _isPause) { isPause = _isPause; }
	void setEnemySponDelayRate(float _rate) { enemySponDelayTimeRate = _rate; }

	bool getPause() const { return isPause; }
	bool getIsTutorial() { return isTutorial; }
	float getEnemySponDelayRate() const { return enemySponDelayTimeRate;};
};

