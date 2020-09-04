#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cKeyboard.h													*/
/*  @brief		:	�L�[�{�[�h���̓N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"

class cKeyboard : public IBaseObject
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update( void );

	// �L�[�����`�F�b�N
	bool CheckButton(unsigned int kcode); // �����Ă��邩
	bool CheckTrigger(unsigned int kcode); // �������u��
	bool CheckRelease(unsigned int kcode); // �������u��
	
private:
	// DirectInput keyboard state
	char m_diKeyState[256];
	// �O�t���[�����
	char m_diPrevKeyState[256];

	// �萔
	static const int KEY_STATE_NUM = 256;

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cKeyboard(void);     //  ������̐������֎~
	cKeyboard(IBaseObject* parent);
	cKeyboard(IBaseObject* parent, const std::string& name);
	~cKeyboard(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cKeyboard(const cKeyboard& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cKeyboard& operator = (const cKeyboard& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cKeyboard& GetInstance(void) {
		static cKeyboard instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
//-----------------------------------------------------------------------------------------------------
};