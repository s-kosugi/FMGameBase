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

class cCsvReader : public IBaseObject
{
public:
	// 初期化
	void Initialize(void);

	// CSVファイル読み込み
	void LoadFile(const std::string filepath, std::vector<std::string>& buf);

private:

	// １行単位の文字列を項目毎に分割する
	void SplitCsv(const std::string & str, std::vector<std::string>& buf);

	// 定数
	static const int LINE_CHAR_MAX;		// １行当たりの最大文字数


//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cCsvReader(void) { };     //  他からの生成を禁止
	cCsvReader(IBaseObject* parent) {  };
	cCsvReader(IBaseObject* parent, const std::string& name) { };
	~cCsvReader(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cCsvReader(const cCsvReader& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cCsvReader& operator = (const cCsvReader& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public :
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cCsvReader& GetInstance(void) {
		static cCsvReader instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
//-----------------------------------------------------------------------------------------------------
};