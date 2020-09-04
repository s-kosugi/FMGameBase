/*==============================================================================*/
/*																				*/
/*	@file title	:	cHitObject.cpp												*/
/*  @brief		:	当たり判定オブジェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cHitObject.h"
#include "..\..\cGame.h"
#include <math.h>

#ifdef DEBUG
#include "..\..\DrawCtrl\cDrawCtrl.h"
#include "..\..\SceneManager\cSceneManager.h"
#include "..\..\DebugFunc\cDebugFunc.h"
#endif
//==========================================================================================
// コンストラクタ
//==========================================================================================
cHitObject::cHitObject(IBaseObject * parent,const std::string object_name, const std::string graphic_file_name)
	: cSpriteObject(parent, object_name, graphic_file_name),
	m_nHp( 0 ),
	m_nMaxHp( 0 ),
	m_nAtk( 0 ),
	m_eHitCate(HIT_NONE),
	m_fHitRange( 0.0f ),
	m_eState( STATE_NORMAL ),
	m_nAreaOutAdjust( 0 )
#ifdef DEBUG 
	,m_pDebugHitObj(nullptr)
#endif
{
#ifdef DEBUG
	m_pDebugHitObj = CreateDrawObject<cSpriteObject>(cSceneManager::GetInstance().FindChild("GameMain"),"HitDebug","data\\graphic\\hitdebug.png");
	// デバッグ当たり判定描画を登録
	cDrawCtrl::GetInstance().RegistDrawObject(*m_pDebugHitObj, "data\\graphic\\hitdebug.png");
#endif
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cHitObject::~cHitObject(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cHitObject::Initialize(void)
{
	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cHitObject::Update(void)
{
	cSpriteObject::Update();
#ifdef DEBUG
	if (m_pDebugHitObj != nullptr)
	{
		// 実際の当たり判定の大きさに合わせる
		m_pDebugHitObj->SetScale(1.0f / 11.0f * m_fHitRange);
		m_pDebugHitObj->SetPos(m_vPos);
		m_pDebugHitObj->SetPriority(3000);
		m_pDebugHitObj->SetAlpha(128);

		m_pDebugHitObj->SetVisible(cDebugFunc::GetInstance().GetDebugHitVisible());
	}
#endif
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cHitObject::Finalize(void)
{
	cSpriteObject::Finalize();

#ifdef DEBUG
	m_pDebugHitObj->DeleteObject();
#endif

	return this;
}

//==========================================================================================
// 当たり判定チェック
// obj : 当たり判定をするオブジェクト
// return : true 当たった  false 当たっていない
//==========================================================================================
bool cHitObject::CheckHitObject(cHitObject& obj)
{
	float length = abs(sqrt((m_vPos.x - obj.GetPos().x) * (m_vPos.x - obj.GetPos().x) + (m_vPos.y - obj.GetPos().y) * (m_vPos.y - obj.GetPos().y)));
	if (length < m_fHitRange / 2.0f + obj.GetHitRange() / 2.0f &&
		m_eState == STATE_NORMAL && obj.GetState() == STATE_NORMAL)
	{
		// ダメージ状態にする
		m_eState = STATE_HIT;
		obj.SetState( STATE_HIT );
		// ダメージ計算
		m_nHp -= obj.GetAtk();
		obj.SetHp(obj.GetHp() - m_nAtk);
		return true;
	}

	return false;
}
//==========================================================================================
// 左エリアアウト処理
//==========================================================================================
void cHitObject::AreaOutLeftProc(void)
{
	if (m_vPos.x + GetSpriteSize().x / 2 < cGame::GetInstance().GetPlayArea().left - m_nAreaOutAdjust)
	{
		m_eObjectState = OBJECT_STATE_DEAD;
	}
}

//==========================================================================================
// 上エリアアウト処理
//==========================================================================================
void cHitObject::AreaOutUpProc(void)
{
	if (m_vPos.y + GetSpriteSize().y / 2 < cGame::GetInstance().GetPlayArea().top - m_nAreaOutAdjust)
	{
		m_eObjectState = OBJECT_STATE_DEAD;
	}
}

//==========================================================================================
// 右エリアアウト処理
//==========================================================================================
void cHitObject::AreaOutRightProc(void)
{
	if (m_vPos.x - GetSpriteSize().x / 2 > cGame::GetInstance().GetPlayArea().right + m_nAreaOutAdjust)
	{
		m_eObjectState = OBJECT_STATE_DEAD;
	}
}

//==========================================================================================
// 下エリアアウト処理
//==========================================================================================
void cHitObject::AreaOutBottomProc(void)
{
	if (m_vPos.y - GetSpriteSize().y / 2 > cGame::GetInstance().GetPlayArea().bottom + m_nAreaOutAdjust)
	{
		m_eObjectState = OBJECT_STATE_DEAD;
	}
}

//==========================================================================================
// 全方向エリアアウト処理
//==========================================================================================
void cHitObject::AreaOutAllProc(void)
{
	AreaOutLeftProc();
	AreaOutUpProc();
	AreaOutRightProc();
	AreaOutBottomProc();
}
