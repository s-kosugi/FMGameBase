/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.cpp											*/
/*  @brief		:	敵管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cEnemyManager.h"
#include "..\..\..\SceneManager\cSceneManager.h"
#include "..\..\..\ScoreManager\cScoreManager.h"
#include "..\..\..\SceneManager\Scene\GameMain\cGameMain.h"
#include "RedFairy/cRedFairy.h"
#include "BlueFairy/cBlueFairy.h"

//==========================================================================================
// 定数
//==========================================================================================
const int cEnemyManager::DEFAULT_POP_INTERVAL = 120;  // 初期出現間隔
const int cEnemyManager::DIFFICULT_POP_RATE = 10;	  // 難易度による敵の出現頻度の倍率

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnemyManager::cEnemyManager( IBaseObject* pObj )
	:IBaseObject( pObj , "EnemyManager")
	, m_nTimer( 0 )
{
}
//==========================================================================================
// デストラクタ
//==========================================================================================
cEnemyManager::~cEnemyManager( void )
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnemyManager::Initialize(void)
{
	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cEnemyManager::Update(void)
{
	m_nTimer++;
	if(GetParent()->GetObjectName() == "GameMain")
	{
		// 難易度によって敵の出現頻度を変更する
		cGameMain* gm = (cGameMain*)GetParent();
		if( m_nTimer % (DEFAULT_POP_INTERVAL - gm->GetDifficult() * DIFFICULT_POP_RATE) == 0)
			Create( (EnemyID)(rand() % (int)EnemyID::MAX) );
	}
	

	IBaseObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cEnemyManager::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
// 敵生成
// return : 生成した敵のポインタ 生成されなかった場合はnullptr
//==========================================================================================
IEnemyBase* cEnemyManager::Create(EnemyID id)
{
	IEnemyBase* pObj = nullptr;
	switch (id)
	{
	case EnemyID::RED_FAIRY:
		pObj = CreateObject<cRedFairy>(this);
		pObj->Initialize();
		break;
	case EnemyID::BLUE_FAIRY:
		pObj = CreateObject<cBlueFairy>(this);
		pObj->Initialize();
		break;
	}

	return pObj;
}

//==========================================================================================
// 当たり判定
// vec 当たり判定をするオブジェクトの位置
// dist 当たり判定をするオブジェクトの半径
// return true プレイヤーの攻撃が当たった false プレイヤーの攻撃があたらなかった
//==========================================================================================
bool cEnemyManager::JudgeHit( const cVector2 & vec, float dist )
{
	for( auto it = m_listChildObject.begin(); it != m_listChildObject.end(); it++ )
	{
		IEnemyBase* enm = (IEnemyBase*)(*it);
		if( dist + enm->GetDist() > enm->GetPos().CalcTwoPointDist(vec) )
		{
			// 攻撃が当たったので敵を死亡状態にする
			enm->Dead();

			// スコアを加算する
			cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild( "ScoreManager" );
			if( sm ) sm->AddScore( 1 );
			return true;
		}
	}
	return false;
}

//==========================================================================================
// プレイヤーとの当たり判定
// vec プレイヤーの位置
// dist プレイヤーの当たり判定半径
// return true プレイヤーが敵の攻撃の範囲内 false プレイヤーが敵の攻撃の範囲外
//==========================================================================================
bool cEnemyManager::JudgePlayer( const cVector2 & vec, float dist )
{
	for( auto it = m_listChildObject.begin(); it != m_listChildObject.end(); it++ )
	{
		IEnemyBase* enm = (IEnemyBase*)(*it);
		if( dist + enm->GetDist() > enm->GetPos().CalcTwoPointDist(vec) )
		{
			// 該当の敵を攻撃状態にする
			enm->StartAttack();
			return true;
		}
	}
	return false;
}
