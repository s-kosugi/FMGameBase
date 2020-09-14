#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cJoyPad.h													*/
/*  @brief		:	�R���g���[���[���̓N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"
#include <DxLib.h>

class cJoyPad : public IBaseObject
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �{�^�������`�F�b�N
	bool CheckButton(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �����Ă��邩
	bool CheckTrigger(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �������u��
	bool CheckRelease(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �������u��

	// �U���̊J�n
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	// Power : 0 �` 1000
	// Time : �U������
	void StartVibration(int InputType, int Power, int Time);

	// �U���̒�~
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	void StopVibration(int InputType);

	// �A�i���O���͎擾
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	POINT  GetAnalogInput(int InputType);

	// �ڑ��䐔�擾
	inline int  GetConnectNum(void) { return m_nJoyPadNum; };

private:
	// DirectInput Joypad state
	int* m_diInputState;
	// �O�t���[�����
	int* m_diPrevInputState;

	// �W���C�p�b�h�ڑ���
	short m_nJoyPadNum;

	//-----------------------------------------------------------------------------------------------------
	// �V���O���g���p
private:
	cJoyPad(void);     //  ������̐������֎~
	cJoyPad(IBaseObject* parent);
	cJoyPad(IBaseObject* parent, const std::string& name);
	~cJoyPad(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cJoyPad(const cJoyPad& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cJoyPad& operator = (const cJoyPad& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:

	static cJoyPad& GetInstance(void) {
		static cJoyPad instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};