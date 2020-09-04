#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cXController.h												*/
/*  @brief		:	XBoxコントローラー入力クラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"
#include <DxLib.h>

class cXController : public IBaseObject
{
public:
	//--------------------------------------------------------------------
	// スティック入力方向
	enum class STICK_DIRECTION
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
	};

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// ボタン押下チェック
	bool CheckButton(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 押しているか
	bool CheckTrigger(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 押した瞬間
	bool CheckRelease(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 離した瞬間

	// 振動の開始
	// Power : 0 ～ 1000
	// Time : 振動時間
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	void StartVibration(int Power, int Time, int InputType = DX_INPUT_PAD1);

	// 振動の停止
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	void StopVibration(int InputType = DX_INPUT_PAD1);

	// 左スティックの取得
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	POINT  GetLeftAnalogInput(int InputType = DX_INPUT_PAD1);

	// 右スティックの取得
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	POINT  GetRightAnalogInput(int InputType = DX_INPUT_PAD1);

	// 左アナログスティックのトリガー判定
	//  direction		direction 方向ID
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	//    DX_INPUT_PAD1　　　　: パッド１
	//    DX_INPUT_PAD1　　　　: パッド２
	//   …
	//  戻り値 : true 倒された瞬間
	bool   IsTriggerLeftAnalog(STICK_DIRECTION direction, int InputType = DX_INPUT_PAD1);

	// 右アナログスティックのトリガー判定
	//  direction		direction 方向ID
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	//    DX_INPUT_PAD1　　　　: パッド１
	//    DX_INPUT_PAD1　　　　: パッド２
	//   …
	//  戻り値 : true 倒された瞬間
	bool   IsTriggerRightAnalog(STICK_DIRECTION direction, int InputType = DX_INPUT_PAD1);

	// 左トリガーの取得
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	// 戻り値 : 左トリガー入力値
	unsigned char  GetLeftTriggerInput(int InputType = DX_INPUT_PAD1);

	// 右トリガーの取得
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	// 戻り値 : 右トリガー入力値
	unsigned char  GetRightTriggerInput(int InputType = DX_INPUT_PAD1);

	// 左トリガーのトリガー判定
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	//    DX_INPUT_PAD1　　　　: パッド１
	//    DX_INPUT_PAD1　　　　: パッド２
	//   …
	//  戻り値 : true 押された瞬間
	bool   IsTriggerLeftTrigger(int InputType = DX_INPUT_PAD1);

	// 右トリガーのトリガー判定
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	//    DX_INPUT_PAD1　　　　: パッド１
	//    DX_INPUT_PAD1　　　　: パッド２
	//   …
	//  戻り値 : true 押された瞬間
	bool   IsTriggerRightTrigger(int InputType = DX_INPUT_PAD1);

	// 左トリガーのボタン判定
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	//    DX_INPUT_PAD1　　　　: パッド１
	//    DX_INPUT_PAD1　　　　: パッド２
	//   …
	//  戻り値 : true 押されてる間
	bool   IsButtonLeftTrigger(int InputType = DX_INPUT_PAD1);

	// 右トリガーのボタン判定
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	//    DX_INPUT_PAD1　　　　: パッド１
	//    DX_INPUT_PAD1　　　　: パッド２
	//   …
	//  戻り値 : true 押されてる間
	bool   IsButtonRightTrigger(int InputType = DX_INPUT_PAD1);

	// 左トリガーのリリース判定
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	//    DX_INPUT_PAD1　　　　: パッド１
	//    DX_INPUT_PAD1　　　　: パッド２
	//   …
	//  戻り値 : true 離された瞬間
	bool   IsReleaseLeftTrigger(int InputType = DX_INPUT_PAD1);

	// 右トリガーのリリース判定
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	//    DX_INPUT_PAD1　　　　: パッド１
	//    DX_INPUT_PAD1　　　　: パッド２
	//   …
	//  戻り値 : true 離された瞬間
	bool   IsReleaseRightTrigger(int InputType = DX_INPUT_PAD1);

	// 接続台数取得
	// 戻り値 : 接続台数
	inline int  GetConnectNum(void) { return m_nJoyPadNum; };

private:

	// XInput Joypad state
	XINPUT_STATE* m_xiInputState;
	// 前フレーム情報
	XINPUT_STATE* m_xiPrevInputState;

	// Xコントローラー接続数
	short m_nJoyPadNum;

	//--------------------------------------------------------------------
	// 定数
	static const int	LIMIT_CANT_ANALOG;		// アナログスティックの遊び
	static const int	LIMIT_CANT_TRIGGER;		// トリガーの遊び

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cXController(void);     //  他からの生成を禁止
	cXController(IBaseObject* parent);
	cXController(IBaseObject* parent, const std::string& name);
	~cXController(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cXController(const cXController& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cXController& operator = (const cXController& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cXController& GetInstance(void) {
		static cXController instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};