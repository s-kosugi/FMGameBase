#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// プレイヤークラス
class cPlayer : public cSpriteObject
{
public:
	cPlayer( IBaseObject* parent );
	~cPlayer( void );

	void Initialize( void );
	void Update( void );
	IBaseObject* Finalize( void );


	// プレイヤーの当たり判定取得
	inline int GetPlayerDist( void ) { return PLAYER_DIST; };
private:

	cVector2	m_vPosUp;			// 移動速度
	cVector2	m_vAccele;			// 加速度
	bool		m_bLand;			// 接地フラグ
	int			m_nFailedTimer;		// 攻撃失敗タイマー


	void JumpWalk( void );			// ジャンプ移動
	void Attack( void );			// 攻撃

	//--------------------------------------------------------------------------------------------
	// 定数
	static const float	START_POS_X;			// ゲーム開始位置x
	static const float	START_POS_Y;			// ゲーム開始位置y
	static const int	PRIORITY = 200;			// 表示優先度
	static const int	LANDING_LINE = 100;		// 接地ライン
	static const float	JUMP_POWER;				// ジャンプ力
	static const float	GRAVITY;				// 重力加速度
	static const int	ATTACK_POS = 300;		// 攻撃エフェクト再生位置
	static const int	ATTACK_RANGE = 200;		// プレイヤーの攻撃範囲
	static const int	FAILED_TIME = 60;		// 攻撃失敗時の攻撃不能時間
	static const int	PLAYER_DIST = 200;		// プレイヤー本体の当たり判定半径


	//--------------------------------------------------------------------------------------------

};
//================================================================================================