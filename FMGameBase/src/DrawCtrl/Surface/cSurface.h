#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSurface.h													*/
/*  @brief		:	サーフェイスクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/02/26													*/
/*																				*/
/*==============================================================================*/

#include "..\IDrawBase.h"
#include "..\..\Utility\Vector\cVector3.h"

//================================================================================================
// サーフェイスクラス
// m_cBeginPointに登録されているPriorityからcSurfaceのPriorityまでの範囲の描画オブジェクトを１オブジェクトとして操作ができる
// 主に画面効果や多人数プレイでの画面分割に使う

class cSurface : public IDrawBase
{
public:
	cSurface(int width, int height, int beginPriority, int endPriority, bool alpha);
	~cSurface();

	// フィルターモード
	enum class FILTER_MODE {
		NONE,
		MONO,		// モノトーン
		GAUSS,		// ガウス
		HSB,		// 色相・再度・明度
		INVERT,		// 階調の反転
	};

	// Getter
	inline float		GetAngle(void) { return m_fAngle; };
	inline cVector2		GetCenter(void) { return m_vCenter; };
	inline RECT			GetRect(void) { return m_Rect; };
	inline int			GetBlendMode(void) { return m_nBlendMode; };
	inline cVector2		GetScale(void) { return m_vScale; };
	inline IDrawBase* GetBeginPointer(void) { return &m_cBeginPoint; };
	inline FILTER_MODE	GetFilterMode(void) { return m_eFilterMode; };
	inline int			GetMonoBlue(void) { return m_nMonoBlue; };
	inline int			GetMonoRed(void) { return m_nMonoRed; };
	inline int			GetGaussPixelWidth(void) { return m_nGaussPixelWidth; };
	inline int			GetGaussParam(void) { return m_nGaussParam; };
	inline int			GetHSBHue(void) { return m_nHSBHue; }
	inline int			GetHSBSaturation(void) { return m_nHSBSaturation; }
	inline int			GetHSBBright(void) { return m_nHSBBright; }
	inline bool			IsShow(void) { return m_bShow; };

	// Setter
	inline void SetAngle(float angle) { m_fAngle = angle; };
	inline void SetCenter(float x, float y) { m_vCenter.x = x; m_vCenter.y = y; };
	inline void SetCenter(cVector2 center) { m_vCenter = center; };
	inline void SetRect(RECT rect) { m_Rect = rect; };
	inline void SetBlendMode(int mode) { m_nBlendMode = mode; };
	inline void SetScale(cVector2 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = scale; };
	inline void SetBeginPriority(int pri) { m_cBeginPoint.SetPriority(pri); };
	inline void SetFilterMode(FILTER_MODE mode) { m_eFilterMode = mode; };
	inline void SetMonoBlue(int param) { m_nMonoBlue = param; };
	inline void SetMonoRed(int param) { m_nMonoRed = param; };
	inline void SetGaussPixelWidth(int param) { m_nGaussPixelWidth = param; };
	inline void SetGaussParam(int param) { m_nGaussParam = param; };
	inline void SetHSBHue(int hue) { m_nHSBHue = hue; };
	inline void SetHSBSaturation(int saturation) { m_nHSBSaturation = saturation; };
	inline void SetHSBBright(int bright) { m_nHSBBright = bright; };
	inline void SetShow(bool flg) { m_bShow = flg; };

protected:
	float	  m_fAngle;			// 回転
	cVector2  m_vCenter;		// 中心位置
	RECT	  m_Rect;			// 描画矩形の始点と終点
	int		  m_nBlendMode;		// 描画ブレンドモード
	cVector2  m_vScale;			// 拡大縮小

	IDrawBase m_cBeginPoint;	// サーフェイスの描画開始ポイントの設定(Priorityで指定)
	bool	  m_bShow;			// 生成したサーフェイスを表示するかどうか(cTransition等で作成をしておくが表示をしない場合に使用)


	//----------------------------------------------------------------------------------
	// フィルターモード用変数
	FILTER_MODE	m_eFilterMode;

	// モノトーンフィルタ用青色差(-255～255)
	int			m_nMonoBlue;
	// モノトーンフィルタ用赤色差(-255～255)
	int			m_nMonoRed;

	// ガウスフィルタ用使用ピクセル幅(8,16,32の何れか)
	int			m_nGaussPixelWidth;
	// ガウスフィルタ用ぼかしパラメータ(100で1ピクセル分の幅)
	int			m_nGaussParam;

	// HSB用色相設定(-180～180)
	int			m_nHSBHue;
	// HSB用彩度設定(-255～)
	int			m_nHSBSaturation;
	// HSB用明度設定(-255～255)
	int			m_nHSBBright;


};