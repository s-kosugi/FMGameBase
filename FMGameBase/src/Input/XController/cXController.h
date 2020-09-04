#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cXController.h												*/
/*  @brief		:	XBox�R���g���[���[���̓N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"
#include <DxLib.h>

class cXController : public IBaseObject
{
public:
	//--------------------------------------------------------------------
	// �X�e�B�b�N���͕���
	enum class STICK_DIRECTION
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
	};

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �{�^�������`�F�b�N
	bool CheckButton(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �����Ă��邩
	bool CheckTrigger(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �������u��
	bool CheckRelease(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �������u��

	// �U���̊J�n
	// Power : 0 �` 1000
	// Time : �U������
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	void StartVibration(int Power, int Time, int InputType = DX_INPUT_PAD1);

	// �U���̒�~
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	void StopVibration(int InputType = DX_INPUT_PAD1);

	// ���X�e�B�b�N�̎擾
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	POINT  GetLeftAnalogInput(int InputType = DX_INPUT_PAD1);

	// �E�X�e�B�b�N�̎擾
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	POINT  GetRightAnalogInput(int InputType = DX_INPUT_PAD1);

	// ���A�i���O�X�e�B�b�N�̃g���K�[����
	//  direction		direction ����ID
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
	//   �c
	//  �߂�l : true �|���ꂽ�u��
	bool   IsTriggerLeftAnalog(STICK_DIRECTION direction, int InputType = DX_INPUT_PAD1);

	// �E�A�i���O�X�e�B�b�N�̃g���K�[����
	//  direction		direction ����ID
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
	//   �c
	//  �߂�l : true �|���ꂽ�u��
	bool   IsTriggerRightAnalog(STICK_DIRECTION direction, int InputType = DX_INPUT_PAD1);

	// ���g���K�[�̎擾
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	// �߂�l : ���g���K�[���͒l
	unsigned char  GetLeftTriggerInput(int InputType = DX_INPUT_PAD1);

	// �E�g���K�[�̎擾
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	// �߂�l : �E�g���K�[���͒l
	unsigned char  GetRightTriggerInput(int InputType = DX_INPUT_PAD1);

	// ���g���K�[�̃g���K�[����
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
	//   �c
	//  �߂�l : true �����ꂽ�u��
	bool   IsTriggerLeftTrigger(int InputType = DX_INPUT_PAD1);

	// �E�g���K�[�̃g���K�[����
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
	//   �c
	//  �߂�l : true �����ꂽ�u��
	bool   IsTriggerRightTrigger(int InputType = DX_INPUT_PAD1);

	// ���g���K�[�̃{�^������
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
	//   �c
	//  �߂�l : true ������Ă��
	bool   IsButtonLeftTrigger(int InputType = DX_INPUT_PAD1);

	// �E�g���K�[�̃{�^������
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
	//   �c
	//  �߂�l : true ������Ă��
	bool   IsButtonRightTrigger(int InputType = DX_INPUT_PAD1);

	// ���g���K�[�̃����[�X����
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
	//   �c
	//  �߂�l : true �����ꂽ�u��
	bool   IsReleaseLeftTrigger(int InputType = DX_INPUT_PAD1);

	// �E�g���K�[�̃����[�X����
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
	//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
	//   �c
	//  �߂�l : true �����ꂽ�u��
	bool   IsReleaseRightTrigger(int InputType = DX_INPUT_PAD1);

	// �ڑ��䐔�擾
	// �߂�l : �ڑ��䐔
	inline int  GetConnectNum(void) { return m_nJoyPadNum; };

private:

	// XInput Joypad state
	XINPUT_STATE* m_xiInputState;
	// �O�t���[�����
	XINPUT_STATE* m_xiPrevInputState;

	// X�R���g���[���[�ڑ���
	short m_nJoyPadNum;

	//--------------------------------------------------------------------
	// �萔
	static const int	LIMIT_CANT_ANALOG;		// �A�i���O�X�e�B�b�N�̗V��
	static const int	LIMIT_CANT_TRIGGER;		// �g���K�[�̗V��

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cXController(void);     //  ������̐������֎~
	cXController(IBaseObject* parent);
	cXController(IBaseObject* parent, const std::string& name);
	~cXController(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cXController(const cXController& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cXController& operator = (const cXController& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cXController& GetInstance(void) {
		static cXController instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};