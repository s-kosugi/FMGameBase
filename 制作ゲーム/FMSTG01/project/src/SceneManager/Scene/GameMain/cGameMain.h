#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.h													*/
/*  @brief		:	ゲームメインシーン											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\BaseObject\IBaseObject.h"

//================================================================================================
// ゲームメインシーン
class cGameMain : public IBaseObject
{
public:
	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// 当たり判定処理
	void CheckHitProc( void );

	// 自機と敵の当たり判定(サブルーチン)
	void CheckHitPlayer(void);

	// 敵と自機の弾の当たり判定(サブルーチン)
	void CheckHitEnemy( void );

};
//================================================================================================