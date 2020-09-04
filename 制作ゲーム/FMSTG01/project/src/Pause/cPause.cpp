/*==============================================================================*/
/*																				*/
/*	@file title	:	cPause.cpp													*/
/*  @brief		:	�|�[�Y�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/01/16													*/
/*																				*/
/*==============================================================================*/

#include "cPause.h"
#include "..\BaseObject\cSpriteObject.h"
#include "..\cGame.h"
#include "..\Utility\utility.h"


//==========================================================================================
// �萔
const float cPause::FONT_POS_X = 450.0f;
const float cPause::FONT_POS_Y = 150.0f;
const unsigned int	cPause::FONT_COLOR = 0xff77ff77;

//==========================================================================================
// ������
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
// �X�V
//==========================================================================================
void cPause::Update(void)
{
	if (m_bPause)
	{
		// �|�[�Y��Ԃ̕ύX
		if (m_nPauseCount > PAUSE_COMP_TIME)
		{
			m_ePauseState = PAUSE_STATE_WAIT;
		}

		// �|�[�Y��ԕʏ���
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
// �j��
//==========================================================================================
IBaseObject * cPause::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// �|�[�Y��Ԃ̊J�n
//==========================================================================================
void cPause::StartPause(void)
{
	m_bPause = true;
	m_nPauseCount = 0;
	m_ePauseState = PAUSE_STATE_START;

	// �㑤�}�X�N�̍쐬
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"UpperMask","data\\graphic\\black.png");
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2.0f, -(float)cGame::GetInstance().GetWindowHeight() / 2.0f);
	obj->SetAlpha( 0 );
	obj->SetPriority(PRIORITY);

	// �����}�X�N�̍쐬
	obj = CreateDrawObject<cSpriteObject>(this, "DownerMask", "data\\graphic\\black.png");
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2.0f, (float)cGame::GetInstance().GetWindowHeight() / 2.0f + (float)cGame::GetInstance().GetWindowHeight());
	obj->SetAlpha(0);
	obj->SetPriority(PRIORITY);

	// �t���[���̍쐬
	obj = CreateDrawObject<cSpriteObject>(this, "PauseFrame", "data\\graphic\\PauseFrame.png");
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() + obj->GetSpriteSize().x / 2, (float)cGame::GetInstance().GetWindowHeight() / 2.0f );
	obj->SetAlpha(255);
	obj->SetPriority(PRIORITY+1);

	// �|�[�Y�����̍쐬
	obj = CreateDrawObject<cSpriteObject>(this, "PauseFont", "data\\graphic\\PauseFont.png");
	obj->SetPos(FONT_POS_X, FONT_POS_Y);
	obj->SetDrawColor(FONT_COLOR);
	obj->SetAlpha(0);
	obj->SetPriority(PRIORITY + 2);

}
//==========================================================================================
// �|�[�Y��Ԃ̏I��
//==========================================================================================
void cPause::EndPause(void)
{
	m_bPause = false;

	// �q�I�u�W�F�N�g�̔j��
	Finalize();
}
//==========================================================================================
// �X�^�[�g��Ԃ̏���
//==========================================================================================
void cPause::Start(void)
{
	cSpriteObject* umask = (cSpriteObject*)FindChild("UpperMask");
	// �㑤�}�X�N�̏���
	if (umask != nullptr)
	{
		float StartPos = (-(float)cGame::GetInstance().GetWindowHeight() / 2.0f);
		umask->SetPosY((float)cGame::GetInstance().GetWindowHeight() / PAUSE_COMP_TIME * m_nPauseCount + StartPos);

		umask->SetAlpha(MASK_MAX_ALPHA / PAUSE_COMP_TIME * m_nPauseCount);
	}
	// �����}�X�N�̏���
	cSpriteObject* dmask = (cSpriteObject*)FindChild("DownerMask");
	if (dmask != nullptr)
	{
		float StartPos = (float)cGame::GetInstance().GetWindowHeight() / 2.0f + (float)cGame::GetInstance().GetWindowHeight();
		dmask->SetPosY(-(float)cGame::GetInstance().GetWindowHeight() / PAUSE_COMP_TIME * m_nPauseCount + StartPos);

		dmask->SetAlpha(MASK_MAX_ALPHA / PAUSE_COMP_TIME * m_nPauseCount);
	}
	// �t���[���̏���
	cSpriteObject* frame = (cSpriteObject*)FindChild("PauseFrame");
	if (frame != nullptr)
	{
		float StartPos = (float)cGame::GetInstance().GetWindowWidth() + (float)cGame::GetInstance().GetWindowWidth() / 2.0f;
		frame->SetPosX(-((float)cGame::GetInstance().GetWindowWidth() / PAUSE_COMP_TIME * m_nPauseCount) + StartPos);
	}
}
//==========================================================================================
// �ҋ@��Ԃ̏���
//==========================================================================================
void cPause::Wait(void)
{
	// �t���[���̏���
	cSpriteObject* font = (cSpriteObject*)FindChild("PauseFont");
	if (font != nullptr)
	{
		unsigned int alpha = (unsigned int)((sin(DEG_TO_RAD(m_nPauseCount)) + 1.0f ) * 127.5f) ;
		font->SetAlpha(alpha);
	}
}
