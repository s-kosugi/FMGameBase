#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGame.h														*/
/*  @brief		:	ゲームクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/14													*/
/*																				*/
/*==============================================================================*/

#include "DxLib.h"
#include "BaseObject\IBaseSingleton.h"
#include "Utility/Vector/cVector2.h"

//===============================================================================
// ゲームクラス
class cGame : public IBaseSingleton<cGame>
{
public:
	~cGame();

	void Initialize(void);
	void Update(void);
	void Draw(void);
	IBaseObject* Finalize(void);


	// 乱数の発生
	static int Random(int min, int max);

	// FPSの取得
	inline unsigned int GetFPS(void) { return m_nFPS; };

	// プレイエリアの取得
	inline RECT GetPlayArea(void) { return m_PlayArea; };
	inline int  GetPlayAreaWidth(void) { return m_PlayArea.right - m_PlayArea.left; };
	inline int  GetPlayAreaHeight(void) { return m_PlayArea.bottom - m_PlayArea.top; };
	inline cVector2 GetPlayAreaCenter( void ){
		cVector2 center;
		center.x = (m_PlayArea.right - m_PlayArea.left) / 2.0f;
		center.y = (m_PlayArea.bottom - m_PlayArea.top) / 2.0f;
		return center;
	};

	// ウィンドウサイズの取得
	inline int GetWindowWidth(void) { int x, y; GetWindowSize(&x, &y); return x; };
	inline int GetWindowHeight(void) { int x, y; GetWindowSize(&x, &y); return y; };

	// ウィンドウの中心位置を取得
	inline cVector2 GetWindowCenter(void) { int x, y; GetWindowSize(&x, &y); cVector2 ret((float)(x / 2), (float)(y / 2)); return ret; };

	// 更新の回数のセット(1Frame内)
	inline int GetOneFrameUpdate(void) { return m_nOneFrameUpdate; };


	// FPSの設定
	inline void SetFPS(unsigned int fps) { m_nFPS = fps; };
	// FPSをリセット
	inline void ResetFPS(void) { m_nFPS = DEFAULT_FPS ;};

	// 更新の回数のセット(1Frame内)
	inline void SetOneFrameUpdate(int num) { m_nOneFrameUpdate = num; };

private:
	// FPS
	unsigned int m_nFPS;

	// 更新回数(1Frame内)
	int			 m_nOneFrameUpdate;

	// プレイエリア
	RECT	m_PlayArea;


	// デフォルトFPS
	static const unsigned int DEFAULT_FPS = 60;

	// プレイエリアの定義
	static const int  PLAYAREA_TOP = 0;
	static const int  PLAYAREA_BOTTOM = 600;
	static const int  PLAYAREA_LEFT = 0;
	static const int  PLAYAREA_RIGHT = 600;

};