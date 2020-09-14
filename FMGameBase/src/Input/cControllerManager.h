#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cControllerManager.h										*/
/*  @brief		:	入力管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"

class cControllerManager : public IBaseObject
{
public:
	// 初期化
	void Initialize(void) override;

	// 更新
	void Update(void) override;

	// キー定義
	enum class KEY_DEFINE
	{
		KEY_LEFT = 0,
		KEY_UP,
		KEY_RIGHT,
		KEY_DOWN,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_PAUSE,


		KEY_ANY,		// 全てのキー

		KEY_MAX = KEY_ANY
	};

	// キー押下チェック(1P+キーボード用)
	bool CheckButton(KEY_DEFINE kcode);
	bool CheckTrigger(KEY_DEFINE kcode);
	bool CheckRelease(KEY_DEFINE kcode);

	// 振動開始
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	// Power : 0 ～ 1000
	// Time : 振動時間
	void StartVibration(int InputType, int Power, int Time);

	// 振動停止
	// InputType : パッド識別子 DX_INPUT_PAD1～4
	void StopVibration(int InputType);

	//-----------------------------------------------------------------------------------------------------
	// シングルトン用
private:
	cControllerManager(void) { };     //  他からの生成を禁止
	cControllerManager(IBaseObject* parent) {  };
	cControllerManager(IBaseObject* parent, const std::string& name) { };
	~cControllerManager(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cControllerManager(const cControllerManager& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cControllerManager& operator = (const cControllerManager& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) override { IBaseObject::Finalize(); return nullptr; };

	static cControllerManager& GetInstance(void) {
		static cControllerManager instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};