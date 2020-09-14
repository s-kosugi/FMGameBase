/*==============================================================================*/
/*																				*/
/*	@file title	:	cPause.cpp													*/
/*  @brief		:	�|�[�Y�V�[��												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/20													*/
/*																				*/
/*==============================================================================*/
#include "cPause.h"
#include "BaseObject/cSpriteObject.h"
#include "cGame.h"
#include "Input/cControllerManager.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cPause::cPause(IBaseObject * parent)
	: IBaseScene(parent, "Pause")
{
}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cPause::~cPause(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void cPause::Initialize(void)
{
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "PauseBack", "data\\graphic\\black.png");
	obj->SetPriority(2000);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);
	obj->SetAlpha( 128 );
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cPause::Update(void)
{
	if (cControllerManager::GetInstance().CheckTrigger(cControllerManager::KEY_DEFINE::KEY_PAUSE))
	{
		Pop();
	}
}

//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject * cPause::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}
