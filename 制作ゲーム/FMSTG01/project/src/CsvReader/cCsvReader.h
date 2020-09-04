#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cCsvReader.h												*/
/*  @brief		:	CSV読み込みクラス											*/
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
	// 初期化
	void Initialize(void);

	// 破棄
	IBaseObject* Finalize(void);

	// CSVファイル読み込み
	void LoadFile(const std::string filepath, std::vector<std::string>& buf);

private:

	// １行単位の文字列を項目毎に分割する
	void SplitCsv(const std::string & str, std::vector<std::string>& buf);

	// 定数
	static const int LINE_CHAR_MAX;		// １行当たりの最大文字数
};