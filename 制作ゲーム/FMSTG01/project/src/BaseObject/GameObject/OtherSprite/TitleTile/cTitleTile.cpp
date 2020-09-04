/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleTile.cpp												*/
/*  @brief		:	描画オブジェクト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/26													*/
/*																				*/
/*==============================================================================*/

#include "cTitleTile.h"
#include "..\..\..\..\cGame.h"


//==========================================================================================
// 定数
//==========================================================================================
const float cTitleTile::TILE_SCALEUP = 0.1f;
const float cTitleTile::CRUMBLE_MOVE_X = 3.0f;
const float cTitleTile::CRUMBLE_START_Y = -4.0f;
const float cTitleTile::CRUMBLE_GRAVITY = 0.5f;

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTitleTile::cTitleTile(IBaseObject* parent, const std::string& objectname, const std::string& filename) :
	cSpriteObject(parent, "TitleTile", "data\\graphic\\hex.png"),
	m_bPop( false ),
	m_bCrumble( false ),
	m_vPosUp(0.0f,0.0f)
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cTitleTile::~cTitleTile(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cTitleTile::
Initialize(void)
{
	cSpriteObject::Initialize();

	SetPriority(PRIORITY);
	SetScale(0.0f);
}

//==========================================================================================
//  更新
//==========================================================================================
void cTitleTile::Update(void)
{
	if (m_bCrumble)
	{
		m_vPosUp.y += CRUMBLE_GRAVITY;
		m_bPop = false;

		// 崩落中に完全に出現していないタイルは消去する
		if( m_vScale.x <= 0.0f ) DeleteObject();
	}
	if (m_bPop)
	{
		// タイル出現中
		float scale = GetScale().x + TILE_SCALEUP;
		if (scale > 1.0f)
		{
			scale = 1.0f;
		}
		SetScale(scale);
	}

	m_vPos.x += m_vPosUp.x;
	m_vPos.y += m_vPosUp.y;

	// 画面外に出たら消える
	if (m_vPos.y - GetSpriteSize().y / 2.0f >= cGame::GetInstance().GetWindowHeight())
		DeleteObject();

	cSpriteObject::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cTitleTile::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
//==========================================================================================
//  崩落開始処理
//==========================================================================================
void cTitleTile::StartCrumble(void)
{
	m_bCrumble = true;

	// 動く方向をランダムに決める
	m_vPosUp.x = (float)cGame::Random(0,(int)CRUMBLE_MOVE_X*10) / 10.0f;
	if (cGame::Random(0, 1))
	{
		m_vPosUp.x *= -1.0f;
	}
	m_vPosUp.y = CRUMBLE_START_Y;
}