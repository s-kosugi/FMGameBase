#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cCsvReader.h												*/
/*  @brief		:	CSV�ǂݍ��݃N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/08													*/
/*																				*/
/*==============================================================================*/

#include "BaseObject\IBaseObject.h"
#include <string>
#include <vector>

class cCsvReader : public IBaseObject
{
public:
	// ������
	void Initialize(void);

	// CSV�t�@�C���ǂݍ���
	void LoadFile(const std::string filepath, std::vector<std::string>& buf);

private:

	// �P�s�P�ʂ̕���������ږ��ɕ�������
	void SplitCsv(const std::string & str, std::vector<std::string>& buf);

	// �萔
	static const int LINE_CHAR_MAX;		// �P�s������̍ő啶����


//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cCsvReader(void) { };     //  ������̐������֎~
	cCsvReader(IBaseObject* parent) {  };
	cCsvReader(IBaseObject* parent, const std::string& name) { };
	~cCsvReader(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cCsvReader(const cCsvReader& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cCsvReader& operator = (const cCsvReader& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public :
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cCsvReader& GetInstance(void) {
		static cCsvReader instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
//-----------------------------------------------------------------------------------------------------
};