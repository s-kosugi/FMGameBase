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
	cSurface(void);
	~cSurface();

	void Create(int width, int height, int beginPriority, int endPriority, bool alpha = true);
	void Delete(void);

	// Getter
	inline cVector3		GetAngle(void) { return m_vAngle; };
	inline cVector2		GetCenter(void) { return m_vCenter; };
	inline RECT			GetRect(void) { return m_Rect; };
	inline int			GetBlendMode(void) { return m_nBlendMode; };
	inline cVector2		GetScale(void) { return m_vScale; };
	inline IDrawBase*	GetBeginPointer(void) { return &m_cBeginPoint; };

	// Setter
	inline void SetAngle(cVector3 angle) { m_vAngle = angle; };
	inline void SetCenter(float x, float y) { m_vCenter.x = x; m_vCenter.y = y; };
	inline void SetCenter(cVector2 center) { m_vCenter = center; };
	inline void SetRect(RECT rect) { m_Rect = rect; };
	inline void SetBlendMode(int mode) { m_nBlendMode = mode; };
	inline void SetScale(cVector2 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = scale; };
	inline void SetBeginPriority(int pri) { m_cBeginPoint.SetPriority(pri); };

private:
	cVector3  m_vAngle;			// 回転
	cVector2  m_vCenter;		// 中心位置
	RECT	  m_Rect;			// 描画矩形の始点と終点
	int		  m_nBlendMode;		// 描画ブレンドモード
	cVector2  m_vScale;			// 拡大縮小

	IDrawBase m_cBeginPoint;	// サーフェイスの描画開始ポイントの設定(Priorityで指定)
};