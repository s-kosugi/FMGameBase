/*==============================================================================*/
/*																				*/
/*	@file title	:	cNumber.cpp													*/
/*  @brief		:	数字オブジェクト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "cNumber.h"
#include <string>

//==========================================================================================
// 定数
//==========================================================================================
const int cNumber::MAX_DIGIT = 3;

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cNumber::cNumber(IBaseObject* parent, std::string objectname, std::string filename) :
	cSpriteObject(parent, objectname, filename),
	m_nMaxDigit(MAX_DIGIT),
	m_nValue(0)
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cNumber::~cNumber(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cNumber::
Initialize(void)
{
	// このクラス自身の表示はしない
	m_bVisible = false;

	cSpriteObject::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cNumber::Update(void)
{
	int i = 0;
	int value = m_nValue;
	for (auto it = m_listChildObject.begin(); it != m_listChildObject.end(); it++, i++)
	{
		cSpriteObject* pNumber = ((cSpriteObject*)*it);
		int num = value % 10;
		int width = pNumber->GetSpriteSize().x;

		// 数値の場所の設定
		pNumber->SetPos(m_vPos.x - width * i, m_vPos.y);
		pNumber->SetSrcRect(num * width, 0, width, pNumber->GetSpriteSize().y);

		pNumber->SetDrawColor(m_nColor);

		value /= 10;
	}
	cSpriteObject::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cNumber::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
//==========================================================================================
//  数字の生成
//  filename : 表示する画像
//  maxdigit : 最大桁数
//  value : 表示する数値
//==========================================================================================
void cNumber::CreateNumber(short maxdigit, int value)
{
	for (int i = 0; i < maxdigit; i++)
	{
		std::string num;
		num = std::to_string(i);
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, m_sObjectName + num, m_sFileName);
		obj->Initialize();
		// 画像を１数字分に設定する
		obj->SetSrcRect(0, 0, obj->GetSrcRect().right / 10, obj->GetSrcRect().bottom);
		obj->SetPriority(GetPriority());
	}
	m_nMaxDigit = maxdigit;
	m_nValue = value;
}

//==========================================================================================
//  描画優先度の設定
//==========================================================================================
void cNumber::SetPriority( int priority )
{
	for( auto it : m_listChildObject )
	{
		cSpriteObject* obj = (cSpriteObject*)it;
		obj->SetPriority(priority);
	}
	IDrawBase::SetPriority(priority);
}
