#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cAnimSpObject.h"

//================================================================================================
// プレイヤークラス
class cPlayer : public cAnimSpObject
{
public:
	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void) override;
	void Update(void) override;
	IBaseObject* Finalize(void) override;

private:
	// プレイヤーの移動速度
	static const float MOVE_SPEED;

	// ゲーム開始位置
	static const float START_POS_X;
	static const float START_POS_Y;
	// 表示優先度
	static const int	PRIORITY;

	// 範囲外処理
	void ProcAreaOut(void);

};
//================================================================================================