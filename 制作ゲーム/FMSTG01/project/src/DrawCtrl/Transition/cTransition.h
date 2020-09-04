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
#include "..\..\Utility\Vector\cVector3.h"

//================================================================================================
// トランジションクラス
// 画面切り替え効果用

class cTransition : public IDrawBase
{
public:
	cTransition(const std::string& filename, IDrawBase* pObj);
	~cTransition();

	void Initialize(void);
	void Update(void);
	void Finalize(void);


	//---------------------------------------------------------------------
	// 定数
	static const std::string RULE_CHECKSPHERE;	// ルール画像ファイル(チェック+球状)

	// DrawBlendGraphで使う境界幅
	enum BorderRange {
		RANGE_1 = 1,
		RANGE_64 = 64,
		RANGE_128 = 128,
		RANGE_255 = 255,
	};

	// トランジションを行う方向
	enum TransDirection {
		TRANS_IN = 0,
		TRANS_OUT,
	};

	// Getter
	inline IDrawBase*	GetTransObject( void ) { return m_pTransObj; };
	inline float		GetBorderParam( void ) { return m_fBorderParam; };
	inline BorderRange	GetBorderRange( void ) { return m_eBorderRange; };
	bool				IsEnd( void );

	// Setter
	inline void SetBorderParamAdd(float value) { m_fBorderParam_Add = value;};
	inline void SetTransDirection(TransDirection value) { m_eTransDirection = value; value == TRANS_IN ? m_fBorderParam = 0.0f : m_fBorderParam = (float)BORDER_MAX; };

private:
	//---------------------------------------------------------------------
	// 定数
	
	static const int		BORDER_MAX;			// 境界位置の最大値
	static const float		BORDER_ADD_DEFAULT;	// 境界位置の増分値の初期値
	static const int		DEFAULT_PRIORITY;	// 表示優先度



	IDrawBase*		m_pTransObj;		// 遷移先の画像のポインタ
	BorderRange		m_eBorderRange;		// DrawBlendGraphで使う境界幅
	float			m_fBorderParam;		// DrawBlendGraphで使う境界位置
	float			m_fBorderParam_Add;	// 1フレーム辺りで増える境界位置の増分値
	TransDirection	m_eTransDirection;	// トランジションを行う方向(フェードインかアウトか)
};