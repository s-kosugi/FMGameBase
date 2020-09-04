#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cAngleBullet.h												*/
/*  @brief		:	角度指定弾クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cBulletBase.h"

//================================================================================================
// 角度指定弾クラス
class cAngleBullet : public cBulletBase
{
public:
	cAngleBullet(IBaseObject* parent);
	cAngleBullet(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cAngleBullet(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// 発射角度のセット
	// angle : 度数法の角度,0度が真下
	void SetShootAngle(float angle);

private:
	static const float HIT_RANGE;	// 当たり判定の大きさ
	static const int DEFAULT_ATK;	// デフォルト攻撃力
	static const int PRIORITY;		// 表示優先度

};
//================================================================================================