#pragma once 

//�������� �ε���
enum StageIndex
{
	Stage_Tutorial,
	Stage_Forest,
	Stage_Ruins,
	Stage_Site
};

/*
2.����
3.����
4.����
5.����
5.�̳�
6.���ô���
7.��
8.������
9.����
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

//��ֹ� Ÿ��
enum EnemyType
{
	Type_Knife,
	Type_Fire,
	Type_Rope
};

//��ֹ� ����
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

//��ư ����
enum ButtonState
{
	Button_Knife,
	Button_Torch,
	Button_Rope
};

//�÷��̾� ����Ʈ 
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

//�÷��̾� ����
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

//����� �Ӽ�
enum LineBarIndex
{
	Line_Forest,
	Line_Ruins,
	Line_Site
};

//����� ����
enum LineBarState
{
	Line_State_Run,
	Line_State_Goal,
	Line_State_Collision,
	Line_State_Stop
};
//�÷��̾� ���� 
enum JumpState
{
	Jump_Idel,
	Jump_Max,
	Jump_Down,
	Jump_Min
};

//���� ����
enum class CoinState
{
	eCoinState_Stay,
	eCoinState_Drop,
	eCoinState_FadeOut,
	eCoinState_Null
};

//���� Ÿ��
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