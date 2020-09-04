#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cSaveData.h													*/
/*  @brief		:	�f�[�^�ۑ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/17													*/
/*																				*/
/*==============================================================================*/

#include <string>

// �f�[�^�ۑ��N���X
class cSaveData
{
public:
	// �Z�[�u�f�[�^�\����
	// �Q�[���ɍ��킹�ĕۑ������������o�ϐ���ǉ�����
	struct Data 
	{
		int HiScore;
	};

	// �Z�[�u�f�[�^�̓ǂݍ��݁A�擾
	// file_name �ǂݍ��ރZ�[�u�f�[�^�̃t�@�C���p�X
	Data Load(std::string file_name);

	// �Z�[�u�f�[�^�̏������݁A�ۑ�
	// file_name �ۑ�����t�@�C���p�X
	// data �ۑ�����Z�[�u�f�[�^���e
	bool Save(std::string file_name, Data data);
};