#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.h													*/
/*  @brief		:	ゲームメインシーン											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// ゲームメインシーン
class cGameMain : public IBaseScene
{
public:
	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize( void );
	void Update( void );
	IBaseObject* Finalize( void );

	// ゲーム状態の設定
	enum class GAME_STATE
	{
		START = 0,
		PLAY,
		OVER
	};

	// 難易度の取得
	inline int			GetDifficult( void ) { return m_nDifficult; };

	// ゲーム状態の取得
	inline GAME_STATE	GetGameState( void ) { return m_eGameState;};

	// ゲーム状態の設定
	inline void			SetGameState( GAME_STATE st ) { m_eGameState = st; };

	// 地面のラインの取得
	inline int			GetLandingLine( void ){ return LANDING_LINE; };

private:
	// ゲーム開始
	void Start(void);
	// ゲーム中
	void Play(void);
	// ゲームオーバー
	void Over(void);

	int			m_nDifficult;			// 難易度 数字が少ないほど易しい
	GAME_STATE	m_eGameState;			// ゲーム状態

	//--------------------------------------------------------------------------------------------
	// 定数
	static const float LEVELUP_TIME;	// 難易度が上がるまでの時間(秒)
	static const int MAX_DIFFICULT;		// 最大難易度
	static const float GAMEOVER_TIME;	// ゲームオーバー状態の時間
	static const int LANDING_LINE;		// 地面のライン
	static const float GAMESTART_TIME;	// ゲームスタート状態の時間
};
//================================================================================================