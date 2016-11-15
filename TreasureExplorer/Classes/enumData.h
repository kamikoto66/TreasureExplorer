#pragma once 

//스테이지 인덱스
enum StageIndex
{
	Stage_Tutorial,
	Stage_Forest,
	Stage_Ruins,
	Stage_Site
};

/*
2.덤불
3.버섯
4.독초
5.나무
5.이끼
6.가시덤불
7.늪
8.웅덩이
9.함정
*/
enum EnemyIndex
{
	Bush = 1,
	MoushRoom,
	PoisonPlant,
	Tree,
	Moss,
	ThornBush,
	Swamp,
	Puddle,
	Trap
};

//장애물 타입
enum EnemyType
{
	Type_Knife,
	Type_Fire,
	Type_Rope
};

//장애물 상태
enum EnemyState
{
	Enemy_Move,
	Enemy_Die,
	Enemy_Null
};

enum HelpIndex
{
	eHelp_Knife,
	eHelp_Torch,
	eHelp_Rope
};

enum HelpState
{
	eHelpState_Move,
	eHelpState_MoveEnd,
	eHelpState_Null
};

//버튼 상태
enum ButtonState
{
	Button_Knife,
	Button_Torch,
	Button_Rope
};

//플레이어 이펙트 
enum EffectIndex
{
	Effect_Knife,
	Effect_Fire,
	Effect_Rope
};

enum EffectState
{
	Effect_On,
	Effect_Off
};

//플레이어 상태
enum PlayerState
{
	Player_Run,
	Player_Run_Knife,
	Player_Run_Fire,
	Player_Run_Rope,
	Player_Action_Knife,
	Player_Action_Fire,
	Player_Action_Rope_Shot,
	Player_Action_Rope_Up,
	Player_Action_Rope_Down
};

//진행바 속성
enum LineBarIndex
{
	Line_Forest,
	Line_Ruins,
	Line_Site
};

//진행바 상태
enum LineBarState
{
	Line_State_Run,
	Line_State_Goal,
	Line_State_Collision,
	Line_State_Stop
};
//플레이어 점프 
enum JumpState
{
	Jump_Idel,
	Jump_Max,
	Jump_Down,
	Jump_Min
};

//코인 상태
enum class CoinState
{
	eCoinState_Stay,
	eCoinState_Drop,
	eCoinState_FadeOut,
	eCoinState_Null
};

//스폰 타입
enum SponType
{
	eBlank,
	eEnemy,
	eCoin,
	eBox
};

enum BoxIndex
{
	eBoxForestAccessoryShabby,
	eBoxRunisAccessoryShabby,
	eBoxSiteAccessoryShabby,
	eBoxForestCapShabby,
	eBoxRunisCapShabby,
	eBoxSiteCapShabby,
	eBoxForestWearShabby,
	eBoxRunisWearShabby,
	eBoxSiteWearShabby
};

enum BoxState
{
	eBoxStateMove,
	eBoxStateDrop,
	eBoxStateFade,
	eBoxStateNull
};

enum TreasureIndex
{
	eTreasureBlank = -2,
	eTreasureBox,
	eForestAccessoryShabby,
	eRunisAccessoryShabby,
	eSiteAccessoryShabby,
	eForestCapShabby,
	eRunisCapShabby,
	eSiteCapShabby,
	eForestWearShabby,
	eRunisWearShabby,
	eSiteWearShabby,
	eForestAccessoryNomal,
	eRunisAccessoryNomal,
	eSiteAccessoryNomal,
	eForestCapNomal,
	eRunisCapNomal,
	eSiteCapNomal,
	eForestWearNomal,
	eRunisWearNomal,
	eSiteWearNomal,
	eForestAccessoryGood,
	eRunisAccessoryGood,
	eSiteAccessoryGood,
	eForestCapGood,
	eRunisCapGood,
	eSiteCapGood,
	eForestWearGood,
	eRunisWearGood,
	eSiteWearGood
};

enum TreasureType
{
	eShabby,
	eNomal,
	eGood
};

enum LodingType
{
	LodingInGame
};