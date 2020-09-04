#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cSurfaceObject.h											*/
/*  @brief		:	サーフェイスオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/03/03													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"
#include "DrawCtrl/Surface/cSurface.h"

//================================================================================================
// 描画オブジェクト
// １クラスにつき１つのサーフェイスを持ちたい場合に使用する。
class cSurfaceObject : public IBaseObject, public cSurface
{
public:

	//---------------------------------------------
	// コンストラクタ
	// parent : 親オブジェクト
	// name : オブジェクト名
	// width : サーフェイスの横幅
	// height : サーフェイスの高さ
	// beginPriority : サーフェイスに含める開始の描画優先度
	// endPriority : サーフェイスに含める終了の描画優先度
	// alpha : 透明度を有効にするかどうか (TRUE : 有効 )
	cSurfaceObject(IBaseObject* parent, const std::string& objectname, int width, int height, int beginPriority, int endPriority, int alpha);
	~cSurfaceObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

};
//================================================================================================

//================================================================================================
// オブジェクト生成関数
//================================================================================================
// サーフェイスオブジェクト生成
// 親オブジェクトとオブジェクトとサーフェイスに必要な項目を指定する。
// parent : 親オブジェクト
// name : オブジェクト名
// width : サーフェイスの横幅
// height : サーフェイスの高さ
// beginPriority : サーフェイスに含める開始の描画優先度
// endPriority : サーフェイスに含める終了の描画優先度
// alpha : 透明度を有効にするかどうか (TRUE : 有効 )
// return : 生成したオブジェクト
template <class T> T* CreateSurfaceObject(IBaseObject* parent, const std::string& name, int width, int height, int beginPriority, int endPriority, int alpha)
{
	// ゲームオブジェクト生成
	T* t = NEW T(parent, name, width, height, beginPriority, endPriority, alpha);

	// 親がいればリストに追加
	if (parent) parent->AddChild(t);

	// オブジェクトの返却
	return t;
}

template <class T> T* CreateSurfaceObject(IBaseObject* parent, const std::string& name, int width, int height, int beginPriority, int endPriority)
{
	// ゲームオブジェクト生成
	T* t = NEW T(parent, name, width, height, beginPriority, endPriority, TRUE);

	// 親がいればリストに追加
	if (parent) parent->AddChild(t);

	// オブジェクトの返却
	return t;
}

