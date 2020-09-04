/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletBase.cpp												*/
/*  @brief		:	弾ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "cBulletBase.h"
#include "..\..\..\cGame.h"
#include "..\Effect\cEffectManager.h"
#include "..\Effect\cEffectObject.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cBulletBase::cBulletBase(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cHitObject(parent, object_name, graphic_file_name), m_fSpeed(0.0f), m_vPosUp(0.0f,0.0f)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cBulletBase::~cBulletBase(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cBulletBase::Initialize(void)
{

	cHitObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cBulletBase::Update(void)
{
	// 移動後の回転処理
	RotateMoveAfter();

	m_vPos.x += m_vPosUp.x;
	m_vPos.y += m_vPosUp.y;

	cHitObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cBulletBase::Finalize(void)
{
	cHitObject::Finalize();

	return this;
}

//==========================================================================================
// 弾が当たった時の処理
//==========================================================================================
void cBulletBase::HitProc(void)
{
	// 当たった弾は消える
	if (m_eState == STATE_HIT)
	{
		// ヒットエフェクトを出す
		cEffectObject* obj = cEffectManager::GetInstance().Create(EFFECT_HIT, m_vPos);
		obj->SetDrawColor(m_nColor);
		m_eState = STATE_DEAD;
		m_eObjectState = OBJECT_STATE_DEAD;
	}
}

//==========================================================================================
// 移動後のスプライト回転処理
//==========================================================================================
void cBulletBase::RotateMoveAfter(void)
{
	cVector2 afterPos;		// 移動後座標
	afterPos = m_vPos + m_vPosUp;

	// 移動前と移動後の座標から表示角度を求める
	m_fAngle = m_vPos.CalcTwoPointAngle(afterPos) + 90.0f;
}