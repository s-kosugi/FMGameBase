/*==============================================================================*/
/*																				*/
/*	@file title	:	cSaveData.cpp													*/
/*  @brief		:	�f�[�^�ۑ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/17													*/
/*																				*/
/*==============================================================================*/

#include "cSaveData.h"

//================================================================================
// �ǂݍ���
// file_name �ǂݍ��ރZ�[�u�f�[�^�̃t�@�C���p�X
//================================================================================
cSaveData::Data cSaveData::Load(std::string file_name)
{
	FILE* fp;
	cSaveData::Data loadData;

	memset(&loadData, 0, sizeof(loadData));

	// �t�@�C����ǂݍ��ݐV�K�쐬�ŊJ��
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != NULL)
	{
		// �f�[�^��ǂݍ���
		fread(&loadData, sizeof(loadData), 1, fp);

		fclose(fp);
	}
	return loadData;
}

//================================================================================
// ��������
// file_name �ۑ�����t�@�C���p�X
// data �ۑ�����Z�[�u�f�[�^���e
//================================================================================
bool cSaveData::Save(std::string file_name, Data data)
{
	FILE* fp;

	// �t�@�C�����������ݐV�K�쐬�ŊJ��
	fopen_s(&fp, file_name.c_str(), "wb");

	if (fp != NULL)
	{
		// �f�[�^����������
		fwrite(&data, sizeof(data), 1, fp);

		fclose(fp);
	}

	return false;
}
