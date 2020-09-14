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
#include "BaseObject\IBaseObject.h"
#include "Utility/Vector/cVector2.h"

//===============================================================================
// ゲームクラス
class cGame : public IBaseObject
{
public:
	void Initialize(void) override;
	void Update(void) override;
	void Draw(void);


	// 乱数の発生
	static int Random(int min, int max);

	//-----------------------------------------------------------------------------------------
	// Getter
	//-----------------------------------------------------------------------------------------
	// FPSの取得
	inline unsigned int GetFPS(void) { return m_nFPS; };

	// プレイエリアの取得
	inline RECT GetPlayArea(void) { return m_PlayArea; };
	inline int  GetPlayAreaWidth(void) { return m_PlayArea.right - m_PlayArea.left; };
	inline int  GetPlayAreaHeight(void) { return m_PlayArea.bottom - m_PlayArea.top; };

	// ウィンドウサイズの取得
	inline int GetWindowWidth(void) { return WINDOW_SIZE_X; };
	inline int GetWindowHeight(void) { return WINDOW_SIZE_Y; };

	// ウィンドウの中心位置を取得
	inline cVector2 GetWindowCenter(void) { cVector2 ret((float)(WINDOW_SIZE_X / 2), (float)(WINDOW_SIZE_Y / 2)); return ret; };

	// 更新の回数の取得(1Frame内)
	inline int GetOneFrameUpdate(void) { return m_nOneFrameUpdate; };

	// デルタタイム取得
	inline float GetDeltaTime(void) const { return m_fDeltaTime * m_fDeltaTimeScale; };

	// ウィンドウ位置を原点にする
	void SetWindowPosOrigin(void);

	// ウィンドウの位置を初期位置にする
	void SetWindowPosDefault(void);

	//-----------------------------------------------------------------------------------------
	// Setter
	//-----------------------------------------------------------------------------------------
	// FPSの設定
	inline void SetFPS(unsigned int fps) { m_nFPS = fps; };
	// FPSをリセット
	inline void ResetFPS(void) { m_nFPS = DEFAULT_FPS; };
	// 更新の回数のセット(1Frame内)
	inline void SetOneFrameUpdate(int num) { m_nOneFrameUpdate = num; };
private:
	// 更新するフレームカウントの計算
	void CalcFrameCount( void );

	// システムキーのチェック
	void CheckSystemKey(void);

	// ウィンドウ位置の切り替え
	void ChangeWindowPos(void);

	//-----------------------------------------------------------------------------------------
	// 変数
	//-----------------------------------------------------------------------------------------
	unsigned int	m_nFPS;				// FPS
	int				m_nOneFrameUpdate;	// 更新回数(1Frame内)
	float			m_fDeltaTime;		// デルタタイム
	float			m_fDeltaTimeScale;	// デルタタイム倍率
	int				m_nFrameCount;		// フレームカウント
	int				m_nStartTime;		// フレーム計測開始時間
	int             m_nPrevTime;		// 1フレーム前の時間

	POINT			m_DefaultWindowPos;	// 初期ウィンドウ位置

	RECT			m_PlayArea;			// プレイエリア

	//-----------------------------------------------------------------------------------------
	// 定数
	//-----------------------------------------------------------------------------------------
	static const unsigned int DEFAULT_FPS = 60; // デフォルトFPS
	static const float		  MAX_DELTA_TIME;	// 最大デルタタイム
	static const float		  ONE_MILL_SECOND;	// １ミリ秒
	static const int		  CALC_FRAME_COUNT; // 平均を計算するフレームの数

	static const int		  WINDOW_SIZE_X;	// ウィンドウ幅
	static const int		  WINDOW_SIZE_Y;	// ウィンドウ高さ

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cGame(void);     //  他からの生成を禁止
	cGame(IBaseObject* parent);
	cGame(IBaseObject* parent, const std::string& name);
	~cGame(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cGame(const cGame& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cGame& operator = (const cGame& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) override { IBaseObject::Finalize(); return nullptr; };

	static cGame& GetInstance(void) {
		static cGame instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
//-----------------------------------------------------------------------------------------------------
};