/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffekseerTest.cpp											*/
/*  @brief		:	�G�t�F�N�V�A�e�X�g�V�[��									*/
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
//  �R���X�g���N�^
//==========================================================================================
cEffekseerTest::cEffekseerTest(IBaseObject * parent)
	: IBaseScene(parent, "EffekseerTest")
	, m_ePlayEffectID( EFFECT_ID::MIN)
	, m_fPlayScale( 1.0f )
{
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cEffekseerTest::~cEffekseerTest(void)
{
}
//==========================================================================================
//  ������
//==========================================================================================
void cEffekseerTest::Initialize(void)
{
	// �V�[���^�C�g���\��
	cTextObject* title = CreateTextObject<cTextObject>(this,"titletext","EffekseerTest");
	title->SetPos(20.0f, 32.0f);

	// �Đ������e�L�X�g
	cTextObject* playInfo = CreateTextObject<cTextObject>(this, "playInfoText", "Z : EffectPlay");
	playInfo->SetPos(60.0f, 48.0f);

	// �G�t�F�N�gID�\��
	cTextObject* effectID = CreateTextObject<cTextObject>(this, "effectIDtext", "EffectID = ");
	effectID->SetPos(20.0f, 96.0f);
	effectID->SetDrawColor(IDrawBase::COLOR_YELLOW);

	// ID�����e�L�X�g
	cTextObject* idInfo = CreateTextObject<cTextObject>(this, "idInfoText", "�� : PrevID\n�� : NextID");
	idInfo->SetPos(60.0f, 108.0f);

	// �G�t�F�N�g�g�嗦�\��
	cTextObject* effectScale = CreateTextObject<cTextObject>(this,"effectScaleText","Scale = ");
	effectScale->SetPos(20.0f,148.0f);
	effectScale->SetDrawColor(IDrawBase::COLOR_YELLOW);

	// �g�嗦�����e�L�X�g
	cTextObject* scaleInfo = CreateTextObject<cTextObject>(this, "scaleInfoText", "I : ScaleUp\nO : ScaleDown\nU : ScaleReset ");
	scaleInfo->SetPos(60.0f, 164.0f);


	m_vPlayPos = cGame::GetInstance().GetWindowCenter();

	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cEffekseerTest::Update(void)
{
	cKeyboard& key = cKeyboard::GetInstance();

	//-------------------------------------------------------------------
	// �|�[�Y
	if (key.CheckTrigger(KEY_INPUT_P))
	{
		Push(SCENE_ID::PAUSE);
	}

	//-------------------------------------------------------------------
	// �G�t�F�N�gID�؂�ւ�
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
	// �G�t�F�N�gID������ύX����
	cTextObject* idtext = (cTextObject*)FindChild("effectIDtext");
	if (idtext)
	{
		std::string str = "EffectID = ";
		str += std::to_string((int)m_ePlayEffectID);
		idtext->SetText(str);
	}
	//-------------------------------------------------------------------
	// �G�t�F�N�g�g�嗦�ύX
	if (key.CheckButton(KEY_INPUT_I)) m_fPlayScale += 0.01f;
	if (key.CheckButton(KEY_INPUT_O)) m_fPlayScale -= 0.01f;
	// �G�t�F�N�g�g�嗦���Z�b�g
	if (key.CheckTrigger(KEY_INPUT_U)) m_fPlayScale = 1.0f;
	// �G�t�F�N�g�g�嗦������ύX����
	cTextObject* scaletext = (cTextObject*)FindChild("effectScaleText");
	if (scaletext)
	{
		std::string str = "Scale = ";
		str += std::to_string(m_fPlayScale);
		scaletext->SetText(str);
	}

	//-------------------------------------------------------------------
	// �G�t�F�N�g�Đ�
	if (key.CheckTrigger(KEY_INPUT_Z))
	{
		cEffectObject* effect = cEffectManager::GetInstance().Create(m_ePlayEffectID, m_vPlayPos);
		effect->SetScale(m_fPlayScale);
	}

	//-------------------------------------------------------------------
	// �V�[���J��
	if (key.CheckTrigger(KEY_INPUT_RETURN))
	{
		// �^�C�g���V�[����
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeScene(SCENE_ID::TITLE);
	}

	IBaseObject::Update();
}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cEffekseerTest::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
