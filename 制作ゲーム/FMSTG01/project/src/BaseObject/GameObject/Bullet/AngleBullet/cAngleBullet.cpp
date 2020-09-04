/*==============================================================================*/
/*																				*/
/*	@file title	:	cAngleBullet.cpp											*/
/*  @brief		:	角度指定弾クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "cAngleBullet.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\Effect\cEffectObject.h"

//==========================================================================================
// 定数
//==========================================================================================
const float cAngleBullet::HIT_RANGE = 12.0f;	// 当たり判定
const int	cAngleBullet::DEFAULT_ATK = 50;		// 標準攻撃力
const int	cAngleBullet::PRIORITY = 300;		// 表示優先

//==========================================================================================
// コンストラクタ
//==========================================================================================
cAngleBullet::cAngleBullet(IBaseObject * parent)
	: cBulletBase(parent, "AngleBullet", "data\\graphic\\Bullet_01.png")
{
}

cAngleBullet::cAngleBullet(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cBulletBase(parent, "AngleBullet",filename)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cAngleBullet::~cAngleBullet(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cAngleBullet::Initialize(void)
{
	cGame game = cGame::GetInstance();

	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;


	SetPriority(PRIORITY);

	cBulletBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cAngleBullet::Update(void)
{
	// 当たった弾は消える
	HitProc();

	// エリアアウトをしたら弾を消す
	AreaOutAllProc();

	cBulletBase::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cAngleBullet::Finalize(void)
{
	cBulletBase::Finalize();

	return this;
}

//==========================================================================================
// 発射角度のセット
// angle : 度数法の角度,0度が真下
//==========================================================================================
void cAngleBullet::SetShootAngle(float angle)
{
	angle += 90.0f;
	m_vPosUp.x = m_fSpeed * cos( DEG_TO_RAD(angle) );
	m_vPosUp.y = m_fSpeed * sin( DEG_TO_RAD(angle) );
}