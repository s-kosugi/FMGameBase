/*==============================================================================*/
/*																				*/
/*	@file title	:	cSceneManager.cpp											*/
/*  @brief		:	�V�[���Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/
#include "cSceneManager.h"
#include "Scene\Title\cTitle.h"
#include "Scene\GameMain\cGameMain.h"
#include "..\cGame.h"

#include "../BaseObject/cSpriteObject.h"

//==========================================================================================
// ������
//==========================================================================================
void cSceneManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "SceneManager";

	// ���݃V�[�����_�~�[�ɐݒ�
	m_eCurrentScene = SCENE_ID_NONE;

	// �^�C�g���V�[�������ɐ�������
	m_eNextScene = SCENE_ID_TITLE;

	// �V�[���؂�ւ��̏�Ԑݒ�
	m_eState = STATE_TRANSITION;

	// �V�[���̐؂�ւ����o�ݒ�
	m_eChangeType = CHANGE_NOFADE;

	m_pTransObj = nullptr;

	//�t�F�[�h�A�E�g�p
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "black", "data\\graphic\\black.png");
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);
	obj->SetVisible(false);


	IBaseObject::Initialize();
}
//==========================================================================================
// �X�V
//==========================================================================================
void cSceneManager::Update(void)
{
	switch (m_eState)
	{
		case STATE_FADEIN:      FadeIn();			break;
		case STATE_UPDATE:		UpdateScene();		break;
		case STATE_FADEOUT:     FadeOut();			break;
		case STATE_TRANSITION:	TransitionScene();	break;
	}
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cSceneManager::Finalize(void)
{
	IBaseObject::Finalize();

	return nullptr;
}
//==========================================================================================
// ���Z�b�g
//==========================================================================================
void cSceneManager::Reset(CHANGE_TYPE changeType)
{
	// �w�肵���t�F�[�h�ŃV�[�������Z�b�g����(�f�t�H���g����)
	m_eChangeType = changeType;
	PrepareFadeOut();
}
//==========================================================================================
// �V�[������
// id : ��������V�[��ID
//==========================================================================================
void cSceneManager::CreateScene(SCENE_ID id)
{
	switch (id)
	{
		case SCENE_ID_TITLE:        CreateObject<cTitle>(this);         break;
		case SCENE_ID_GAMEMAIN:     CreateObject<cGameMain>(this);      break;
	}
}
//==========================================================================================
// �t�F�[�h�A�E�g�O����
//==========================================================================================
void cSceneManager::PrepareFadeOut(void)
{
	m_eState = STATE_FADEOUT;

	cSpriteObject* obj = (cSpriteObject*)FindChild("black");
	obj->SetAlpha(0);
	switch (m_eChangeType)
	{
	case CHANGE_NOFADE:
		obj->SetVisible(false);
		break;
	case CHANGE_FADE:
		obj->SetVisible(true);
		break;
	case CHANGE_UNITRANS:
		if (m_pTransObj == nullptr)
		{
			m_pTransObj = new cTransition(cTransition::RULE_CHECKSPHERE, obj);
			m_pTransObj->Initialize();
			m_pTransObj->SetTransDirection(cTransition::TRANS_OUT);
		}
		break;
	}
}
//==========================================================================================
// �t�F�[�h�C��
//==========================================================================================
void cSceneManager::FadeIn(void)
{
	cSpriteObject* obj = (cSpriteObject*)FindChild("black");
	int alpha = obj->GetAlpha();

	switch (m_eChangeType)
	{
		// �t�F�[�h�C�����o�Ȃ�
		case CHANGE_NOFADE:
			m_eState = STATE_UPDATE;
			break;
		// �t�F�[�h�C��
		case CHANGE_FADE:
			alpha -= FADE_SPEED;
			if (alpha < 0)
			{
				alpha = 0;

				m_eState = STATE_UPDATE;
			}
			obj->SetAlpha(alpha);
			break;
		case CHANGE_UNITRANS:
			if (m_pTransObj != nullptr)
			{
				m_pTransObj->Update();
				if (m_pTransObj->IsEnd())
				{
					m_eState = STATE_UPDATE;
					SAFE_DELETE(m_pTransObj);
				}
			} else
			{
				m_eState = STATE_UPDATE;
			}
			break;
	}
}

//==========================================================================================
// �V�[���X�V
//==========================================================================================
void cSceneManager::UpdateScene(void)
{
	IBaseObject::Update();

	// �V�[���ύX�̌��m
	if (m_eCurrentScene != m_eNextScene)
	{
		// �t�F�[�h�A�E�g����
		PrepareFadeOut();
	}
}
//==========================================================================================
// �t�F�[�h�A�E�g
//==========================================================================================
void cSceneManager::FadeOut(void)
{
	cSpriteObject * obj = (cSpriteObject*)FindChild("black");
	int alpha = obj->GetAlpha();

	switch (m_eChangeType)
	{
		// �t�F�[�h�A�E�g���o�Ȃ�
		case CHANGE_NOFADE:
			m_eState = STATE_TRANSITION;
			break;
		// �t�F�[�h�A�E�g
		case CHANGE_FADE:
			alpha += FADE_SPEED;
			if (alpha > 255)
			{
				alpha = 255;

				m_eState = STATE_TRANSITION;
			}
			obj->SetAlpha(alpha);
			break;
		case CHANGE_UNITRANS:
			if (m_pTransObj != nullptr)
			{
				m_pTransObj->Update();
				if (m_pTransObj->IsEnd())	m_eState = STATE_TRANSITION;
			} else
			{
				m_eState = STATE_TRANSITION;
			}
			break;
	}
}
//==========================================================================================
// �V�[���J��
//==========================================================================================
void cSceneManager::TransitionScene(void)
{
	IBaseObject::Finalize();
	SAFE_DELETE(m_pTransObj);

	CreateScene(m_eNextScene);

	// �t�F�[�h�p�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "black", "data\\graphic\\black.png");
	obj->SetAlpha(255);
	obj->SetPriority(60000);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	switch( m_eChangeType)
	{
	case CHANGE_NOFADE: obj->SetVisible(false); break;
	case CHANGE_FADE:	obj->SetVisible(true); break;
	case CHANGE_UNITRANS:
		m_pTransObj = new cTransition(cTransition::RULE_CHECKSPHERE, obj);
		m_pTransObj->Initialize();
		m_pTransObj->SetTransDirection(cTransition::TRANS_IN);
		obj->SetVisible(false);
		break;
	}

	IBaseObject::Initialize();

	IBaseObject::Update();

	m_eCurrentScene = m_eNextScene;

	m_eState = STATE_FADEIN;
}
