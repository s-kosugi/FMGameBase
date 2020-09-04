#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cCsvReader.h												*/
/*  @brief		:	CSV�ǂݍ��݃N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/08													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"
#include <string>
#include <vector>

class cCsvReader : public IBaseSingleton<cCsvReader>
{
public:
	// ������
	void Initialize(void);

	// �j��
	IBaseObject* Finalize(void);

	// CSV�t�@�C���ǂݍ���
	void LoadFile(const std::string filepath, std::vector<std::string>& buf);

private:

	// �P�s�P�ʂ̕���������ږ��ɕ�������
	void SplitCsv(const std::string & str, std::vector<std::string>& buf);

	// �萔
	static const int LINE_CHAR_MAX;		// �P�s������̍ő啶����
};