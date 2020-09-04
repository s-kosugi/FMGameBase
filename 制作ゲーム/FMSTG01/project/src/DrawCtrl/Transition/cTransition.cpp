/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransition.cpp												*/
/*  @brief		:	トランジションラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/11													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include "cTransition.h"
#include "..\cDrawCtrl.h"

//==========================================================================================
// 定数
const float cTransition::BORDER_ADD_DEFAULT = 4.0f;
const int	cTransition::BORDER_MAX = 255;
const int	cTransition::DEFAULT_PRIORITY = 30000;

const std::string cTransition::RULE_CHECKSPHERE = "data\\graphic\\rule01.png";
//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTransition::cTransition(const std::string& filename,IDrawBase* pObj) :
	IDrawBase(filename),
	m_pTransObj(pObj),
	m_eBorderRange(RANGE_64),
	m_fBorderParam(0.0f),
	m_fBorderParam_Add(BORDER_ADD_DEFAULT),
	m_eTransDirection(TRANS_IN)
{
	// トランジションはオブジェクト削除時にメモリからアンロードする
	m_bUnload = true;

	SetPriority(DEFAULT_PRIORITY);
	// 描画情報を登録
	cDrawCtrl::GetInstance().RegistTransition(*this, filename);
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cTransition::~cTransition()
{
	cDrawCtrl::GetInstance().RemoveDrawObject(this);
}
//==========================================================================================
//  初期化
//==========================================================================================
void cTransition::Initialize(void)
{
}
//==========================================================================================
//  更新
//==========================================================================================
void cTransition::Update(void)
{
	if (m_eTransDirection == TRANS_IN)
	{
		// 境界位置を更新
		m_fBorderParam += m_fBorderParam_Add;
		if (m_fBorderParam >= BORDER_MAX)
		{
			m_fBorderParam = (float)BORDER_MAX;
		}
	}
	else
	{
		// TRANS_OUT
		// 境界位置を更新
		m_fBorderParam -= m_fBorderParam_Add;
		if (m_fBorderParam <= 0)
		{
			m_fBorderParam = 0.0f;
		}
	}
}
//==========================================================================================
//  解放
//==========================================================================================
void cTransition::Finalize(void)
{
}
//==========================================================================================
//  トランジションが終了したかどうか
//==========================================================================================
bool cTransition::IsEnd(void)
{
	if (m_eTransDirection == TRANS_IN)
	{
		if (m_fBorderParam >= BORDER_MAX) return true;
		return false;
	}
	if (m_eTransDirection == TRANS_OUT)
	{
		if (m_fBorderParam <= 0) return true;
		return false;
	}
	return false;
}
