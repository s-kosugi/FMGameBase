#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransition.h												*/
/*  @brief		:	トランジションクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/11													*/
/*																				*/
/*==============================================================================*/

#include "..\IDrawBase.h"
#include "Utility/Timer/cTimer.h"

//================================================================================================
// トランジションクラス
// ユニバーサルトランジションを行い、出現や消失演出の制御を行う

class cTransition : public IDrawBase
{
public:
	// トランジションを行う方向
	enum class TransDirection {
		TRANS_IN = 0,
		TRANS_OUT,
	};

	// -------------------------------------------------------------------------------------------
	// コンストラクタ
	// filename  : ルール画像のファイル名
	// pObj      : ブレンドする元画像のオブジェクトのポインタ
	// dir       : TRANS_IN フェードイン   TRANS_OUT フェードアウト
	// transtime : トランジション時間
	cTransition(const std::string& filename, IDrawBase* pObj, TransDirection dir, float transtime);

	// デストラクタ
	~cTransition();

	// 初期化
	void Initialize(void);
	// 更新
	void Update(void);
	// 破棄
	void Finalize(void);


	//---------------------------------------------------------------------
	// 定数

	// DrawBlendGraphで使う境界幅
	enum class BorderRange {
		RANGE_1 = 1,
		RANGE_64 = 64,
		RANGE_128 = 128,
		RANGE_255 = 255,
	};

	// Getter
	inline IDrawBase* GetTransObject(void) { return m_pTransObj; };
	inline float		GetBorderParam(void) { return m_fBorderParam; };
	inline BorderRange	GetBorderRange(void) { return m_eBorderRange; };

	// トランジションが終了したかどうか？
	//  ret : true 終了した false : 再生中
	bool				IsEnd(void);

	// Setter
	inline void SetTransTime(float time) { m_fTransTime = time; };
	inline void SetTransDirection(TransDirection value) { m_eTransDirection = value; value == TransDirection::TRANS_IN ? m_fBorderParam = 0.0f : m_fBorderParam = (float)BORDER_MAX; };

private:
	//---------------------------------------------------------------------
	// 定数

	static const float	BORDER_MAX;			// 境界位置の最大値
	static const int	DEFAULT_PRIORITY;	// 表示優先度



	IDrawBase* m_pTransObj;		// 遷移先の画像のポインタ
	BorderRange		m_eBorderRange;		// DrawBlendGraphで使う境界幅
	float			m_fBorderParam;		// DrawBlendGraphで使う境界位置
	TransDirection	m_eTransDirection;	// トランジションを行う方向(フェードインかアウトか)
	float			m_fTransTime;		// 合計トランジション時間(秒)
	cTimer			m_cTimer;			// トランジションタイマー
};