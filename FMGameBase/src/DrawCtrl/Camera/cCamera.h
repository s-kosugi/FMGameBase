#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cCamera.h													*/
/*  @brief		:	�J�����N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/05/22													*/
/*																				*/
/*==============================================================================*/

#include "DxLib.h"
#include "BaseObject\IBaseObject.h"
#include "Utility/Vector/cVector3.h"

//===============================================================================
// �J�����N���X
class cCamera : public IBaseObject
{
public:

	void Initialize(void);
	void Update(void);

	// �J�����̉�]
	// ���݂̈ʒu���璍���_����ɐ�����]�����ʒu�ɃJ������ύX����
	void RotateHorizon( float angle );

	//-----------------------------------------------------------------------------------------
	// Getter
	//-----------------------------------------------------------------------------------------



	//-----------------------------------------------------------------------------------------
	// Setter
	//-----------------------------------------------------------------------------------------

private:

	//-----------------------------------------------------------------------------------------
	// �ϐ�
	//-----------------------------------------------------------------------------------------

	// �J�������W
	cVector3	m_vPos;

	// �����_
	cVector3	m_vTargetPos;

	//-----------------------------------------------------------------------------------------
	// �萔
	//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cCamera(void) { };     //  ������̐������֎~
	cCamera(IBaseObject* parent) {  };
	cCamera(IBaseObject* parent, const std::string& name) { };
	~cCamera(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cCamera(const cCamera& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cCamera& operator = (const cCamera& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cCamera& GetInstance(void) {
		static cCamera instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
//-----------------------------------------------------------------------------------------------------
};