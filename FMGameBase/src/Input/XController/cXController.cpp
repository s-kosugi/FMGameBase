/*==============================================================================*/
/*																				*/
/*	@file title	:	cXController.cpp											*/
/*  @brief		:	XBOX�R���g���[���[���̓N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/22													*/
/*																				*/
/*==============================================================================*/

#include "cXController.h"
#include "../../Utility/memory.h"

//==========================================================================================
// �萔
const int cXController::LIMIT_CANT_ANALOG = 30000;
const int cXController::LIMIT_CANT_TRIGGER = 200;

//==========================================================================================
// ������
//==========================================================================================
void cXController::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "XController";

	// �R���g���[���[�ڑ������擾
	m_nJoyPadNum = GetJoypadNum();

	// �ڑ�����Ă���R���g���[���[���������L�[�����쐬����
	m_xiInputState = NEW XINPUT_STATE[m_nJoyPadNum];
	m_xiPrevInputState = NEW XINPUT_STATE[m_nJoyPadNum];

	memset(m_xiInputState, 0, m_nJoyPadNum * sizeof(XINPUT_STATE));
	memset(m_xiPrevInputState, 0, m_nJoyPadNum * sizeof(XINPUT_STATE));


	IBaseObject::Initialize();
}
//==========================================================================================
// �X�V
//==========================================================================================
void cXController::Update(void)
{
	for (int i = 1; i <= m_nJoyPadNum;i++)
	{
		// ���͏�Ԃ��擾����
		memcpy(&m_xiPrevInputState[i - 1], &m_xiInputState[i - 1], sizeof(XINPUT_STATE));
		GetJoypadXInputState(i, &m_xiInputState[i - 1]);
	}
	IBaseObject::Update();
}
//==========================================================================================
// �{�^�������`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   XINPUT_BUTTON_A : A�{�^��
//   XINPUT_BUTTON_DPAD_UP : ��{�^��
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:������Ă����@false:������Ă��Ȃ�
//==========================================================================================
bool cXController::CheckButton(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// �{�^����������Ă��邩�ǂ���
	if (m_xiInputState[InputType - 1].Buttons[kcode])
		return true;

	return false;
}
//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   XINPUT_BUTTON_A : A�{�^��
//   XINPUT_BUTTON_DPAD_UP : ��{�^��
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:������Ă���
//==========================================================================================
bool cXController::CheckTrigger(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// �{�^���������ꂽ�u��
	if (!(m_xiPrevInputState[InputType - 1].Buttons[kcode]) && (m_xiInputState[InputType - 1].Buttons[kcode])) return true;

	return false;
}
//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   XINPUT_BUTTON_A : A�{�^��
//   XINPUT_BUTTON_DPAD_UP : ��{�^��
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:�����ꂽ�u��
//==========================================================================================
bool cXController::CheckRelease(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// �{�^���������ꂽ�u��
	if ((m_xiPrevInputState[InputType - 1].Buttons[kcode]) && !(m_xiInputState[InputType - 1].Buttons[kcode])) return true;

	return false;
}

//==========================================================================================
// �U���̊J�n
// Power : 0 �` 1000
// Time : �U������
// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
//==========================================================================================
void cXController::StartVibration(int Power, int Time , int InputType )
{
	StartJoypadVibration(InputType, Power, Time);
}

//==========================================================================================
// �U���̒�~
// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
//==========================================================================================
void cXController::StopVibration(int InputType)
{
	StopJoypadVibration(InputType);
}

//==========================================================================================
// ���X�e�B�b�N�̎擾
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l POINT -32768 �` 32767�܂ł̒l
//
//==========================================================================================
POINT cXController::GetLeftAnalogInput(int InputType)
{
	POINT pt;
	pt.x = pt.y = 0;
	if (InputType > m_nJoyPadNum) return pt;

	pt.x = m_xiInputState[InputType - 1].ThumbLX;
	pt.y = m_xiInputState[InputType - 1].ThumbLY;
	return pt;
}

//==========================================================================================
// �E�X�e�B�b�N�̎擾
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l POINT -32768 �` 32767�܂ł̒l
//
//==========================================================================================
POINT cXController::GetRightAnalogInput(int InputType)
{
	POINT pt;
	pt.x = pt.y = 0;
	if (InputType > m_nJoyPadNum) return pt;

	pt.x = m_xiInputState[InputType - 1].ThumbRX;
	pt.y = m_xiInputState[InputType - 1].ThumbRY;
	return pt;
}

//==========================================================================================
// ���A�i���O�X�e�B�b�N�̃g���K�[����
//  STICK_DIRECTION direction ����ID
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
//  �߂�l : true �|���ꂽ�u��
//==========================================================================================
bool cXController::IsTriggerLeftAnalog(STICK_DIRECTION direction , int InputType )
{
	if (InputType > m_nJoyPadNum) return false;
	switch (direction)
	{
	case STICK_DIRECTION::LEFT:
		return (m_xiInputState[InputType-1].ThumbLX < LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbLX > LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::RIGHT:
		return (m_xiInputState[InputType-1].ThumbLX > LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbLX < LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::UP:
		return (m_xiInputState[InputType-1].ThumbLY < LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbLY > LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::DOWN:
		return (m_xiInputState[InputType-1].ThumbLY > LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbLY < LIMIT_CANT_ANALOG);
	}
	return false;
}

//==========================================================================================
// �E�A�i���O�X�e�B�b�N�̃g���K�[����
//  STICK_DIRECTION	direction ����ID
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
//  �߂�l : true �|���ꂽ�u��
//==========================================================================================
bool cXController::IsTriggerRightAnalog( STICK_DIRECTION direction, int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	switch (direction)
	{
	case STICK_DIRECTION::LEFT:
		return (m_xiInputState[InputType-1].ThumbRX < LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbRX > LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::RIGHT:
		return (m_xiInputState[InputType-1].ThumbRX > LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbRX < LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::UP:
		return (m_xiInputState[InputType-1].ThumbRY < LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbRY > LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::DOWN:
		return (m_xiInputState[InputType-1].ThumbRY > LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbRY < LIMIT_CANT_ANALOG);
	}
	return false;
}

//==========================================================================================
// ���g���K�[�̎擾
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l unsigned char 0 �` 255�܂ł̒l
//
//==========================================================================================
unsigned char cXController::GetLeftTriggerInput(int InputType)
{
	if (InputType > m_nJoyPadNum) return 0;

	return m_xiInputState[InputType - 1].LeftTrigger;
}

//==========================================================================================
// �E�g���K�[�̎擾
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l unsigned char 0 �` 255�܂ł̒l
//
//==========================================================================================
unsigned char cXController::GetRightTriggerInput(int InputType)
{
	if (InputType > m_nJoyPadNum) return 0;

	return m_xiInputState[InputType - 1].RightTrigger;
}
//==========================================================================================
// ���g���K�[�̃g���K�[����
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l bool true �������u��
//
//==========================================================================================
bool cXController::IsTriggerLeftTrigger( int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	return ( m_xiInputState[InputType-1].LeftTrigger > LIMIT_CANT_TRIGGER && m_xiPrevInputState[InputType-1].LeftTrigger < LIMIT_CANT_TRIGGER );
}

//==========================================================================================
// �E�g���K�[�̃g���K�[����
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l bool true �������u��
//
//==========================================================================================
bool cXController::IsTriggerRightTrigger( int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	return ( m_xiInputState[InputType-1].RightTrigger > LIMIT_CANT_TRIGGER && m_xiPrevInputState[InputType-1].RightTrigger < LIMIT_CANT_TRIGGER );
}
//==========================================================================================
// ���g���K�[�̃{�^������
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l bool true �����Ă����
//
//==========================================================================================
bool cXController::IsButtonLeftTrigger( int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	return ( m_xiInputState[InputType-1].LeftTrigger > LIMIT_CANT_TRIGGER );
}
//==========================================================================================
// �E�g���K�[�̃{�^������
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l bool true �����Ă����
//
//==========================================================================================
bool cXController::IsButtonRightTrigger( int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	return ( m_xiInputState[InputType-1].RightTrigger > LIMIT_CANT_TRIGGER );
}
//==========================================================================================
// ���g���K�[�̃����[�X����
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l bool true �����ꂽ�u��
//
//==========================================================================================
bool cXController::IsReleaseLeftTrigger(int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	return (m_xiInputState[InputType - 1].LeftTrigger < LIMIT_CANT_TRIGGER && m_xiPrevInputState[InputType - 1].LeftTrigger > LIMIT_CANT_TRIGGER);
}
//==========================================================================================
// �E�g���K�[�̃����[�X����
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l bool true �����ꂽ�u��
//
//==========================================================================================
bool cXController::IsReleaseRightTrigger(int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	return (m_xiInputState[InputType - 1].RightTrigger < LIMIT_CANT_TRIGGER && m_xiPrevInputState[InputType - 1].RightTrigger > LIMIT_CANT_TRIGGER);
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cXController::cXController(void):
	m_xiInputState(nullptr),
	m_xiPrevInputState(nullptr),
	m_nJoyPadNum(0)
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cXController::cXController(IBaseObject* parent):
	cXController::cXController()
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cXController::cXController(IBaseObject* parent, const std::string& name):
	cXController::cXController(parent)
{
}

//==========================================================================================
// �R�s�[�R���X�g���N�^
//==========================================================================================
cXController::cXController(const cXController& t):
	cXController::cXController()
{
}
