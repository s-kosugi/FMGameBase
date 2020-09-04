/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.cpp												*/
/*  @brief		:	�Q�[�����C���V�[��											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cGameMain.h"
#include "..\..\cSceneManager.h"
#include "..\..\..\Input\Keyboard\cKeyboard.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include "..\..\..\BaseObject\GameObject\Effect\cEffectManager.h"
#include <DxLib.h>

#include "..\..\..\BaseObject\GameObject\Player\cPlayer.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
{
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cGameMain::~cGameMain(void)
{
}
//==========================================================================================
//  ������
//==========================================================================================
void cGameMain::Initialize(void)
{
	// �w�i�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "TitleBack", "data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth()/2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	// �G�t�F�N�g�}�l�[�W���[�̒ǉ�
	AddChild(&cEffectManager::GetInstance());

	// �v���C���[�L�����N�^�[�̐���
	CreateObject<cPlayer>(this);

	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cGameMain::Update(void)
{

	IBaseObject::Update();

	// �G�t�F�N�V�A�e�X�g�V�[����
	cKeyboard& key = cKeyboard::GetInstance();
	if (key.CheckTrigger(KEY_INPUT_RETURN))
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeSceneUniTrans(SCENE_ID::EFFEKSEER_TEST,"data\\graphic\\rule_00.png");
	}
}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
