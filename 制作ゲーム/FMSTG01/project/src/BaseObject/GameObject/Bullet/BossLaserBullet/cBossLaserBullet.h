#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossLaserBullet.h											*/
/*  @brief		:	ボスレーザークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/24													*/
/*																				*/
/*==============================================================================*/

#include "..\cBulletBase.h"

//================================================================================================
// ボスレーザークラス
class cBossLaserBullet : public cBulletBase
{
public:
	cBossLaserBullet(IBaseObject* parent);
	cBossLaserBullet(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cBossLaserBullet(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// レーザー配置の開始
	void StartConfig( float fAngle  );

	// 発射角度のセット
	// angle : 度数法の角度,0度が真下
	void SetShootAngle(float angle);

	// オブジェクトの生存時間
	inline void SetLifeCounter(short time) { m_nLifeCounter = time; };

private:
	static const float HIT_RANGE;	// 当たり判定の大きさ
	static const int DEFAULT_ATK;	// デフォルト攻撃力
	static const int PRIORITY;		// 表示優先度
	static const short DEFAULT_LIFETIME; // デフォルト生存時間

	short			 m_nLifeCounter;	// オブジェクトの生存時間

};
//================================================================================================