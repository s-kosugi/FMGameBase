#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTextObject.h												*/
/*  @brief		:	テキストオブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/08/23													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseObject.h"
#include "DrawCtrl\Text\cText.h"

//================================================================================================
// テキストオブジェクト
// １クラスにつき１つのテキストを持ちたい場合に使用する。
class cTextObject : public IBaseObject, public cText
{
public:
	cTextObject(IBaseObject* parent, const std::string& objectname, const std::string& text);
	cTextObject(IBaseObject* parent, const std::string& objectname, const std::string& text, const std::string& fontname, int fontsize, int Thick, int FontType, int EdgeSize, int Italic);
	~cTextObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

private:

};
//================================================================================================

//================================================================================================
// オブジェクト生成関数
//================================================================================================
// デフォルトフォントでオブジェクト生成
// 親オブジェクトとオブジェクト名と表示テキストを指定する。
// return : 生成したオブジェクト
template <class T> T* CreateTextObject(IBaseObject* parent, const std::string& name, const std::string& text)
{
	// ゲームオブジェクト生成
	T* t = NEW T(parent, name, text);

	// 親がいればリストに追加
	if (parent) parent->AddChild(t);

	// オブジェクトの返却
	return t;
}

// 指定フォントオブジェクト生成
// 親オブジェクトとオブジェクト名と表示テキストとCreateFontToHandleで必要な引数を指定する。
// fontnameはフォント名を指定
// fontsize Thick FontType EdgeSizeは-1でデフォルト
// Italicは0がデフォルト
// return : 生成したオブジェクト
template <class T> T* CreateTextObject(IBaseObject* parent, const std::string& name, const std::string& text, const std::string& fontname, int fontsize, int Thick, int FontType, int EdgeSize, int Italic)
{
	// ゲームオブジェクト生成
	T* t = NEW T(parent, name, text, fontname, fontsize, Thick, FontType, EdgeSize, Italic);

	// 親がいればリストに追加
	if (parent) parent->AddChild(t);

	// オブジェクトの返却
	return t;
}