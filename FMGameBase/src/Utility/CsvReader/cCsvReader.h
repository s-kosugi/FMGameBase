#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cCsvReader.h												*/
/*  @brief		:	CSV読み込みクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/08													*/
/*																				*/
/*==============================================================================*/

#include "BaseObject\IBaseObject.h"
#include <string>
#include <vector>

// CSV読み込みクラス
class cCsvReader : public IBaseObject
{
public:
	cCsvReader(IBaseObject* parent);
	~cCsvReader();

	// CSVファイル読み込み
	void LoadFile(const std::string filepath);


	// 指定されたデータを文字列で取得
	const std::string GetString(int row, int col);
	// 指定されたデータを整数で取得
	const int GetInt(int row, int col);
	// 指定されたデータを小数で取得
	const float GetFloat(int row, int col);

	// 行数の取得
	const int GetRowNum(void);

	// 列数の取得
	const int GetColNum(void);

	// 項目数の取得
	const int GetDataNum(void);


private:

	// 定数
	static const int LINE_CHAR_MAX;		// １行当たりの最大文字数

	// 読み込みデータ
	std::vector<std::string> m_Buffer;

	// 行数
	int m_RowNum;

};