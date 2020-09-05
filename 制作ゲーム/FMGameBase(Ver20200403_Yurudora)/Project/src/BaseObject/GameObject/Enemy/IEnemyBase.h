#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IEnemyBase.h												*/
/*  @brief		:	敵ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// 敵ベースクラス
class IEnemyBase : public cSpriteObject
{
public:
	IEnemyBase(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~IEnemyBase(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// 死亡処理
	virtual void Dead( void );

	// 攻撃開始
	virtual void StartAttack(void);		

	// 当たり判定の半径を取得
	inline float GetDist( void ) { return m_fDist; };
protected:
	cVector2	m_vPosUp;		// 移動値
	int			m_nScore;		// 獲得スコア
	float		m_fDist;		// 当たり判定の半径


	// エリアアウト処理
	void AreaOutLeftProc( void );
	void AreaOutUpProc( void );
	void AreaOutRightProc( void );
	void AreaOutBottomProc( void );
	void AreaOutAllProc( void );

	static const int	AREAOUT_ADJUST;	// エリアアウト距離
	static const int	ATTACK_POS;		// 攻撃座標
	static const float	HIT_DIST;		// 当たり判定の半径
};
//================================================================================================