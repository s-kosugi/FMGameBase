#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpriteObject.h												*/
/*  @brief		:	描画オブジェクト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/01													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"
#include "..\DrawCtrl\Sprite\cSprite.h"

//================================================================================================
// 描画オブジェクト
// １クラスにつき１つのスプライトを持ちたい場合に使用する。
class cSpriteObject : public IBaseObject, public cSprite
{
public:
	cSpriteObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cSpriteObject( void );


	virtual void Initialize( void );
	virtual void Initialize( const cVector2& pos );
	virtual void Update( void );
	virtual IBaseObject* Finalize( void );

private:

};
//================================================================================================

//================================================================================================
// オブジェクト生成関数
//================================================================================================
// オブジェクト生成
// 親オブジェクトとオブジェクト名と画像ファイル名を指定する。
// return : 生成したオブジェクト
template <class T> T* CreateDrawObject(IBaseObject* parent, const std::string& name, const std::string& filename)
{
	// ゲームオブジェクト生成
	T* t = NEW T(parent, name,filename);

	// 親がいればリストに追加
	if (parent) parent->AddChild(t);

	// オブジェクトの返却
	return t;
}
