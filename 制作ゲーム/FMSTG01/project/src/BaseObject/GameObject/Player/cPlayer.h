#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\cHitObject.h"

//================================================================================================
// プレイヤークラス
class cPlayer : public cHitObject
{
public:
	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// ボム残数の取得
	inline short GetBomNum( void ){ return m_nBomNum; };

private:
	//-----------------------------------------------------------------------
	// 定数

	// HP
	const int MAX_HP = 1000;

	// 移動速度
	const float MOVE_SPEED = 5.0f;

	// ゲーム開始位置
	const float START_POS_X = 300.0f;
	const float START_POS_Y = 700.0f;
	// 表示優先度
	const int	PRIORITY = 350;

	// 画像のサイズ
	const short SIZE_X = 64;
	const short SIZE_Y = 64;

	// アニメーション枚数
	const short ANIM_NUM = 3;

	// アニメーション時間
	const short ANIM_TIME = 4;

	// 当たり判定の大きさ
	const float HIT_RANGE = 15.0f;

	// 無敵時間(ダメージ時)
	const int FLASH_MAX_TIME = 60;

	// フラッシュの点滅間隔
	const int FLASH_INTERVAL = 5;

	// 煙の発生開始HPの割合
	const float SMOKE_START_RATE = 0.3f;
	// 煙の発生間隔
	const short SMOKE_START_INTERVAL = 30;
	// 煙の色
	const unsigned int SMOKE_COLOR = 0xffffffff;

	// 死亡後の待機時間
	const int DEAD_WAIT_TIME = 60;

	// 自機の弾の同時発射数
	static const int   BULLET_NUM = 4;
	// 弾の移動速度
	const float BULLET_SPEED = 18.0f;
	// 自機の弾の色
	const unsigned int BULLET_COLOR = 0xffaaaaff;
	// 自機の弾発射位置テーブル
	cVector2 SHOT_START_POS[BULLET_NUM] = { { -20.0f,0.0f } ,{ -12.0f,-4.0f } ,{ 12.0f,-4.0f } ,{ 19.0f,0.0f } };
	// 自機の左右のNway弾の数
	const short			NWAY_BULLET_NUM = 3;
	// nWay弾の発射間隔
	const float			NWAY_BULLET_ANGLE_INTERVAL = 8.0f;
	// nWay弾の開始角度
	const float			NWAY_BULLET_START_ANGLE = 15.0f;
	// 通常ショット発射間隔
	const short			SHOT_INTERVAL = 12;

	// ホーミング弾の移動速度
	const float HOMING_BULLET_SPEED = 9.0f;
	// ホーミング弾の回転角度
	const float HOMING_ROTATE = 5.0f;
	// ホーミング弾の最大数
	const unsigned int HOMING_MAX_NUM = 5;
	// ホーミング弾の色
	const unsigned int HOMING_COLOR = 0xffffaaff;
	// ホーミングレーザーの出現間隔
	const unsigned int HOMING_NEXT_POPTIME = 2;
	// レーザー発射状態時間
	const short LASER_STATE_TIME = 240;
	// レーザーの発射間隔
	const short LASER_SHOOT_INTERVAL = 10;
	// レーザー発射角度の範囲
	const int   LASER_ANGLE_RANGE = 80;
	// レーザーのエリアアウト補正値
	const int	LASER_AREAOUT_ADJUST = 80;
	// レーザーの攻撃力
	const int	LASER_ATK = 500;
	// ボム数の初期値
	const short DEFAULT_BOM_NUM = 5;

	//-----------------------------------------------------------------------
	// 状態別処理
	void Normal( void );
	void Hit( void );
	void Flash( void );
	void Dead( void );

	// キー操作処理
	void OperationKey( void );
	// 範囲外処理
	void ProcAreaOut( void );
	// 煙発生処理
	void AppeaSmoke( void );
	// レーザー発射処理
	void ShootLaser( void );

	// 煙の発生タイマー
	short m_nSmokeTimer;

	// 無敵時間
	int m_nFlashTimer;

	// 死亡後待機時間
	int m_nDeadTimer;

	// 通常弾発射間隔タイマー
	short m_nShotCoolTime;

	// レーザー発射状態管理タイマー
	short m_nLaserTimer;

	// ボムの残数
	short m_nBomNum;


	// 出現演出時の移動力
	cVector2 m_vPosUp;

	// 出現演出フラグ
	bool  m_bAppear;
};
//================================================================================================