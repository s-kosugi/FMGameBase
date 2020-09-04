#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	ISingleton.h												*/
/*  @brief		:	�V���O���g���N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/09/18													*/
/*																				*/
/*==============================================================================*/

// �V���O���g��������N���X�Ɍp���������邽�߂̃x�[�X�N���X
template<class T> class ISingleton {
protected:
	ISingleton(void) {};     //  ������̐������֎~(���������̋֎~)(�R���X�g���N�^��private�ɂ��鎖�ŊO�������s��)
	virtual ~ISingleton(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	ISingleton(const T& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)(private�ɂ��鎖�ŊO���g�p�֎~)
	T& operator = (const T& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)(private�ɂ��鎖�ŊO���g�p�֎~)

public:
	static T& GetInstance(void) {
		static T instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};		// �ÓI�����o�֐��AGetInstance�����鎖�Ő�������Ă��Ȃ������̃N���X�̊֐����Ăяo�������\
};