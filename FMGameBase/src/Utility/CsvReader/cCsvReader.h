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

// CSV�ǂݍ��݃N���X
class cCsvReader : public IBaseObject
{
public:
	cCsvReader(IBaseObject* parent);
	~cCsvReader();

	// CSV�t�@�C���ǂݍ���
	void LoadFile(const std::string filepath);


	// �w�肳�ꂽ�f�[�^�𕶎���Ŏ擾
	const std::string GetString(int row, int col);
	// �w�肳�ꂽ�f�[�^�𐮐��Ŏ擾
	const int GetInt(int row, int col);
	// �w�肳�ꂽ�f�[�^�������Ŏ擾
	const float GetFloat(int row, int col);

	// �s���̎擾
	const int GetRowNum(void);

	// �񐔂̎擾
	const int GetColNum(void);

	// ���ڐ��̎擾
	const int GetDataNum(void);


private:

	// �萔
	static const int LINE_CHAR_MAX;		// �P�s������̍ő啶����

	// �ǂݍ��݃f�[�^
	std::vector<std::string> m_Buffer;

	// �s��
	int m_RowNum;

};