#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSnipeBullet.h												*/
/*  @brief		:	狙い撃ち弾クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\cBulletBase.h"

//================================================================================================
// 狙い撃ち弾クラス
class cSnipeBullet : public cBulletBase
{
public:
	cSnipeBullet(IBaseObject* parent);
	cSnipeBullet(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cSnipeBullet(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// 発射角度の設定
	void SetShootAngle(float angle);

	// 追尾対象へ移動するベクトルを求める
	void CalcTargetVector(const cVector2& tPos);

private:
	//-------------------------------------------------------------------------------------------
	// 定数
	static const float HIT_RANGE;	// 当たり判定の大きさ
	static const int PRIORITY;		// 表示優先度
	static const int DEFAULT_ATK;	// デフォルト攻撃力
};
//================================================================================================