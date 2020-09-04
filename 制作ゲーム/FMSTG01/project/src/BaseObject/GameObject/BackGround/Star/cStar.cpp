/*==============================================================================*/
/*																				*/
/*	@file title	:	cStar.cpp													*/
/*  @brief		:	星オブジェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/10													*/
/*																				*/
/*==============================================================================*/

#include "cStar.h"
#include "..\..\..\..\cGame.h"
#include <math.h>
#include "..\..\..\..\Utility\utility.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cStar::cStar(IBaseObject * parent)
	: cSpriteObject(parent, "Star", "data\\graphic\\star.png"),
	m_nSaveColor(0x00000000),
	m_vPosUp(0.0f,0.0f),
	m_eStarType(TYPE_SMALL),
	m_fFlashCounter(0.0f),
	m_fColorIncrement(1.0f)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cStar::~cStar(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cStar::Initialize(void)
{
	// ランダムで星の大きさを変更する
	m_eStarType = (StarType)cGame::Random(0, StarType::TYPE_MAX-1);
	switch (m_eStarType)
	{
	case TYPE_SMALL:
		SetSrcRect(0,0,1,1);
		m_vPosUp = cVector2(0.0f,SMALL_STAR_SPEED);
		break;
	case TYPE_MIDIUM:
		SetSrcRect(0, 0, 1, 2);
		m_vPosUp = cVector2(0.0f,MIDIUM_STAR_SPEED );
		break;
	case TYPE_LARGE:
		SetSrcRect(0, 0, 1, 3);
		m_vPosUp = cVector2(0.0f,LARGE_STAR_SPEED );
		break;
	}

	// ランダムで色を変更する
	int colorType = cGame::Random(0,5);
	switch (colorType){
	case 0: m_nColor = m_nSaveColor = cSprite::COLOR_RED; break;
	case 1: m_nColor = m_nSaveColor = cSprite::COLOR_BLUE; break;
	case 2: m_nColor = m_nSaveColor = cSprite::COLOR_YELLOW; break;
	case 3: m_nColor = m_nSaveColor = cSprite::COLOR_GREEN; break;
	case 4: m_nColor = m_nSaveColor = cSprite::COLOR_PURPLE; break;
	case 5: m_nColor = m_nSaveColor = cSprite::COLOR_DEFAULT; break;
	}

	// 点滅速度をランダムで変更する
	m_fColorIncrement = ((float)cGame::Random(10,100))/10.0f;

	m_fFlashCounter = 0.0f;
	SetPriority(PRIORITY);

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cStar::Update(void)
{
	m_vPos.y += m_vPosUp.y;

	// 色の点滅処理
	FlashColor();

	// 画面外に出たら画面上部から再出現させる
	if (m_vPos.y >= cGame::GetInstance().GetPlayAreaHeight())
	{
		Initialize();
		SetPos((float)cGame::Random(0, cGame::GetInstance().GetPlayAreaWidth()), -3);
		return;
	}

	cSpriteObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cStar::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// 色の点滅処理
//==========================================================================================
void cStar::FlashColor(void)
{
	// 点滅カウンターの加算
	m_fFlashCounter += m_fColorIncrement;

	// 点滅をさせる(0～255での値を出す)
	unsigned int NowColor = (unsigned int)((sin(DEG_TO_RAD(m_fFlashCounter)) + 1.0f) * 127.5f);
	// RとGにも同様の値をコピーする
	m_nColor = NowColor | (NowColor << 8) | (NowColor << 16);
	// 元の色は維持する
	m_nColor |= m_nSaveColor;
}
