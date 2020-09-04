#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectObject.h												*/
/*  @brief		:	エフェクトオブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "..\..\..\DrawCtrl\Effect\cEffect.h"

//================================================================================================
// エフェクトオブジェクト
// １クラスにつき１つのエフェクトを持ちたい場合に使用する。
class cEffectObject : public IBaseObject, public cEffect
{
public:
	cEffectObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cEffectObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

};
//================================================================================================

//================================================================================================
// オブジェクト生成関数
//================================================================================================
// オブジェクト生成
// 親オブジェクトとオブジェクト名と画像ファイル名を指定する。
// return : 生成したオブジェクト
template <class T> T* CreateEffectObject(IBaseObject* parent, const std::string& name, const std::string& filename)
{
	// ゲームオブジェクト生成
	T* t = NEW T(parent, name, filename);

	// 親がいればリストに追加
	if (parent) parent->AddChild(t);

	// オブジェクトの返却
	return t;
}
