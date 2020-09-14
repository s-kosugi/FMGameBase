#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cMouse.h													*/
/*  @brief		:	�}�E�X���̓N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"
#include <DxLib.h>

class cMouse : public IBaseObject
{
public:
	void Initialize(void);
	void Update(void);

	// �}�E�X�{�^�������`�F�b�N
	bool CheckButton(unsigned int kcode); // �����Ă��邩
	bool CheckTrigger(unsigned int kcode); // �������u��
	bool CheckRelease(unsigned int kcode); // �������u��

	// �}�E�X���W�̐ݒ�
	void SetPoint(int x, int y);
	void SetPoint(POINT pt);

	// �}�E�X���W�̎擾
	POINT GetPoint(void);

private:
	// MouseButton state
	int m_nButtonState;
	int m_nPrevButtonState;

	//-----------------------------------------------------------------------------------------------------
	// �V���O���g���p
private:
	cMouse(void);     //  ������̐������֎~
	cMouse(IBaseObject* parent);
	cMouse(IBaseObject* parent, const std::string& name);
	~cMouse(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cMouse(const cMouse& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cMouse& operator = (const cMouse& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cMouse& GetInstance(void) {
		static cMouse instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};