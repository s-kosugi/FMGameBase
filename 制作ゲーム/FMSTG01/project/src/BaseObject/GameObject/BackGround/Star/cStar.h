#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStar.h														*/
/*  @brief		:	星オブジェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/10													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// 星オブジェクトクラス
class cStar : public cSpriteObject
{
public:
	cStar(IBaseObject* parent);
	~cStar(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	void FlashColor( void );

private:
	enum StarType {
		TYPE_SMALL,
		TYPE_MIDIUM,
		TYPE_LARGE,

		TYPE_MAX
	};

	// 星の種別
	StarType m_eStarType;

	// 移動速度
	cVector2 m_vPosUp;

	// 元の色を記憶しておく変数
	unsigned int m_nSaveColor;

	// 色の増分値
	float		m_fColorIncrement;

	// 点滅をさせる為のカウンター
	float m_fFlashCounter;

	// 定数
	const float SMALL_STAR_SPEED = 1.0f;
	const float MIDIUM_STAR_SPEED = 1.5f;
	const float LARGE_STAR_SPEED = 2.0f;
	const int	PRIORITY = -50;
};
//================================================================================================