/*==============================================================================*/
/*																				*/
/*	@file title	:	cCsvReader.cpp												*/
/*  @brief		:	CSV�ǂݍ��݃N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/08													*/
/*																				*/
/*==============================================================================*/

#include "cCsvReader.h"
#include <DxLib.h>
#include <sstream>

// �萔
const int cCsvReader::LINE_CHAR_MAX = 256;		// �P�s������̍ő啶����

//==========================================================================================
// ������
//==========================================================================================
void cCsvReader::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "CsvReader";

	IBaseObject::Initialize();
}
//==========================================================================================
// �t�@�C���ǂݍ���
// fiepath : �ǂݍ��ރt�@�C���̃p�X
// buf : �ǂݍ��񂾃t�@�C����������z��Ƃ��ē���
//==========================================================================================
void cCsvReader::LoadFile(const std::string filepath, std::vector<std::string>& buf)
{
	int handle = FileRead_open(filepath.c_str());

	// �G���[
	if (handle == 0)
	{
		ErrorLogAdd("FileLoadError! FileHandle is None\n");
		return;
	}
	// �P�s���Ƃ̃f�[�^���i�[���Ă���
	char line[LINE_CHAR_MAX];

	// �t�@�C���I�[�܂łP�s���ǂݍ���
	while (FileRead_gets(line, LINE_CHAR_MAX, handle) != -1)
	{
		SplitCsv(line, buf);
	}

	FileRead_close(handle);

	return;
}
//==========================================================================================
// �P�s�P�ʂ̕���������ږ��ɕ�������
// str : �s�P�ʂł̕�����
// buf : �ǂݍ��񂾕������i�[����o�b�t�@
//==========================================================================================
void cCsvReader::SplitCsv(const std::string & str, std::vector<std::string>& buf)
{
	// ������X�g���[��
	std::istringstream iss(str);

	std::string readStr;

	// ,����getline�ŕ������ǂݍ���
	while (std::getline(iss, readStr, ',')) {
		buf.push_back(readStr);
	}

	return;
}
