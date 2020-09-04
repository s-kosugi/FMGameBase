#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cAnimSpObject.h												*/
/*  @brief		:	アニメーション描画オブジェクト								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/14													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"
#include "..\DrawCtrl\Sprite\cAnimSprite.h"

//================================================================================================
// アニメーション描画オブジェクト
// １クラスにつき１つのスプライトを持ちたい場合に使用する。
class cAnimSpObject : public IBaseObject, public cAnimSprite
{
public:
	cAnimSpObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cAnimSpObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

};
//================================================================================================
