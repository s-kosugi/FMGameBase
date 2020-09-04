/*==============================================================================*/
/*																				*/
/*	@file title	:	cBomStock.cpp												*/
/*  @brief		:	�{���X�g�b�N�I�u�W�F�N�g									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/07													*/
/*																				*/
/*==============================================================================*/

#include "cBomStock.h"
#include "..\..\Player\cPlayer.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cBomStock::cBomStock(IBaseObject* parent) :
	cUIObject(parent,"BomStock","data\\graphic\\BomFrame.png")
{

}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cBomStock::~cBomStock(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cBomStock::
Initialize(void)
{
	SetPriority(PRIORITY);

	// �{���̎c�e�����̕\���쐬
	for (int i = 0; i < CREATE_BOMVISIBLE_MAX; i++)
	{
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "BomStockCircle", "data\\graphic\\BomStock.png");
		obj->SetVisible(false);
		obj->SetPriority(PRIORITY+1);

	}
	cUIObject::Initialize();
}

//==========================================================================================
//  �X�V
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
//  ���
//==========================================================================================
IBaseObject* cBomStock::Finalize(void)
{
	cUIObject::Finalize();
	return this;
}