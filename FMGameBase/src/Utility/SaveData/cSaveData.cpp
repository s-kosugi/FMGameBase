/*==============================================================================*/
/*																				*/
/*	@file title	:	cSaveData.cpp													*/
/*  @brief		:	データ保存クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/17													*/
/*																				*/
/*==============================================================================*/

#include "cSaveData.h"

//================================================================================
// 読み込み
// file_name 読み込むセーブデータのファイルパス
//================================================================================
cSaveData::Data cSaveData::Load(std::string file_name)
{
	FILE* fp;
	cSaveData::Data loadData;

	memset(&loadData, 0, sizeof(loadData));

	// ファイルを読み込み新規作成で開く
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != NULL)
	{
		// データを読み込み
		fread(&loadData, sizeof(loadData), 1, fp);

		fclose(fp);
	}
	return loadData;
}

//================================================================================
// 書き込み
// file_name 保存するファイルパス
// data 保存するセーブデータ内容
//================================================================================
bool cSaveData::Save(std::string file_name, Data data)
{
	FILE* fp;

	// ファイルを書き込み新規作成で開く
	fopen_s(&fp, file_name.c_str(), "wb");

	if (fp != NULL)
	{
		// データを書き込み
		fwrite(&data, sizeof(data), 1, fp);

		fclose(fp);
	}

	return false;
}
