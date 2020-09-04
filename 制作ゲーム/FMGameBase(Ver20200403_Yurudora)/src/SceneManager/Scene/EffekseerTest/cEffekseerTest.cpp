/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffekseerTest.cpp											*/
/*  @brief		:	エフェクシアテストシーン									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/01/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cEffekseerTest.h"
#include "..\..\cSceneManager.h"
#include "..\..\..\Input\Keyboard\cKeyboard.h"
#include "BaseObject/TextObject/cTextObject.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"
#include "BaseObject/GameObject/Effect/cEffectObject.h"
#include <DxLib.h>
#include <string>

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cEffekseerTest::cEffekseerTest(IBaseObject * parent)
	: IBaseScene(parent, "EffekseerTest")
	, m_ePlayEffectID( EFFECT_ID::MIN)
	, m_fPlayScale( 1.0f )
{
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cEffekseerTest::~cEffekseerTest(void)
{
}
//==========================================================================================
//  初期化
//==========================================================================================
void cEffekseerTest::Initialize(void)
{
	// シーンタイトル表示
	cTextObject* title = CreateTextObject<cTextObject>(this,"titletext","EffekseerTest");
	title->SetPos(20.0f, 32.0f);

	// 再生説明テキスト
	cTextObject* playInfo = CreateTextObject<cTextObject>(this, "playInfoText", "Z : EffectPlay");
	playInfo->SetPos(60.0f, 48.0f);

	// エフェクトID表示
	cTextObject* effectID = CreateTextObject<cTextObject>(this, "effectIDtext", "EffectID = ");
	effectID->SetPos(20.0f, 96.0f);
	effectID->SetDrawColor(IDrawBase::COLOR_YELLOW);

	// ID説明テキスト
	cTextObject* idInfo = CreateTextObject<cTextObject>(this, "idInfoText", "← : PrevID\n→ : NextID");
	idInfo->SetPos(60.0f, 108.0f);

	// エフェクト拡大率表示
	cTextObject* effectScale = CreateTextObject<cTextObject>(this,"effectScaleText","Scale = ");
	effectScale->SetPos(20.0f,148.0f);
	effectScale->SetDrawColor(IDrawBase::COLOR_YELLOW);

	// 拡大率説明テキスト
	cTextObject* scaleInfo = CreateTextObject<cTextObject>(this, "scaleInfoText", "I : ScaleUp\nO : ScaleDown\nU : ScaleReset ");
	scaleInfo->SetPos(60.0f, 164.0f);


	m_vPlayPos = cGame::GetInstance().GetWindowCenter();

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cEffekseerTest::Update(void)
{
	cKeyboard& key = cKeyboard::GetInstance();

	//-------------------------------------------------------------------
	// ポーズ
	if (key.CheckTrigger(KEY_INPUT_P))
	{
		Push(SCENE_ID::PAUSE);
	}

	//-------------------------------------------------------------------
	// エフェクトID切り替え
	if (key.CheckTrigger(KEY_INPUT_LEFT))
	{
		m_ePlayEffectID = (EFFECT_ID)((int)m_ePlayEffectID-1 );
		if (m_ePlayEffectID < EFFECT_ID::MIN)
		{
			m_ePlayEffectID = (EFFECT_ID)((int)EFFECT_ID::MAX - 1);
		}

	}
	if (key.CheckTrigger(KEY_INPUT_RIGHT))
	{
		m_ePlayEffectID = (EFFECT_ID)((int)m_ePlayEffectID + 1);
		if (m_ePlayEffectID >= EFFECT_ID::MAX)
		{
			m_ePlayEffectID = EFFECT_ID::MIN;
		}

	}
	// エフェクトID文字を変更する
	cTextObject* idtext = (cTextObject*)FindChild("effectIDtext");
	if (idtext)
	{
		std::string str = "EffectID = ";
		str += std::to_string((int)m_ePlayEffectID);
		idtext->SetText(str);
	}
	//-------------------------------------------------------------------
	// エフェクト拡大率変更
	if (key.CheckButton(KEY_INPUT_I)) m_fPlayScale += 0.01f;
	if (key.CheckButton(KEY_INPUT_O)) m_fPlayScale -= 0.01f;
	// エフェクト拡大率リセット
	if (key.CheckTrigger(KEY_INPUT_U)) m_fPlayScale = 1.0f;
	// エフェクト拡大率文字を変更する
	cTextObject* scaletext = (cTextObject*)FindChild("effectScaleText");
	if (scaletext)
	{
		std::string str = "Scale = ";
		str += std::to_string(m_fPlayScale);
		scaletext->SetText(str);
	}

	//-------------------------------------------------------------------
	// エフェクト再生
	if (key.CheckTrigger(KEY_INPUT_Z))
	{
		cEffectObject* effect = cEffectManager::GetInstance().Create(m_ePlayEffectID, m_vPlayPos);
		effect->SetScale(m_fPlayScale);
	}

	//-------------------------------------------------------------------
	// シーン遷移
	if (key.CheckTrigger(KEY_INPUT_RETURN))
	{
		// タイトルシーンへ
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeScene(SCENE_ID::TITLE);
	}

	IBaseObject::Update();
}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cEffekseerTest::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
