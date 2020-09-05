#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cMouse.h													*/
/*  @brief		:	マウス入力クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"
#include <DxLib.h>

class cMouse : public IBaseObject
{
public:
	void Initialize(void);
	void Update(void);

	// マウスボタン押下チェック
	bool CheckButton(unsigned int kcode); // 押しているか
	bool CheckTrigger(unsigned int kcode); // 押した瞬間
	bool CheckRelease(unsigned int kcode); // 離した瞬間

	// マウス座標の設定
	void SetPoint(int x, int y);
	void SetPoint(POINT pt);

	// マウス座標の取得
	POINT GetPoint(void);

private:
	// MouseButton state
	int m_nButtonState;
	int m_nPrevButtonState;

	//-----------------------------------------------------------------------------------------------------
	// シングルトン用
private:
	cMouse(void);     //  他からの生成を禁止
	cMouse(IBaseObject* parent);
	cMouse(IBaseObject* parent, const std::string& name);
	~cMouse(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cMouse(const cMouse& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cMouse& operator = (const cMouse& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cMouse& GetInstance(void) {
		static cMouse instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};