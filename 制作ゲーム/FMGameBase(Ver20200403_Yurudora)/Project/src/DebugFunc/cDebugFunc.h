#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDebugFunc.h												*/
/*  @brief		:	�f�o�b�O�@�\�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/24													*/
/*																				*/
/*==============================================================================*/
#ifdef DEBUG

#include "DxLib.h"
#include "..\BaseObject\IBaseObject.h"
#include <string>
#include "Utility/Vector/cVector2.h"

//===============================================================================
// �f�o�b�O�@�\�N���X
class cDebugFunc : public IBaseObject
{
public:
	void Initialize(void);
	void Update(void);
	void Draw(void);

	// �f�o�b�O���O�ǉ�
	void PushDebugLog(std::string str);

	// �f�o�b�O���O�ő�o�͐��ݒ�
	inline void SetDebugLogMax(int num) { m_nMaxLog = num; };
	// �f�o�b�O���O�ǉ� str : �o�͂�����������  num : �o�͂��������l
	void PushDebugLog(std::string str, float num);
	// �f�o�b�O���O�ǉ� str : �o�͂�����������  num : �o�͂��������l
	void PushDebugLog(std::string str, int num);

	// �~�`��o�^(1�t���[���ԕ`��)
	// pos   : �w��|�C���g
	// range : �w��|�C���g����͈̔�(���a�j
	// color : �`��F(ARGB)
	void RegistDrawCircle(const cVector2& pos, float range,unsigned int color);

	// ��`�`��o�^(1�t���[���ԕ`��)
	// pos   : �w��|�C���g
	// range : �w��|�C���g����͈̔�
	// color : �`��F(ARGB)
	void RegistDrawBox(const cVector2& pos, POINT range,unsigned int color);

private:
	enum class PRINTMODE
	{
		ALL,		// �����\������
		LOG,		// �����\���Ȃ�
		NONE,		// �f�o�b�O�\���I�t

		MAX
	};
	// �f�o�b�O�p�~�`��\����
	struct DebugCircle {
		cVector2 pos = {0.0f,0.0f};
		float range = 0.0f;
		unsigned int color = 0xffffffff;
	};
	// �f�o�b�O�p��`�`��\����
	struct DebugBox {
		cVector2 pos = {0.0f,0.0f};
		POINT range = {0,0};
		unsigned int color = 0xffffffff;
	};


	// �f�o�b�O�p�X�V���x�ύX
	void DebugChangeUpdateSpeed(void);

	// �f�o�b�O�V�[�����Z�b�g
	void DebugSceneReset(void);

	// �f�o�b�O�o��
	void DebugPrint(void);

	// �f�o�b�O�}�`�`��
	void DrawShape(void);

	// �t���[�����[�g�v�Z
	void CalcFrameRate(void);

	// �X�N���[���V���b�g�B�e
	void SaveScreenShot(void);

	//---------------------------------------------------------
	// �t���[�����[�g�v�Z�p
	int m_nStartTime;
	int m_nFrameCount;
	float m_fFrameLate;
	//---------------------------------------------------------

	std::list<std::string> m_listLog;		// �f�o�b�O���O
	int m_nMaxLog;							// �f�o�b�O���O�ő�\���s��
	int m_nLogNum;							// ���ONo

	PRINTMODE m_eDebugPrintMode;		// �f�o�b�O�\���̐؂�ւ� 0:���O�A�w���v�\�� 1:���O�̂ݕ\�� 2:��\��

	int m_nFPSMode;							// 0:�����l 1:�������� 2:���� -1:�����x�� -2:�x��

	int m_nDebugFontHandle;					// �t�H���g�̃n���h��

	std::list<DebugCircle> m_listDrawCircle;// �f�o�b�O�~�`�惊�X�g
	std::list<DebugBox> m_listDrawBox;		// �f�o�b�O��`�`�惊�X�g


	static const int FPS_MODE_MAX;			// �X�V�t���[�����[�h�ő�
	static const int FONT_SIZE;				// �t�H���g�T�C�Y
	static const int LOG_MAX;				// ���O�\���ő吔

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cDebugFunc(void);     //  ������̐������֎~
	cDebugFunc(IBaseObject* parent);
	cDebugFunc(IBaseObject* parent, const std::string& name);
	~cDebugFunc(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cDebugFunc(const cDebugFunc& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cDebugFunc& operator = (const cDebugFunc& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cDebugFunc& GetInstance(void) {
		static cDebugFunc instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
//-----------------------------------------------------------------------------------------------------
};
#endif // DEBUG