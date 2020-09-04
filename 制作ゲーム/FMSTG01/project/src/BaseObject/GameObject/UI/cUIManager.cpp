/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIManager.cpp												*/
/*  @brief		:	UI管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "cUIManager.h"
#include "UIWindow\cUIWindow.h"
#include "HPGauge\cHPGauge.h"
#include "HPGaugeBefore\cHPGaugeBefore.h"
#include "HPGaugeFrame\cHPGaugeFrame.h"
#include "Number\HPNumber\cHpNumber.h"
#include "BomStock\cBomStock.h"
#include "Number\ScoreNumber\cScoreNumber.h"
#include "ClearFont\cClearFontManager.h"
#include "Number\TimeBonusNumber\cTimeBonusNumber.h"

//==========================================================================================
// 初期化
//==========================================================================================
void cUIManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "UIManager";

	IBaseObject::Initialize();

	// ウィンドウの生成
	Create(UI_WINDOW,{700,300});

	// HPゲージ
	Create(UI_HPGAUGE, { 700,250 });
	Create(UI_HPGAUGE_BEFORE, { 700,250 });
	Create(UI_HPGAUGE_FRAME, { 700,250 });

	cHpNumber* num = (cHpNumber*)Create(UI_HP_NUMBER, { 818,251 });
	num->CreateNumber(4,123);

	Create(UI_BOMSTOCK,{700,450});

	// スコア数字の表示
	cScoreNumber* score = (cScoreNumber*)Create(UI_SCORE_NUMBER, { 860,77 });
	score->CreateNumber(8,0);

}

//==========================================================================================
// 更新
//==========================================================================================
void cUIManager::Update(void)
{
	IBaseObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cUIManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// 生成
//==========================================================================================
cUIObject* cUIManager::Create(UIID id, cVector2 pos)
{
	cUIObject* obj = nullptr;
	switch (id)
	{
	case UI_WINDOW: obj = CreateObject<cUIWindow>(this); break;
	case UI_HPGAUGE: obj = CreateObject<cHPGauge>(this); break;
	case UI_HPGAUGE_BEFORE: obj = CreateObject<cHPGaugeBefore>(this); break;
	case UI_HPGAUGE_FRAME: obj = CreateObject<cHPGaugeFrame>(this); break;
	case UI_HP_NUMBER: obj = CreateObject<cHpNumber>(this); break;
	case UI_BOMSTOCK: obj = CreateObject<cBomStock>(this); break;
	case UI_SCORE_NUMBER: obj = CreateObject<cScoreNumber>(this); break;
	case UI_GAMECLEAR_FONT: obj = CreateObject<cClearFontManager>(this); break;
	case UI_TIMEBONUS_NUMBER: obj = CreateObject<cTimeBonusNumber>(this); break;
	}

	if (obj != nullptr)
	{
		obj->Initialize();
		obj->SetPos(pos);
	}
	return obj;
}
