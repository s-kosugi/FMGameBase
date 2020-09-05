/*==============================================================================*/
/*																				*/
/*	@file title	:	IEnemyBase.cpp												*/
/*  @brief		:	敵ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "IEnemyBase.h"
#include "..\Effect\cEffectManager.h"
#include "..\..\..\cGame.h"
#include "..\..\..\SceneManager\cSceneManager.h"
#include "..\..\..\SceneManager\Scene\GameMain\cGameMain.h"
#include "..\Player\cPlayer.h"

//==========================================================================================
// 定数
//==========================================================================================
const int  IEnemyBase::AREAOUT_ADJUST = 100; // エリアアウト距離
const int  IEnemyBase::ATTACK_POS = 300;	 // 攻撃座標
const float IEnemyBase::HIT_DIST = 130.0f;	 // 当たり判定の半径

//==========================================================================================
// コンストラクタ
//==========================================================================================
IEnemyBase::IEnemyBase(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cSpriteObject(parent, object_name, graphic_file_name),
	m_vPosUp(0.0f,0.0f),
	m_nScore(0),
	m_fDist( HIT_DIST )
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
IEnemyBase::~IEnemyBase(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void IEnemyBase::Initialize(void)
{
	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void IEnemyBase::Update(void)
{
	cGameMain* gm = (cGameMain*)GetParent()->GetParent();

	// ゲームプレイ中にのみ敵を動かす
	if( gm->GetGameState() == cGameMain::GAME_STATE::PLAY)
	{
		m_vPos += m_vPosUp;
	}
	
	// 画面左にエリアアウトしたら敵を削除する
	AreaOutLeftProc();

	cSpriteObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* IEnemyBase::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// 死亡処理
//==========================================================================================
void IEnemyBase::Dead( void )
{
	DeleteObject();
}

//==========================================================================================
// 攻撃開始関数
//==========================================================================================
void IEnemyBase::StartAttack( void )
{
	// エフェクト生成位置算出
	cVector2 vec = m_vPos;
	vec.x -= ATTACK_POS;

	// 攻撃エフェクト生成
	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	if( em ) em->Create(EFFECT_ID::HIT,vec);
}

//==========================================================================================
// 左エリアアウト処理
//==========================================================================================
void IEnemyBase::AreaOutLeftProc(void)
{
	if (m_vPos.x + GetSpriteSize().x / 2 < ((cGame*)GetRoot())->GetPlayArea().left - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 上エリアアウト処理
//==========================================================================================
void IEnemyBase::AreaOutUpProc(void)
{
	if (m_vPos.y + GetSpriteSize().y / 2 < ((cGame*)GetRoot())->GetPlayArea().top - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 右エリアアウト処理
//==========================================================================================
void IEnemyBase::AreaOutRightProc(void)
{
	if (m_vPos.x - GetSpriteSize().x / 2 > ((cGame*)GetRoot())->GetPlayArea().right + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 下エリアアウト処理
//==========================================================================================
void IEnemyBase::AreaOutBottomProc(void)
{
	if (m_vPos.y - GetSpriteSize().y / 2 > ((cGame*)GetRoot())->GetPlayArea().bottom + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 全方向エリアアウト処理
//==========================================================================================
void IEnemyBase::AreaOutAllProc(void)
{
	AreaOutLeftProc();
	AreaOutUpProc();
	AreaOutRightProc();
	AreaOutBottomProc();
}