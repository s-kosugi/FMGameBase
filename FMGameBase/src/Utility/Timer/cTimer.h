#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTimer.h													*/
/*  @brief		:	タイマークラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/01/14													*/
/*																				*/
/*==============================================================================*/
#include "BaseObject/IBaseObject.h"

//================================================================================================
// タイマークラス
class cTimer : public IBaseObject
{
public:
	cTimer( IBaseObject* parent, const std::string& name );
	~cTimer(void);

	// 初期化
	// limit : 計測時間(秒)
	void    Setup(float limit);
	// 初期化
	// limit : 計測時間(秒)
	// scale : タイムスケール(1.0が等速)
	void    Setup(float limit, float scale);
	// 更新
	void    Update(void);
	// リセット
	inline void    Reset(void) { m_fCurrentTime = 0.0f; };

	// 終了判定
	// ret : true 指定時間を経過した false 指定時間を経過していない
	inline bool    Finished(void)const { return (m_fCurrentTime >= m_fLimitTime); };

	// 終了時間の取得
	inline float   GetTime(void) const		{ return m_fCurrentTime; };
	// 指定した限界時間の取得
	inline float   GetLimit(void) const		{ return m_fLimitTime; };
	// タイムスケールを取得
	inline float   GetTimeScale(void) const { return m_fTimeScale; };

	// 限界時間の設定
	void    SetLimit(float limit);
	// タイムスケールを設定
	inline void    SetTimeScale(float scale) { m_fTimeScale = scale; };

private:
	static const float  DEFAULT_TIME_SCALE;		 // 初期タイムスケール
	float               m_fCurrentTime;          // 現在の時間
	float               m_fLimitTime;            // 設定時間
	float               m_fTimeScale;            // タイムスケール

};
//================================================================================================