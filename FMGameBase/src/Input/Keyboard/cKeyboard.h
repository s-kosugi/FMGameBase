#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cKeyboard.h													*/
/*  @brief		:	キーボード入力クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"

class cKeyboard : public IBaseObject
{
public:
	// 初期化
	void Initialize(void);

	// 更新
	void Update( void );

	// キー押下チェック
	bool CheckButton(unsigned int kcode); // 押しているか
	bool CheckTrigger(unsigned int kcode); // 押した瞬間
	bool CheckRelease(unsigned int kcode); // 離した瞬間
	
private:
	// DirectInput keyboard state
	char m_diKeyState[256];
	// 前フレーム情報
	char m_diPrevKeyState[256];

	// 定数
	static const int KEY_STATE_NUM = 256;

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cKeyboard(void);     //  他からの生成を禁止
	cKeyboard(IBaseObject* parent);
	cKeyboard(IBaseObject* parent, const std::string& name);
	~cKeyboard(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cKeyboard(const cKeyboard& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cKeyboard& operator = (const cKeyboard& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cKeyboard& GetInstance(void) {
		static cKeyboard instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
//-----------------------------------------------------------------------------------------------------
};