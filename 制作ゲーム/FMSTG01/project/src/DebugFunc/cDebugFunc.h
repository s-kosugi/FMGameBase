#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDebugFunc.h												*/
/*  @brief		:	�f�o�b�O�@�\�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/24													*/
/*																				*/
/*==============================================================================*/

#include "DxLib.h"
#include "..\BaseObject\IBaseSingleton.h"

//===============================================================================
// �f�o�b�O�@�\�N���X
class cDebugFunc : public IBaseSingleton<cDebugFunc>
{
public:
	~cDebugFunc();

	void Initialize(void);
	void Update(void);
	void Draw(void);
	IBaseObject* Finalize(void);

	// �f�o�b�O�����蔻��\���ؑ�
	bool GetDebugHitVisible(void) {return m_bHitVisible;};

	// �f�o�b�O���O�ǉ�
	void PushDebugLog(std::string str);

	// �f�o�b�O���O�ő�o�͐��ݒ�
	inline void SetDebugLogMax(int num) { m_nMaxLog = num; };

private:
	enum DebugPrintMode
	{
		DPRINT_ALL,
		DPRINT_LOG,
		DPRINT_NO,

		DPRINT_MAX
	};

	// �f�o�b�O�p�X�V���x�ύX
	void DebugChangeUpdateSpeed(void);

	// �f�o�b�O�V�[�����Z�b�g
	void DebugSceneReset(void);

	// �f�o�b�O�o��
	void DebugPrint(void);

	// �t���[�����[�g�v�Z
	void CalcFrameRate(void);

	//---------------------------------------------------------
	// �t���[�����[�g�v�Z�p
	int m_nStartTime;
	int m_nFrameCount;
	float m_fFrameLate;
	//---------------------------------------------------------

	std::list<std::string> m_listLog;		// �f�o�b�O���O
	int m_nMaxLog;							// �f�o�b�O���O�ő�\���s��
	int m_nLogNum;							// ���ONo

	DebugPrintMode m_eDebugPrintMode;		// �f�o�b�O�\���̐؂�ւ� 0:���O�A�w���v�\�� 1:���O�̂ݕ\�� 2:��\��

	int m_nFPSMode;							// 0:�����l 1:�������� 2:���� -1:�����x�� -2:�x��

	int m_nDebugFontHandle;					// �t�H���g�̃n���h��


	static const int FPS_MODE_MAX;			// �X�V�t���[�����[�h�ő�
	static const int FONT_SIZE;				// �t�H���g�T�C�Y

	bool m_bHitVisible;						// �����蔻��\���L��
};