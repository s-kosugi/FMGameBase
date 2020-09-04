#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cSaveData.h													*/
/*  @brief		:	データ保存クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/17													*/
/*																				*/
/*==============================================================================*/

#include <string>

// データ保存クラス
class cSaveData
{
public:
	// セーブデータ構造体
	// ゲームに合わせて保存したいメンバ変数を追加する
	struct Data 
	{
		int HiScore;
	};

	// セーブデータの読み込み、取得
	// file_name 読み込むセーブデータのファイルパス
	Data Load(std::string file_name);

	// セーブデータの書き込み、保存
	// file_name 保存するファイルパス
	// data 保存するセーブデータ内容
	bool Save(std::string file_name, Data data);
};