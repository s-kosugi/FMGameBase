#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cAnimSprite.h												*/
/*  @brief		:	アニメーションスプライトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/14													*/
/*																				*/
/*==============================================================================*/

#include "cSprite.h"
#include <string>
#include <vector>

//================================================================================================
// アニメーションスプライトクラス
class cAnimSprite : public cSprite
{
public:
	cAnimSprite(const std::string& filename);
	~cAnimSprite();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// アニメーション情報
	struct AnimationData {
		std::string         Name;				// アニメーション名
		std::vector<int>    Frames;				// フレームデータ
		float               Interval = 0.0f;	// 更新間隔(秒単位)
		bool                Loop = false;       // ループフラグ
	};

	// アニメーションの変更
	void ChangeAnime(const std::string& animName);
	// アニメーションの変更
	void ChangeAnime(int animID);

	// アニメーションのコピー
	void CopyAnime(const cAnimSprite& src);

	//---------------------------------------------------------------------------------------------
	// Getter
	inline POINT	GetFrameSize(void) { return m_FrameSize; };
	inline int		GetFrameCols(void) { return m_nFrameCols; };
	inline int		GetFrameRows(void) { return m_nFrameRows; };
	inline int		GetCurrentAnimeID(void) { return m_nCurrentAnimeID; };
	inline float	GetCurrentFrame(void) { return m_fCurrentFrame; };
	inline float	GetCurrentAnimeFPS(void) { return m_fCurrentAnimeFPS; };
	inline int		IsStop(void) { return m_bStopFlag; };
	inline float	GetPlaySpeedRate(void) { return m_fPlaySpeedRate; };

	//---------------------------------------------------------------------------------------------
	// Setter
	inline void		SetFrameCols(short col) { m_nFrameCols = col; };
	inline void		SetFrameRows(short row) { m_nFrameRows = row; };
	inline void		SetPlayRate(float rate) { m_fPlaySpeedRate = rate; };
	inline void		SetCurrentFrame(float frame) { m_fCurrentFrame = frame; };


	// 旧FMGB互換用アニメーションセット関数
	void SetAnimation(int Startx, int Starty, int width, int height, short AnimMax, float AnimTime);

protected:

	//---------------------------------------------------------------------------------------------
	// アニメーションデータリスト
	typedef std::vector<AnimationData> ANIMATION_LIST;


private:

	// ASSファイルからのスプライトキーID
	enum ASS_KEY
	{
		ASS_KEY_FILE,           // 使用するファイル名
		ASS_KEY_FRAME,          // フレームオブジェクト
		ASS_KEY_WIDTH,          // フレームの幅
		ASS_KEY_HEIGHT,         // フレームの高さ
		ASS_KEY_COLS,           // 横に並んでいるフレームの数
		ASS_KEY_ROWS,           // 縦に並んでいるフレームの数
		ASS_KEY_ANIMATIONS,     // アニメーションオブジェクト
		ASS_KEY_FRAMES,         // アニメーションで使用するフレーム番号
		ASS_KEY_INTERVAL,       // アニメーション更新間隔(秒単位)
		ASS_KEY_LOOP,           // アニメーションループフラグ

		ASS_KEY_MAX             // ASSキーの数
	};

	bool LoadASS(const std::string& filename);		// ASSファイルの読込と解析


	// アニメーション全体で必要な変数
	POINT		m_FrameSize;		// 1枚毎の大きさ
	short		m_nFrameCols;		// 横に並んでいるフレーム数
	short		m_nFrameRows;		// 縦に並んでいるフレーム数

	ANIMATION_LIST	m_AnimationList;            // アニメーションリスト

	// アニメーション再生用変数
	int				m_nCurrentAnimeID;		// 現在のアニメーションID
	float			m_fCurrentFrame;		// 現在のアニメーションフレーム
	float			m_fCurrentAnimeFPS;		// 現在のアニメーション更新速度
	bool			m_bStopFlag;			// 停止フラグ
	float			m_fPlaySpeedRate;		// アニメーションの再生速度倍率


	//---------------------------------------------------------------------------------------------
	// 定数
	static const char* m_sKeyName[ASS_KEY_MAX];   // キー名

};
//=================================================================================================
