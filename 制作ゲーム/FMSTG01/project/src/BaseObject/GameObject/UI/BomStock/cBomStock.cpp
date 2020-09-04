/*==============================================================================*/
/*																				*/
/*	@file title	:	cBomStock.cpp												*/
/*  @brief		:	ボムストックオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/07													*/
/*																				*/
/*==============================================================================*/

#include "cBomStock.h"
#include "..\..\Player\cPlayer.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cBomStock::cBomStock(IBaseObject* parent) :
	cUIObject(parent,"BomStock","data\\graphic\\BomFrame.png")
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cBomStock::~cBomStock(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cBomStock::
Initialize(void)
{
	SetPriority(PRIORITY);

	// ボムの残弾部分の表示作成
	for (int i = 0; i < CREATE_BOMVISIBLE_MAX; i++)
	{
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "BomStockCircle", "data\\graphic\\BomStock.png");
		obj->SetVisible(false);
		obj->SetPriority(PRIORITY+1);

	}
	cUIObject::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cBomStock::Update(void)
{

	cPlayer* player = (cPlayer*)GetParent()->FindSibling("Player");
	if( player == nullptr) return; 

	int i = 0;
	for (auto it = m_listChildObject.begin(); it != m_listChildObject.end(); it++,i++)
	{
		cSpriteObject* obj = (cSpriteObject*)(*it);
		obj->SetPos(m_vPos.x - GetSpriteSize().x/2 + STOCK_OFFSET_X + i * STOCK_INTERVAL_X,m_vPos.y + STOCK_OFFSET_Y);

		if (i < player->GetBomNum())
		{
			obj->SetVisible(true);
		}
		else
		{
			obj->SetVisible(false);
		}
	}

	cUIObject::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cBomStock::Finalize(void)
{
	cUIObject::Finalize();
	return this;
}