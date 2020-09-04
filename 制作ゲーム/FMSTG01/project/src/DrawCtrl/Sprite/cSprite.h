#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSprite.h													*/
/*  @brief		:	スプライトクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\IDrawBase.h"

//================================================================================================
// 描画スプライトクラス
class cSprite : public IDrawBase
{
public:
	cSprite(const std::string& filename);
	~cSprite();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// アニメーション情報
	struct Animation {
		POINT		StartPos;			// パーツの開始点
		POINT		Size;				// 1枚毎の大きさ
		short		AnimMax;			// アニメーション枚数
		short		AnimTime;			// 1アニメーション毎の時間

		short		AnimFrame;			// 現在のアニメーションフレーム(何枚目か)
		short		TimerCount;			// 現在のアニメーションタイマー
	};
	
	//---------------------------------------------------------------------------------------------
	// スプライトタイプ
	enum SpriteType {
		SPTYPE_NORMAL = 0,		// 通常の描画
		SPTYPE_CIRCLEGAUGE,		// 円形ゲージ
	};
	//---------------------------------------------------------------------------------------------
	// Getter
	POINT GetSpriteSize(void);
	inline RECT GetSrcRect(void) { return m_SrcRect; };
	inline cVector2 GetCenter(void) { return m_vCenter; };
	inline int GetBlendMode(void) { return m_BlendMode; };
	inline cVector2 GetScale(void) { return m_vScale; };
	inline float GetAngle(void) { return m_fAngle; };

	inline float GetStartAngle(void) { return m_fStartAngle; };
	inline float GetEndAngle(void) { return m_fEndAngle; };
	inline SpriteType GetSpriteType(void) { return m_eSpType; };


	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetSrcRect(RECT rect) { m_SrcRect = rect;};
	void SetSrcRect(int Startx, int Starty, int Sizex, int Sizey);
	inline void SetCenter(cVector2 vec) { m_vCenter = vec; };
	inline void SetCenter(float x, float y) {m_vCenter.x = x; m_vCenter.y = y;};
	inline void SetBlendMode(int mode) {m_BlendMode = mode;};
	inline void SetScale(cVector2 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = scale; };
	inline void SetAngle(float angle) { m_fAngle = angle; };

	inline void SetStartAngle(float angle) { m_fStartAngle = angle; };
	inline void SetEndAngle(float angle) { m_fEndAngle = angle; };
	inline void SetAnimation(Animation anim) { m_Animation = anim; };
	void SetAnimation( int Startx,int Starty,int width, int height,short AnimMax,short AnimTime );

protected:

	//---------------------------------------------------------------------------------------------
	// スプライト表示情報
	RECT		m_SrcRect;				// 描画矩形の始点と終点
	cVector2	m_vCenter;				// 回転と拡大の中心位置
	int			m_BlendMode;			// 描画ブレンドモード
	cVector2	m_vScale;				// 拡大縮小
	float		m_fAngle;				// スプライトの回転角度

	float		m_fStartAngle;			// 円グラフの開始角度
	float		m_fEndAngle;			// 円グラフの終了角度
	
	Animation	m_Animation;			// アニメーション情報構造体
	SpriteType	m_eSpType;				// スプライトタイプ
};
//================================================================================================