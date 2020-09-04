/*==============================================================================*/
/*																				*/
/*	@file title	:	cPause.cpp													*/
/*  @brief		:	ポーズクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/01/16													*/
/*																				*/
/*==============================================================================*/

#include "cPause.h"
#include "..\BaseObject\cSpriteObject.h"
#include "..\cGame.h"
#include "..\Utility\utility.h"


//==========================================================================================
// 定数
const float cPause::FONT_POS_X = 450.0f;
const float cPause::FONT_POS_Y = 150.0f;
const unsigned int	cPause::FONT_COLOR = 0xff77ff77;

//==========================================================================================
// 初期化
//==========================================================================================
void cPause::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "Pause";

	m_bPause = false;
	m_nPauseCount = 0;
	m_ePauseState = PAUSE_STATE_START;

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cPause::Update(void)
{
	if (m_bPause)
	{
		// ポーズ状態の変更
		if (m_nPauseCount > PAUSE_COMP_TIME)
		{
			m_ePauseState = PAUSE_STATE_WAIT;
		}

		// ポーズ状態別処理
		switch (m_ePauseState)
		{
		case PAUSE_STATE_START:
			Start();
			break;
		case PAUSE_STATE_WAIT:
			Wait();
			break;
		}

		m_nPauseCount++;

	}

	IBaseObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cPause::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// ポーズ状態の開始
//==========================================================================================
void cPause::StartPause(void)
{
	m_bPause = true;
	m_nPauseCount = 0;
	m_ePauseState = PAUSE_STATE_START;

	// 上側マスクの作成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"UpperMask","data\\graphic\\black.png");
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2.0f, -(float)cGame::GetInstance().GetWindowHeight() / 2.0f);
	obj->SetAlpha( 0 );
	obj->SetPriority(PRIORITY);

	// 下側マスクの作成
	obj = CreateDrawObject<cSpriteObject>(this, "DownerMask", "data\\graphic\\black.png");
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2.0f, (float)cGame::GetInstance().GetWindowHeight() / 2.0f + (float)cGame::GetInstance().GetWindowHeight());
	obj->SetAlpha(0);
	obj->SetPriority(PRIORITY);

	// フレームの作成
	obj = CreateDrawObject<cSpriteObject>(this, "PauseFrame", "data\\graphic\\PauseFrame.png");
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() + obj->GetSpriteSize().x / 2, (float)cGame::GetInstance().GetWindowHeight() / 2.0f );
	obj->SetAlpha(255);
	obj->SetPriority(PRIORITY+1);

	// ポーズ文字の作成
	obj = CreateDrawObject<cSpriteObject>(this, "PauseFont", "data\\graphic\\PauseFont.png");
	obj->SetPos(FONT_POS_X, FONT_POS_Y);
	obj->SetDrawColor(FONT_COLOR);
	obj->SetAlpha(0);
	obj->SetPriority(PRIORITY + 2);

}
//==========================================================================================
// ポーズ状態の終了
//==========================================================================================
void cPause::EndPause(void)
{
	m_bPause = false;

	// 子オブジェクトの破棄
	Finalize();
}
//==========================================================================================
// スタート状態の処理
//==========================================================================================
void cPause::Start(void)
{
	cSpriteObject* umask = (cSpriteObject*)FindChild("UpperMask");
	// 上側マスクの処理
	if (umask != nullptr)
	{
		float StartPos = (-(float)cGame::GetInstance().GetWindowHeight() / 2.0f);
		umask->SetPosY((float)cGame::GetInstance().GetWindowHeight() / PAUSE_COMP_TIME * m_nPauseCount + StartPos);

		umask->SetAlpha(MASK_MAX_ALPHA / PAUSE_COMP_TIME * m_nPauseCount);
	}
	// 下側マスクの処理
	cSpriteObject* dmask = (cSpriteObject*)FindChild("DownerMask");
	if (dmask != nullptr)
	{
		float StartPos = (float)cGame::GetInstance().GetWindowHeight() / 2.0f + (float)cGame::GetInstance().GetWindowHeight();
		dmask->SetPosY(-(float)cGame::GetInstance().GetWindowHeight() / PAUSE_COMP_TIME * m_nPauseCount + StartPos);

		dmask->SetAlpha(MASK_MAX_ALPHA / PAUSE_COMP_TIME * m_nPauseCount);
	}
	// フレームの処理
	cSpriteObject* frame = (cSpriteObject*)FindChild("PauseFrame");
	if (frame != nullptr)
	{
		float StartPos = (float)cGame::GetInstance().GetWindowWidth() + (float)cGame::GetInstance().GetWindowWidth() / 2.0f;
		frame->SetPosX(-((float)cGame::GetInstance().GetWindowWidth() / PAUSE_COMP_TIME * m_nPauseCount) + StartPos);
	}
}
//==========================================================================================
// 待機状態の処理
//==========================================================================================
void cPause::Wait(void)
{
	// フレームの処理
	cSpriteObject* font = (cSpriteObject*)FindChild("PauseFont");
	if (font != nullptr)
	{
		unsigned int alpha = (unsigned int)((sin(DEG_TO_RAD(m_nPauseCount)) + 1.0f ) * 127.5f) ;
		font->SetAlpha(alpha);
	}
}
