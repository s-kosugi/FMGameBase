/*==============================================================================*/
/*																				*/
/*	@file title	:	cBlueFairyDead.cpp											*/
/*  @brief		:	青妖精死亡エフェクトクラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "cBlueFairyDead.h"
#include "Utility/Easing/Easing.h"
#include "Utility/Timer/cTimer.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cBlueFairyDead::PRIORITY = 400;			// 表示優先度
const float cBlueFairyDead::LIFE_TIME = 1.0f;		// 表示時間
const float cBlueFairyDead::MAX_SPEED = 0.0f;		// 最大移動速度
const float cBlueFairyDead::MIN_SPEED = -5.0f;		// 最小移動速度
const float cBlueFairyDead::FLASH_INTERVAL = 0.08f;	// 点滅間隔

//==========================================================================================
// コンストラクタ
//==========================================================================================
cBlueFairyDead::cBlueFairyDead( IBaseObject* parent )
	: cSpriteObject( parent, "RedFairyDead1", "data\\graphic\\enemy_02_dead1.png" )
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cBlueFairyDead::~cBlueFairyDead( void )
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cBlueFairyDead::Initialize( const cVector2& pos )
{
	SetPriority( PRIORITY );

	// 座標を設定
	m_vPos = pos;

	cTimer* timer = CreateObject<cTimer>( this, "VanishTimer" );
	timer->Setup( LIFE_TIME );

	// もう片方の半身を別スプライトで作成する
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>( this, "RedFairyDead2", "data\\graphic\\enemy_02_dead2.png" );
	obj->SetPos( pos );

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cBlueFairyDead::Update( void )
{
	cTimer* timer = (cTimer*)FindChild( "VanishTimer" );
	if( timer )
	{
		cSpriteObject* child = (cSpriteObject*)FindChild( "RedFairyDead2" );

		m_vPosUp.x = m_vPosUp.y = Easing::OutQuad( timer->GetTime(), timer->GetLimit(), MAX_SPEED, MIN_SPEED );

		// 点滅処理 タイマーを整数時間に置き換えて計算
		SetVisible( int( timer->GetTime() * 100.0f ) % (int)( FLASH_INTERVAL * 100 ) <= FLASH_INTERVAL * 100 / 2.0f ? true : false );

		// もう片方の半身は逆向きに移動させる
		if( child )
		{
			child->SetPos( child->GetPos() - m_vPosUp );
			child->SetVisible( m_bVisible );
		}
		// 時間経過したらオブジェクトを削除する
		if( timer->Finished() )
		{
			DeleteObject();
		}
	}
	m_vPos += m_vPosUp;

	cSpriteObject::Update();
}