#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cNumber.h													*/
/*  @brief		:	数字オブジェクト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "BaseObject/cSpriteObject.h"

//================================================================================================
// 数字クラス
class cNumber : public cSpriteObject
{
public:
	cNumber(IBaseObject* parent, std::string objectname, std::string filename);
	~cNumber(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// 数字の生成
	void CreateNumber(short maxdigit, int value);

	// 数値の設定
	inline void SetValue(int value) { m_nValue = value; };

	// 描画優先度の設定
	void SetPriority( int priority );

protected:
	static const int	MAX_DIGIT;		// 最大桁数初期値

	int					m_nValue;		// 表示する数値
	int					m_nMaxDigit;	// 最大桁数
};
//================================================================================================