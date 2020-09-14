#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDebugFunc.h												*/
/*  @brief		:	デバッグ機能クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/24													*/
/*																				*/
/*==============================================================================*/
#ifdef DEBUG

#include "DxLib.h"
#include "..\BaseObject\IBaseObject.h"
#include <string>
#include "Utility/Vector/cVector2.h"

//===============================================================================
// デバッグ機能クラス
class cDebugFunc : public IBaseObject
{
public:
	void Initialize(void);
	void Update(void);
	void Draw(void);

	// デバッグログ追加
	void PushDebugLog(std::string str);

	// デバッグログ最大出力数設定
	inline void SetDebugLogMax(int num) { m_nMaxLog = num; };
	// デバッグログ追加 str : 出力したい文字列  num : 出力したい数値
	void PushDebugLog(std::string str, float num);
	// デバッグログ追加 str : 出力したい文字列  num : 出力したい数値
	void PushDebugLog(std::string str, int num);

	// 円描画登録(1フレーム間描画)
	// pos   : 指定ポイント
	// range : 指定ポイントからの範囲(半径）
	// color : 描画色(ARGB)
	void RegistDrawCircle(const cVector2& pos, float range,unsigned int color);

	// 矩形描画登録(1フレーム間描画)
	// pos   : 指定ポイント
	// range : 指定ポイントからの範囲
	// color : 描画色(ARGB)
	void RegistDrawBox(const cVector2& pos, POINT range,unsigned int color);

private:
	enum class PRINTMODE
	{
		ALL,		// 説明表示あり
		LOG,		// 説明表示なし
		NONE,		// デバッグ表示オフ

		MAX
	};
	// デバッグ用円描画構造体
	struct DebugCircle {
		cVector2 pos = {0.0f,0.0f};
		float range = 0.0f;
		unsigned int color = 0xffffffff;
	};
	// デバッグ用矩形描画構造体
	struct DebugBox {
		cVector2 pos = {0.0f,0.0f};
		POINT range = {0,0};
		unsigned int color = 0xffffffff;
	};


	// デバッグ用更新速度変更
	void DebugChangeUpdateSpeed(void);

	// デバッグシーンリセット
	void DebugSceneReset(void);

	// デバッグ出力
	void DebugPrint(void);

	// デバッグ図形描画
	void DrawShape(void);

	// フレームレート計算
	void CalcFrameRate(void);

	// スクリーンショット撮影
	void SaveScreenShot(void);

	//---------------------------------------------------------
	// フレームレート計算用
	int m_nStartTime;
	int m_nFrameCount;
	float m_fFrameLate;
	//---------------------------------------------------------

	std::list<std::string> m_listLog;		// デバッグログ
	int m_nMaxLog;							// デバッグログ最大表示行数
	int m_nLogNum;							// ログNo

	PRINTMODE m_eDebugPrintMode;		// デバッグ表示の切り替え 0:ログ、ヘルプ表示 1:ログのみ表示 2:非表示

	int m_nFPSMode;							// 0:初期値 1:少し早い 2:速い -1:少し遅い -2:遅い

	int m_nDebugFontHandle;					// フォントのハンドル

	std::list<DebugCircle> m_listDrawCircle;// デバッグ円描画リスト
	std::list<DebugBox> m_listDrawBox;		// デバッグ矩形描画リスト


	static const int FPS_MODE_MAX;			// 更新フレームモード最大
	static const int FONT_SIZE;				// フォントサイズ
	static const int LOG_MAX;				// ログ表示最大数

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cDebugFunc(void);     //  他からの生成を禁止
	cDebugFunc(IBaseObject* parent);
	cDebugFunc(IBaseObject* parent, const std::string& name);
	~cDebugFunc(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cDebugFunc(const cDebugFunc& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cDebugFunc& operator = (const cDebugFunc& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cDebugFunc& GetInstance(void) {
		static cDebugFunc instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
//-----------------------------------------------------------------------------------------------------
};
#endif // DEBUG