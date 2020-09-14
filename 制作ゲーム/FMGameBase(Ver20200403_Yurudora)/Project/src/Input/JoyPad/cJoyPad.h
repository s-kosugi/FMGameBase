#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cJoyPad.h													*/
/*  @brief		:	コントローラー入力クラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"
#include <DxLib.h>

class cJoyPad : public IBaseObject
{
public:
	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// ボタン押下チェック
	bool CheckButton(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 押しているか
	bool CheckTrigger(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 押した瞬間
	bool CheckRelease(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 離した瞬間

	// 振動の開始
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	// Power : 0 ～ 1000
	// Time : 振動時間
	void StartVibration(int InputType, int Power, int Time);

	// 振動の停止
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	void StopVibration(int InputType);

	// アナログ入力取得
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	POINT  GetAnalogInput(int InputType);

	// 接続台数取得
	inline int  GetConnectNum(void) { return m_nJoyPadNum; };

private:
	// DirectInput Joypad state
	int* m_diInputState;
	// 前フレーム情報
	int* m_diPrevInputState;

	// ジョイパッド接続数
	short m_nJoyPadNum;

	//-----------------------------------------------------------------------------------------------------
	// シングルトン用
private:
	cJoyPad(void);     //  他からの生成を禁止
	cJoyPad(IBaseObject* parent);
	cJoyPad(IBaseObject* parent, const std::string& name);
	~cJoyPad(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cJoyPad(const cJoyPad& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cJoyPad& operator = (const cJoyPad& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:

	static cJoyPad& GetInstance(void) {
		static cJoyPad instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};