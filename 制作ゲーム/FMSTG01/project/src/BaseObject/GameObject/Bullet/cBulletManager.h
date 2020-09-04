#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletManager.h											*/
/*  @brief		:	弾管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "BulletID.h"
#include "..\..\..\Utility\Vector\cVector2.h"

// 弾ベースクラスの前方宣言
class cBulletBase;

class cBulletManager : public IBaseSingleton<cBulletManager>
{
public:
	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 弾生成
	// type : 弾の種類  startPos : 弾の開始位置  hitCategory : 弾の当たり判定区分(HIT_PLAYER or HIT_ENEMY) speed : 弾の移動速度
	// 戻り値 : 生成した弾のポインタ
	cBulletBase* Create( BulletType type, const cVector2& startPos , int hitCategory,float speed, unsigned int color = 0x00ffffff, const std::string& filename = "none");

	// nWay弾の生成
	// bulletNum : 弾の発射数 angleInterval : 発射角度間隔 startAngle : 開始角度 color : 弾色
	void CreateNWayBullet(const cVector2& startPos, int hitCategory, float speed, const int bulletNum, float angleInterval, float startAngle, unsigned int color = 0x00ffffff, BulletType type = BT_ANGLE,const std::string& = "none");
	
private:

};