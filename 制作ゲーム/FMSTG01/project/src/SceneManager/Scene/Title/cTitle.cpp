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
#include "..\..\..\Input\cControllerManager.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include "..\..\..\BaseObject\GameObject\Effect\cEffectManager.h"
#include "..\..\..\BaseObject\GameObject\OtherSprite\TitleTile\cTitleTileManager.h"
#include "..\..\..\SoundCtrl\cSoundCtrl.h"

#include <DxLib.h>


//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTitle::cTitle(IBaseObject * parent)
	: IBaseObject(parent, "Title"),
	m_nCounter( 0 ),
	m_eTitleState( STATE_TILE_POP )
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
	// �^�C���}�l�[�W���[�̍쐬
	cTitleTileManager* tileMan = CreateObject<cTitleTileManager>(this);
	tileMan->StartPop();

	// �^�C�g�������̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"TitleFont","data\\graphic\\TitleFont.png");
	obj->SetVisible(false);
	obj->SetPriority(101);
	obj->SetPos(cGame::GetInstance().GetWindowWidth() / 2.0f ,cGame::GetInstance().GetWindowHeight() / 2.0f - 75.0f);


	// PUSHKEY�̐���
	obj = CreateDrawObject<cSpriteObject>(this,"PushKey","data\\graphic\\PushKey.png");
	obj->SetVisible(false);
	obj->SetPriority(101);
	obj->SetPos(cGame::GetInstance().GetWindowWidth() / 2.0f ,(float)cGame::GetInstance().GetWindowHeight() - obj->GetSpriteSize().y );

	// �^�C�g��BGM�̍Đ�
	cSoundCtrl::GetInstance().BGMPlay(SOUND_TITLE);

	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();

	m_nCounter++;
	
	switch( m_eTitleState )
	{
	case STATE_TILE_POP:
		TilePop();
		break;
	case STATE_APPEAR_TITLE:
		AppearTitle();
		break;
	case STATE_PUSHKEY:
		PushKey();
		break;
	case STATE_CRUMBLE:
		Crumble();
		break;
	}

	// �^�C�����X�e�[�g��
	if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_1))
	{
		m_eTitleState = STATE_CRUMBLE;

		cSpriteObject* font = ((cSpriteObject*)FindChild("TitleFont"));
		if( nullptr != font ) font->DeleteObject();
		cSpriteObject* push = ((cSpriteObject*)FindChild("PushKey"));
		if(nullptr != push) push->DeleteObject();
		((cTitleTileManager*)FindChild("TitleTileManager"))->StartCrumble();
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
//==========================================================================================
//  �^�C���o����
//==========================================================================================
void cTitle::TilePop(void)
{
	cTitleTileManager* tileMan = (cTitleTileManager*)FindChild("TitleTileManager");

	// �^�C���̏o�����I����Ă���΃^�C�g�������o���V�[���ֈڍs
	if (tileMan != nullptr && tileMan->IsPopComp())
	{
		cSpriteObject* obj = (cSpriteObject*)FindChild("TitleFont");
		obj->SetVisible(true);
		m_eTitleState = STATE_APPEAR_TITLE;
	}
}
//==========================================================================================
//  �^�C�g���o����
//==========================================================================================
void cTitle::AppearTitle(void)
{
	m_eTitleState = STATE_PUSHKEY;
	m_nCounter = 0;
}
//==========================================================================================
//  �L�[�����\��
//==========================================================================================
void cTitle::PushKey(void)
{
	cSpriteObject* obj = (cSpriteObject*)FindChild("PushKey");
	if(m_nCounter % PUSHKEY_INTERVAL > PUSHKEY_INTERVAL / 2)
	{
		obj->SetVisible(true);
	}else
	{
		obj->SetVisible(false);
	}
}
//==========================================================================================
//  �^�C���������
//==========================================================================================
void cTitle::Crumble(void)
{
	// �S�Ẵ^�C��������邩�L�[���������ꍇ�̓Q�[�����C��
	if (m_listChildObject.empty() || cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_1))
	{
		// �S�Ẵ^�C�������ꂽ��Q�[�����C��
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeScene(SCENE_ID_GAMEMAIN, cSceneManager::CHANGE_UNITRANS);
	}
}
