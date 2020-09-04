#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTargetEffect.h												*/
/*  @brief		:	ターゲットエフェクトクラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "..\cSpEffectObject.h"

//================================================================================================
// ターゲットエフェクトエフェクトクラス
class cTargetEffect : public cSpEffectObject
{
public:
	cTargetEffect(IBaseObject* parent);
	~cTargetEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// 追尾対象が生きているかどうか
	bool IsSearchTargetAlive(void);

	// 追尾対象の重複チェック
	static bool CheckDupulication(cSpriteObject* pObj);

	inline void SetTargetObject(cSpriteObject* pObj) { m_pTargetObj = pObj ;};

	inline cSpriteObject* GetTargetObject(void) { return m_pTargetObj; };
private:
	// ターゲットスプライトのアニメーション状態
	enum TARGET_ANM_STATE
	{
		TG_APPEAR,		// 出現
		TG_FLASH,		// 点滅
		TG_NORMAL,		// 通常
	};

	// 定数	
	// 表示優先度
	const int	PRIORITY = 500;

	// 色
	const unsigned int SPRITE_COLOR = 0xffff8888;
	// ターゲットサイト回転値
	const float ANGLE_ADD = 1.0f;
	// 生存時間デフォ値
	const unsigned int LIFE_TIME = 180;
	// 拡大率初期値
	const float SCALE_RATE = 3.0f;
	// エフェクトが完全に出現するまでの時間
	const unsigned int   APPEAR_TIME = 30;
	// 円部分の大きさ最大値
	const float  CIRCLE_SCALE_MAX = 2.4f;
	// 円部分のターゲットロックオン状態の色
	const unsigned int CIRCLE_DICISION_COLOR = 0xff88ff88;

	// 点滅間隔
	const int	FLASH_INTERVAL = 9;
	// 点滅終了時間
	const unsigned int FLASH_TIME = 50;
	// 円部分の拡縮間隔
	const int CIRCLE_SCALE_INTERVAL = 40;
	// 円部分の拡縮範囲
	const float CIRCLE_SCALE_RANGE = 0.1f;
	
	// アニメーション状態
	TARGET_ANM_STATE m_eAnimState;

	// 追従するオブジェクトのポインタ
	cSpriteObject* m_pTargetObj;

	// 生存時間
	unsigned int m_nLifeTime;

	// サークルスプライトのポインタ
	cSpriteObject* m_pCircleSprite;


	// 状態別処理
	// 出現時処理
	void Appear( void );
	// 点滅時処理
	void Flash( void );
	// 通常自処理
	void Normal( void );

};
//================================================================================================