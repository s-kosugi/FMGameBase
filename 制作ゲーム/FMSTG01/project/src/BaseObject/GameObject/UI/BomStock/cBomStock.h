#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cBomStock.h													*/
/*  @brief		:	ボムストックオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// ボムストッククラス
class cBomStock : public cUIObject
{
public:
	cBomStock(IBaseObject* parent);
	~cBomStock(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	const int PRIORITY = 2001;

	const int CREATE_BOMVISIBLE_MAX = 6;		// ボム残弾の最大表示数

	const int STOCK_OFFSET_X = 30;				// ボム残弾表示をどれだけずらすか
	const int STOCK_OFFSET_Y = 23;				// ボム残弾表示をどれだけずらすか
	const int STOCK_INTERVAL_X = 28;			// ボム残弾を表示する間隔
};
//================================================================================================