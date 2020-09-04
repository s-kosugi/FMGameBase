/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransition.cpp												*/
/*	@brief		:	トランジションクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/11													*/
/*																				*/
/*==============================================================================*/

#include "cTransition.h"
#include "..\cDrawCtrl.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// 定数
const float	cTransition::BORDER_MAX = 255;
const int	cTransition::DEFAULT_PRIORITY = 30000;

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTransition::cTransition(const std::string& filename, IDrawBase* pObj, TransDirection dir, float transtime) :
	IDrawBase(filename),
	m_pTransObj(pObj),
	m_eBorderRange(BorderRange::RANGE_64),
	m_fBorderParam(0.0f),
	m_eTransDirection(dir),
	m_fTransTime( transtime ),
	m_cTimer(nullptr,"TransTimer")
{
	// トランジション方向によって初期境界位置を変更する
	if (dir == TransDirection::TRANS_IN) m_fBorderParam = 0.0f;
	else m_fBorderParam = (float)BORDER_MAX;

	// トランジションはオブジェクト削除時にメモリからアンロードする
	m_bUnload = true;

	// タイマーのセット
	m_cTimer.Setup(m_fTransTime);

	SetPriority(DEFAULT_PRIORITY);
	// 描画情報を登録
	cDrawCtrl::GetInstance().RegistTransition(*this, filename);
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cTransition::~cTransition()
{
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
	m_cTimer.Update();
	if (m_eTransDirection == TransDirection::TRANS_IN)
	{
		m_fBorderParam = Easing::Linear(m_cTimer.GetTime(), m_cTimer.GetLimit(), BORDER_MAX, 0.0f);
	}
	else
	{
		m_fBorderParam = Easing::Linear(m_cTimer.GetTime(), m_cTimer.GetLimit(), 0.0f , BORDER_MAX);
	}
}
//==========================================================================================
//  解放
//==========================================================================================
void cTransition::Finalize(void)
{
	m_cTimer.Finalize();
}
//==========================================================================================
//  トランジションが終了したかどうか
//==========================================================================================
bool cTransition::IsEnd(void)
{
	if (m_eTransDirection == TransDirection::TRANS_IN)
	{
		if (m_fBorderParam >= BORDER_MAX) return true;
		return false;
	}
	if (m_eTransDirection == TransDirection::TRANS_OUT)
	{
		if (m_fBorderParam <= 0) return true;
		return false;
	}
	return false;
}
