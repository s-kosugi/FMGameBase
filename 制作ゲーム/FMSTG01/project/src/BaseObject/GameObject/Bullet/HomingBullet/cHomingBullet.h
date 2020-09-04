#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingBullet.h												*/
/*  @brief		:	ホーミング弾クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "..\cBulletBase.h"

//================================================================================================
// ホーミング弾クラス
class cHomingBullet : public cBulletBase
{
public:
	cHomingBullet(IBaseObject* parent);
	cHomingBullet(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cHomingBullet(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// 回転上限角度の設定
	inline void SetRotLimit(float rot) { m_fRotLimit = rot; };

	// 常時サーチフラグの設定
	inline void SetAlwaysSearch(bool flg) { m_bAlwaysSearch = flg;};

	// 一番近いターゲットに設定する
	inline void SetNearTarget(void) { m_pTargettingObj = SearchTargettingObject();};

	// ランダムなターゲットに設定する
	cSpriteObject* SetRandomTarget( void );

	// 発射角度の設定
	void SetShootAngle(float angle);

protected:
	// ホーミングの移動ベクトルを求める
	void CalcHomingMove(cVector2& hVec, const cVector2& trgPos);

	// 追尾対象へ移動するベクトルを求める
	void CalcTargetVector(const cVector2& tPos, cVector2& tVec);

	// 旋回上限角度を加味した移動ベクトルを求める
	void CalcRotateLimit(cVector2& rVec, const cVector2& srcVec, const cVector2& trgVec, const cVector2& trgPos);

	// 追尾対象を決定する
	cSpriteObject* SearchTargettingObject( void );
	// 追尾対象の敵を探す
	cSpriteObject* SearchTargettingEnemy( void );
	// 追尾対象が存在しているかどうか
	bool IsSearchTargetAlive( void );
	

	// 旋回上限角度
	float m_fRotLimit;

	// 常時サーチフラグ
	bool m_bAlwaysSearch;

	// 追尾対象
	cSpriteObject* m_pTargettingObj;

	// 弾の生存時間
	int	 m_nLifeTime;

private:
	//-------------------------------------------------------------------------------------------
	// 定数
	static const float HIT_RANGE;		// 当たり判定の大きさ
	static const int   PRIORITY;		// 表示優先度
	static const float ROT_LIMIT;		// 旋回上限角度初期値
	static const int   LIFE_TIME;		// 弾の生存時間初期値
	static const int   DEFAULT_ATK;		// デフォルト攻撃力

};
//================================================================================================