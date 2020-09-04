#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	IBaseSingleton.h											*/
/*  @brief		:	�V���O���g���I�u�W�F�N�g									*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"

// �V���O���g���I�u�W�F�N�g�N���X
template<class T> class IBaseSingleton : public IBaseObject
{
protected:
	IBaseSingleton(void) { IBaseObject::IBaseObject(); };     //  ������̐������֎~
	IBaseSingleton(IBaseObject* parent) { IBaseObject::IBaseObject( parent, "None" );};
	IBaseSingleton(IBaseObject* parent, const std::string& name) { IBaseObject::IBaseObject(parent, name); };
	virtual ~IBaseSingleton(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	IBaseSingleton(const T& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	T& operator = (const T& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)

public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	virtual IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static T& GetInstance(void) {
		static T instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};		// �ÓI�����o�֐��AGetInstance�����鎖�Ő�������Ă��Ȃ������̃N���X�̊֐����Ăяo�������\
};