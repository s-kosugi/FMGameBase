#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.h												*/
/*  @brief		:	敵管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "EnemyID.h"
#include "Utility/Vector/cVector2.h"

// 前方宣言
class IEnemyBase;

// 敵管理クラス
class cEnemyManager : public IBaseObject
{
public:
	// コンストラクタ
	cEnemyManager( IBaseObject* pObj );
	~cEnemyManager( void );

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 敵生成
	IEnemyBase* Create( EnemyID id);

	// 当たり判定
	// vec 当たり判定をするオブジェクトの位置
	// dist 当たり判定をするオブジェクトの半径
	// return true プレイヤーの攻撃が当たった false プレイヤーの攻撃があたらなかった
	bool	JudgeHit( const cVector2& vec ,float dist ); 

	// プレイヤーとの当たり判定
	// vec プレイヤーの位置
	// dist プレイヤーの当たり判定半径
	// return true プレイヤーが敵の攻撃の範囲内 false プレイヤーが敵の攻撃の範囲外
	bool	JudgePlayer( const cVector2& vec ,float dist ); 
private:

	int		m_nTimer;		// 敵の出現制御タイマー

	static const int DEFAULT_POP_INTERVAL;			// 初期出現間隔
	static const int DIFFICULT_POP_RATE;			// 難易度による敵の出現頻度の倍率

};