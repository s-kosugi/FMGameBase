#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cText.h														*/
/*  @brief		:	テキストクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/08/23													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\IDrawBase.h"

//================================================================================================
// テキスト描画クラス
class cText : public IDrawBase
{
public:
	cText(const std::string& text);
	cText(const std::string& text, const std::string& fontname, int fontsize, int Thick, int FontType, int EdgeSize, int Italic);
	~cText();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// Getter
	inline std::string GetText(void) { return m_sText; };
	inline unsigned int GetEdgeColor(void) { return m_nEdgeColor; };
	inline int	GetVerticalFlag(void) { return m_nVerticalFlag; };		// 縦方向に描画するかの設定 FALSE : 横方向 TRUE : 縦方向

	int GetWidth(void);		// 文字列の幅を取得する。指定のフォントデータで描画する文字列の幅(ドット単位)を得る

	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetText(std::string text) { m_sText = text; };					// 文字列の設定 デフォルトフォントでは無効
	inline void SetEdgeColor(unsigned int color) { m_nEdgeColor = color; };		// 縁の色の設定 デフォルトフォントでは無効
	inline void SetVerticalFlag(int flag) { m_nVerticalFlag = flag; };			// 縦方向かどうかの設定 FALSE : 横方向 TRUE : 縦方向 デフォルトフォントでは無効

protected:

	//---------------------------------------------------------------------------------------------
	// テキスト表示情報
	std::string		m_sText;		// テキスト内容

	unsigned int	m_nEdgeColor;	// 文字の縁の色
	int				m_nVerticalFlag;// 縦方向かどうか FALSE : 横方向 TRUE : 縦方向
};
//================================================================================================