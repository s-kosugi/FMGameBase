/*==============================================================================*/
/*																				*/
/*	@file title	:	cDebugFunc.cpp												*/
/*  @brief		:	�f�o�b�O�@�\�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/24													*/
/*																				*/
/*==============================================================================*/
#ifdef DEBUG

#include "cDebugFunc.h"
#include "..\cGame.h"
#include "..\Input\Keyboard\cKeyboard.h"
#include "..\SceneManager\cSceneManager.h"
#include "DrawCtrl/cDrawCtrl.h"
#include <sstream>
#include "EffekseerForDXLib.h"

//==========================================================================================
// �萔
//==========================================================================================
const int cDebugFunc::FPS_MODE_MAX = 5;
const int cDebugFunc::FONT_SIZE = 15;
const int cDebugFunc::LOG_MAX = 30;

//==========================================================================================
//  ������
//==========================================================================================
void cDebugFunc::Initialize(void)
{
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

	// �X�N���[���V���b�g�ۑ�
	SaveScreenShot();
}

//==========================================================================================
//  �`��
//==========================================================================================
void cDebugFunc::Draw(void)
{
	DebugPrint();
}
//==========================================================================================
// �f�o�b�O���O��ǉ�
//==========================================================================================
void cDebugFunc::PushDebugLog(std::string str)
{
	m_listLog.push_front(str);
	str += "\n";
	str = "[" + std::to_string(m_nLogNum)+"] "+ str;
	LogFileAdd(str.c_str());
	m_nLogNum++;
}
//==========================================================================================
// �f�o�b�O���O��ǉ�
//==========================================================================================
void cDebugFunc::PushDebugLog(std::string str, float num)
{
	std::ostringstream oss;
	oss << str << " " << num;

	PushDebugLog(oss.str());
}
//==========================================================================================
// �f�o�b�O���O��ǉ�
//==========================================================================================
void cDebugFunc::PushDebugLog(std::string str, int num)
{
	std::ostringstream oss;
	oss << str << " " << num;

	PushDebugLog(oss.str());
}
//==========================================================================================
// �~�`��o�^(1�t���[���ԕ`��)
// pos   : �w��|�C���g
// range : �w��|�C���g����͈̔�
// color : �`��F(ARGB)
//==========================================================================================
void cDebugFunc::RegistDrawCircle(const cVector2 & pos, float range,unsigned int color)
{
	DebugCircle circle;
	circle.pos = pos;
	circle.range = range;
	circle.color = color;
	m_listDrawCircle.push_back(circle);
}
//==========================================================================================
// ��`�`��o�^(1�t���[���ԕ`��)
// pos   : �w��|�C���g
// range : �w��|�C���g����͈̔�
// color : �`��F(ARGB)
//==========================================================================================
void cDebugFunc::RegistDrawBox(const cVector2 & pos, POINT range,unsigned int color)
{
	DebugBox box;
	box.pos = pos;
	box.range = range;
	box.color = color;
	m_listDrawBox.push_back(box);
}
//==========================================================================================
// �f�o�b�O�p�X�V���x�ύX
//==========================================================================================
void cDebugFunc::DebugChangeUpdateSpeed(void)
{
	// FPS���[�h�̕ύX
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F2))
	{
		m_nFPSMode = 0;
	}
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F3))
	{
		m_nFPSMode++;
	}
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F4))
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
	}
	else if (m_nFPSMode == 0)
	{
		cGame::GetInstance().SetFPS(60);
		cGame::GetInstance().SetOneFrameUpdate(1);
	}
	else if (m_nFPSMode < 0)
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
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F11))
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
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F1))
	{
		m_eDebugPrintMode = (PRINTMODE)(((int)m_eDebugPrintMode + 1) % (int)PRINTMODE::MAX);
	}

	if (m_eDebugPrintMode <= PRINTMODE::LOG)
	{
		// �f�o�b�O�}�`�̕`��
		DrawShape();

		// �����F
		unsigned int nPrintColor = GetColor(255, 255, 255);


		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(255, 255, 255);

		//------------------------------------------------------------------------
		// �t���[�����[�g�\��
		DrawFormatStringToHandle(cGame::GetInstance().GetWindowWidth() - 75, cGame::GetInstance().GetWindowHeight() - 16,
								 nPrintColor,
								 m_nDebugFontHandle,
								 "%2.2fFPS", (float)((double)m_fFrameLate * cGame::GetInstance().GetOneFrameUpdate()));
		//------------------------------------------------------------------------
		// �}�E�X���W�̕\��
		//cMouse mouse = cMouse::GetInstance();
		//POINT mspt = mouse.GetPoint();

		//DrawFormatString(GetWindowWidth() - 120, GetWindowHeight() - 48, nPrintColor, "Mouse.x %d", mspt.x);
		//DrawFormatString(GetWindowWidth() - 120, GetWindowHeight() - 32, nPrintColor, "Mouse.y %d", mspt.y);

		//------------------------------------------------------------------------
		// �V�[��ID�̕\��
		cSceneManager& sm = cSceneManager::GetInstance();
		DrawFormatStringToHandle(cGame::GetInstance().GetWindowWidth() - 100, cGame::GetInstance().GetWindowHeight() - 64,
								nPrintColor,
								m_nDebugFontHandle,
								"SceneID %d", sm.GetCurrentSceneID());
		//------------------------------------------------------------------------
		// �G�t�F�N�g�����̕\��
		Effekseer::Manager* efMan = GetEffekseer2DManager();
		int efNum = efMan->GetTotalInstanceCount();
		DrawFormatStringToHandle(cGame::GetInstance().GetWindowWidth() - 190, cGame::GetInstance().GetWindowHeight() - 80,
			nPrintColor,
			m_nDebugFontHandle,
			"EffectInstance %4d", efNum);

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

				DrawFormatStringToHandle(0, cGame::GetInstance().GetWindowHeight() - FONT_SIZE * (i + 1),
					nPrintColor,
					m_nDebugFontHandle,
					("[" + std::to_string(m_nLogNum - i) + "]" + ":" + (*it)).c_str() );

				i++;
				it++;
			}
		}

		// �w���v�̕\��
		if (m_eDebugPrintMode == PRINTMODE::ALL)
		{
			std::string str;
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 0, " F1  : �f�o�b�O�\���̐؂�ւ�", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 15, " F2  : FPS���Z�b�g", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 30, " F3  : FPS����", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 45, " F4  : FPS����", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 60, " F11 : �V�[�����Z�b�g", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 75, " PrtScr : �X�N���[���V���b�g", nPrintColor, m_nDebugFontHandle);
		}
	}
	// �f�o�b�O�}�`���X�g�̃N���A
	m_listDrawBox.clear();
	m_listDrawCircle.clear();
}
//==========================================================================================
// �f�o�b�O�}�`�`��
//==========================================================================================
void cDebugFunc::DrawShape(void)
{
	// ��`�̕`��
	if (!m_listDrawBox.empty())
	{
		for (auto it = m_listDrawBox.begin();it != m_listDrawBox.end();it++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).color >> 24);
			SetDrawBright(255, 255, 255);
			DrawBox((int)((*it).pos.x - (*it).range.x / 2),
				    (int)((*it).pos.y - (*it).range.y / 2),
					(int)((*it).pos.x + (*it).range.x / 2),
					(int)((*it).pos.y + (*it).range.y / 2),
					(*it).color,
					true);
		}
	}
	// �~�̕`��
	if (!m_listDrawCircle.empty())
	{
		for (auto it = m_listDrawCircle.begin();it != m_listDrawCircle.end();it++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).color >> 24);
			SetDrawBright(255, 255, 255);
			DrawCircle((int)((*it).pos.x),
					   (int)((*it).pos.y),
					   (int)((*it).range),
					   (*it).color);
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

//==========================================================================================
// ���݃t���[���̃X�N���[���V���b�g��ۑ�����
//==========================================================================================
void cDebugFunc::SaveScreenShot(void)
{
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_SYSRQ))
	{
		cDrawCtrl::GetInstance().RequestScreenShot();
	}
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cDebugFunc::cDebugFunc(void) :
	m_nStartTime(0),
	m_nFrameCount(0),
	m_fFrameLate(0.0f),
	m_nMaxLog(LOG_MAX),
	m_nLogNum(0),
	m_eDebugPrintMode(PRINTMODE::ALL),
	m_nFPSMode(0),
	m_nDebugFontHandle(-1)
{
	m_nStartTime = GetNowCount();
	m_nDebugFontHandle = CreateFontToHandle("DebugFont", FONT_SIZE,-1, DX_FONTTYPE_NORMAL);
	m_listLog.clear();
	m_listDrawCircle.clear();
	m_listDrawBox.clear();
}
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cDebugFunc::cDebugFunc(IBaseObject* parent) :
	cDebugFunc::cDebugFunc()
{
}
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cDebugFunc::cDebugFunc(IBaseObject* parent, const std::string& name) :
	cDebugFunc::cDebugFunc(parent)
{
}
//==========================================================================================
// �R�s�[�R���X�g���N�^
//==========================================================================================
cDebugFunc::cDebugFunc(const cDebugFunc& t) :
	cDebugFunc::cDebugFunc()
{
}

#endif // DEBUG