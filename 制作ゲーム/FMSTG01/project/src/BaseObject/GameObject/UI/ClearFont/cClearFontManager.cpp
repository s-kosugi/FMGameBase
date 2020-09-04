/*==============================================================================*/
/*																				*/
/*	@file title	:	cClearFontManager.cpp										*/
/*  @brief		:	�N���A�t�H���g�Ǘ�											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/30													*/
/*																				*/
/*==============================================================================*/

#include "cClearFontManager.h"
#include "..\cUIManager.h"
#include "..\Number\TimeBonusNumber\cTimeBonusNumber.h"
#include "..\..\..\..\SceneManager\cSceneManager.h"
#include "..\..\..\..\ScoreManager\cScoreManager.h"
#include "..\..\..\..\SoundCtrl\cSoundCtrl.h"

//==========================================================================================
//  �萔
//==========================================================================================
const float		cClearFontManager::CLEARFONT_POS_X = 300.0f;
const float		cClearFontManager::CLEARFONT_POS_Y = 100.0f;
const float		cClearFontManager::TIMEBONUSFONT_POS_X = 300.0f;
const float		cClearFontManager::TIMEBONUSFONT_POS_Y = 220.0f;
const float		cClearFontManager::SCOREFONT_POS_X = 300.0f;
const float		cClearFontManager::SCOREFONT_POS_Y = 440.0f;

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cClearFontManager::cClearFontManager(IBaseObject* parent) :
	cUIObject(parent, "ClearFontManager", "data\\graphic\\GameClear.png"),
	m_nCounter(0),
	m_eState(STATE_FONT_POP)
{
}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cClearFontManager::~cClearFontManager(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cClearFontManager::
Initialize(void)
{
	// �}�l�[�W���[�{�͕̂\�����Ȃ�
	m_bVisible = false;

	IBaseObject::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cClearFontManager::Update(void)
{

	switch (m_eState)
	{
	case STATE_FONT_POP:
		Pop();
		break;
	case STATE_TIMEBONUS_POP:
		TimeBonusPop();
		break;
	case STATE_BONUS_RANDSHOW:
		BonusRandShow();
		break;
	case STATE_COMP_WAIT:
		CompWait();
		break;
	case STATE_SCORE_POP:
		ScorePop();
		break;
	}
	IBaseObject::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cClearFontManager::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}
//==========================================================================================
//  �N���A�t�H���g�o��
//==========================================================================================
void cClearFontManager::Pop(void)
{

	if (m_nCounter == 0)
	{
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"ClearFont","data\\graphic\\GameClear.png");
		m_ClearFontRect = obj->GetSrcRect();
		obj->SetSrcRect(0,obj->GetSpriteSize().y,obj->GetSpriteSize().x,0);
		obj->SetPos(CLEARFONT_POS_X, CLEARFONT_POS_Y);
		obj->SetPriority(1000);
		obj->SetDrawColor(0xffaaaaff);
	}

	// RECT�������ď������o��������
	cSpriteObject* clearfont = (cSpriteObject*)FindChild("ClearFont");
	if (nullptr != clearfont)
	{
		RECT rect = clearfont->GetSrcRect();
		if (rect.top > m_ClearFontRect.top)
		{
			rect.top--;
			clearfont->SetSrcRect(rect);
		}
		else
		{
			rect.top = 0;
			// �o�����������玟�̃X�e�[�^�X��
			m_eState = STATE_TIMEBONUS_POP;
			m_nCounter = 0;
			return;
		}
	}

	m_nCounter++;

}
//==========================================================================================
//  �^�C���{�[�i�X�o��
//==========================================================================================
void cClearFontManager::TimeBonusPop(void)
{
	if (m_nCounter == 0)
	{
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "TimeBonus", "data\\graphic\\TimeBonusFont.png");
		m_ClearFontRect = obj->GetSrcRect();
		obj->SetSrcRect(0, obj->GetSpriteSize().y, obj->GetSpriteSize().x, 0);
		obj->SetPos(TIMEBONUSFONT_POS_X, TIMEBONUSFONT_POS_Y);
		obj->SetPriority(1000);
	}

	// RECT�������ď������o��������
	cSpriteObject* clearfont = (cSpriteObject*)FindChild("TimeBonus");
	if (nullptr != clearfont)
	{
		RECT rect = clearfont->GetSrcRect();
		if (rect.top > m_ClearFontRect.top)
		{
			rect.top--;
			clearfont->SetSrcRect(rect);
		} else
		{
			rect.top = 0;
			// �o�����������玟�̃X�e�[�^�X��
			m_eState = STATE_BONUS_RANDSHOW;
			m_nCounter = 0;

			cTimeBonusNumber* number = (cTimeBonusNumber*)cUIManager::GetInstance().Create(UI_TIMEBONUS_NUMBER, cVector2 (715.0f, 330.0f));
			number->CreateNumber(7, 18974);
			number->SetGoalValue(cScoreManager::GetInstance().GetTimeBonus());
			return;
		}
	}
	m_nCounter++;
}
//==========================================================================================
//  �����_���Ƀ{�[�i�X�\����ҋ@
//==========================================================================================
void cClearFontManager::BonusRandShow(void)
{
	cTimeBonusNumber* num = (cTimeBonusNumber*)FindSibling("TimeBonusNumber");

	if (num != nullptr)
	{
		if (num->IsGoal()){
			m_eState = STATE_COMP_WAIT;
			// �X�R�A�{�[�i�X�����Z
			cScoreManager::GetInstance().AddScore(cScoreManager::GetInstance().GetTimeBonus());

			cSoundCtrl::GetInstance().Play(SOUND_DIGI);

			m_nCounter=0;
			return;
		}
	}
	else
	{
		m_eState = STATE_COMP_WAIT;
	}
	if( m_nCounter % 10 == 0) cSoundCtrl::GetInstance().Play(SOUND_PI);
	m_nCounter++;
}
//==========================================================================================
//  �o�����I�������̑ҋ@����
//==========================================================================================
void cClearFontManager::CompWait(void)
{
	if (COMP_WAIT_TIME < m_nCounter)
	{
		cSceneManager::GetInstance().ChangeScene(SCENE_ID_TITLE);
	}
	m_nCounter++;

}
//==========================================================================================
//  �X�R�A�o��
//==========================================================================================
void cClearFontManager::ScorePop(void)
{
	if (m_nCounter == 0)
	{
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "ClearScore", "data\\graphic\\ClearScore.png");
		m_ClearFontRect = obj->GetSrcRect();
		obj->SetSrcRect(0, obj->GetSpriteSize().y, obj->GetSpriteSize().x, 0);
		obj->SetPos(SCOREFONT_POS_X, SCOREFONT_POS_Y);
		obj->SetPriority(1000);
	}

	// RECT�������ď������o��������
	cSpriteObject* clearfont = (cSpriteObject*)FindChild("ClearScore");
	if (nullptr != clearfont)
	{
		RECT rect = clearfont->GetSrcRect();
		if (rect.top > m_ClearFontRect.top)
		{
			rect.top--;
			clearfont->SetSrcRect(rect);
		} else
		{
			rect.top = 0;
			// �o�����������玟�̃X�e�[�^�X��
		}
	}
	m_nCounter++;
}
