/*==============================================================================*/
/*																				*/
/*	@file title	:	cDebugFunc.cpp												*/
/*  @brief		:	�f�o�b�O�@�\�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/24													*/
/*																				*/
/*==============================================================================*/

#include <string>
#include "cDebugFunc.h"
#include "..\cGame.h"
#include "..\Input\Keyboard\cKeyboard.h"
#include "..\SceneManager\cSceneManager.h"
#include "..\Input\cControllerManager.h"

//==========================================================================================
// �萔
//==========================================================================================
const int cDebugFunc::FPS_MODE_MAX = 5;
const int cDebugFunc::FONT_SIZE = 15;

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cDebugFunc::~cDebugFunc()
{
}

//==========================================================================================
//  ������
//==========================================================================================
void cDebugFunc::Initialize(void)
{
	m_nStartTime = GetNowCount();
	m_nFrameCount = 0;
	m_fFrameLate = 0.0f;

	m_listLog.clear();
	m_nMaxLog = 10;
	m_bHitVisible = false;
	m_nLogNum = 0;

	m_nDebugFontHandle = CreateFontToHandle("DebugFont", FONT_SIZE, -1, DX_FONTTYPE_NORMAL);
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cDebugFunc::Update(void)
{
	// �f�o�b�O�p�X�V���x�ύX
	DebugChangeUpdateSpeed();

	// �f�o�b�O�p�V�[�����Z�b�g
	DebugSceneReset();

	// �t���[�����[�g�v�Z
	CalcFrameRate();
}

//==========================================================================================
//  �`��
//==========================================================================================
void cDebugFunc::Draw(void)
{
	DebugPrint();
}

//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject * cDebugFunc::Finalize(void)
{
	DeleteFontToHandle(m_nDebugFontHandle);

	IBaseObject::Finalize();

	return nullptr;
}

//==========================================================================================
// �f�o�b�O���O��ǉ�
//==========================================================================================
void cDebugFunc::PushDebugLog(std::string str)
{
	m_listLog.push_front(str);
	str += "\n";
	str = "[" + std::to_string(m_nLogNum) + "] " + str;
	LogFileAdd(str.c_str());
	m_nLogNum++;
}

//==========================================================================================
// �f�o�b�O�p�X�V���x�ύX
//==========================================================================================
void cDebugFunc::DebugChangeUpdateSpeed(void)
{
	// FPS���[�h�̕ύX
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F2))
	{
		m_nFPSMode = 0;
	}
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F3))
	{
		m_nFPSMode++;
	}
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F4))
	{
		m_nFPSMode--;
	}
	// �ő�l�`�F�b�N
	if (FPS_MODE_MAX <= m_nFPSMode) m_nFPSMode = FPS_MODE_MAX;
	if (-FPS_MODE_MAX >= m_nFPSMode) m_nFPSMode = -FPS_MODE_MAX;

	// �Q�[�����x�̕ύX
	if (m_nFPSMode > 0)
	{
		cGame::GetInstance().SetFPS(60);
		cGame::GetInstance().SetOneFrameUpdate(m_nFPSMode);
	} else if (m_nFPSMode == 0)
	{
		cGame::GetInstance().SetFPS(60);
		cGame::GetInstance().SetOneFrameUpdate(1);
	} else if (m_nFPSMode < 0)
	{
		cGame::GetInstance().SetFPS(60 + m_nFPSMode * 10);
		cGame::GetInstance().SetOneFrameUpdate(1);
	}
}
//==========================================================================================
// �f�o�b�O�V�[�����Z�b�g
//==========================================================================================
void cDebugFunc::DebugSceneReset(void)
{
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F12))
	{
		cSceneManager::GetInstance().Reset();
	}
}

//==========================================================================================
// �f�o�b�O�o��
//==========================================================================================
void cDebugFunc::DebugPrint(void)
{
	// �f�o�b�O�o�͂̐؂�ւ�
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F1))
	{
		m_eDebugPrintMode = (DebugPrintMode)((m_eDebugPrintMode + 1) % DPRINT_MAX);
	}

	if (m_eDebugPrintMode <= DPRINT_LOG)
	{
		// �����F
		unsigned int nPrintColor = GetColor(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(255, 255, 255);

		//------------------------------------------------------------------------
		// �t���[�����[�g�\��
		DrawFormatString(cGame::GetInstance().GetWindowWidth() - 75, cGame::GetInstance().GetWindowHeight() - 16, nPrintColor, "%2.2fFPS", m_fFrameLate * cGame::GetInstance().GetOneFrameUpdate());

		//------------------------------------------------------------------------
		// �V�[��ID�̕\��
		cSceneManager sm = cSceneManager::GetInstance();
		DrawFormatString(cGame::GetInstance().GetWindowWidth() - 100, cGame::GetInstance().GetWindowHeight() - 64, nPrintColor, "SceneID %d", sm.GetCurrentSceneID());

		//------------------------------------------------------------------------
		// �f�o�b�O���O�̕\��
		if (!m_listLog.empty())
		{
			auto it = m_listLog.begin();
			auto end = m_listLog.end();
			int i = 0;
			while (it != end)
			{
				if (i >= m_nMaxLog)
				{
					it = m_listLog.erase(it);
					continue;
				}

				DrawFormatString(0, cGame::GetInstance().GetWindowHeight() - 20 * (i + 1), nPrintColor, ("[" + std::to_string(m_nLogNum - i) + "] " + " : " + (*it)).c_str());

				i++;
				it++;
			}
		}

		// �w���v�̕\��
		if (m_eDebugPrintMode == DPRINT_ALL)
		{
			std::string str;
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 0, " F1  : �f�o�b�O�\���̐؂�ւ�", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 15, " F2  : FPS���Z�b�g", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 30, " F3  : FPS����", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 45, " F4  : FPS����", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 60, " F12 : �V�[�����Z�b�g", nPrintColor, m_nDebugFontHandle);
		}
	}
	// �f�o�b�O�����蔻��̕\��
	if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_4))
	{
		if (m_bHitVisible)
		{
			m_bHitVisible = false;
		} else
		{
			m_bHitVisible = true;
		}
	}
}

//==========================================================================================
// �t���[�����[�g�v�Z
//==========================================================================================
void cDebugFunc::CalcFrameRate(void)
{
	// �t���[�����[�g�v�Z
	int nNowTime = GetNowCount();
	m_nFrameCount++;
	// 1�b���ɍX�V
	if (nNowTime > m_nStartTime + 1000)
	{
		m_fFrameLate = m_nFrameCount / ((float)(nNowTime - m_nStartTime) / 1000.0f);
		m_nFrameCount = 0;
		m_nStartTime = nNowTime;
	}
}
