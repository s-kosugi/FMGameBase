/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.cpp													*/
/*  @brief		:	�^�C�g���V�[��												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cTitle.h"
#include "..\..\cSceneManager.h"
#include "..\..\..\Input\Keyboard\cKeyboard.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include <DxLib.h>

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTitle::cTitle(IBaseObject * parent)
	: IBaseScene(parent, "Title")
{
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cTitle::~cTitle(void)
{
}
//==========================================================================================
//  ������
//==========================================================================================
void cTitle::Initialize(void)
{
	// �w�i�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"TitleBack","data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);


	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();

	// �Q�[�����C���V�[����
	cKeyboard& key = cKeyboard::GetInstance();
	//if (key.CheckTrigger(KEY_INPUT_RETURN))
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		//sm->ChangeScene(SCENE_ID_GAMEMAIN, cSceneManager::CHANGE_TYPE::CHANGE_UNITRANS);
		sm->ChangeSceneUniTrans(SCENE_ID::GAMEMAIN,"data\\graphic\\rule_01.png");
	}
}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cTitle::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
