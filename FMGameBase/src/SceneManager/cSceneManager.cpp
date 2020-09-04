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
#include "Scene\EffekseerTest\cEffekseerTest.h"
#include "Scene/Pause/cPause.h"
#include "..\cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

#include "../BaseObject/cSpriteObject.h"

//==========================================================================================
// �萔
//==========================================================================================
const float    cSceneManager::DEFAULT_FADE_TIME = 1.0f;

//==========================================================================================
// ������
//==========================================================================================
void cSceneManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "SceneManager";

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
	case STATE::FADEIN:      FadeIn();			break;
	case STATE::UPDATE:		UpdateScene();		break;
	case STATE::FADEOUT:     FadeOut();			break;
	case STATE::TRANSITION:	TransitionScene();	break;
	}
}

//==========================================================================================
// �V�[���ύX
//==========================================================================================
void cSceneManager::ChangeScene(SCENE_ID id, CHANGE_TYPE type)
{
	m_eNextScene = id;
	m_eChangeOutType = type;
	m_eChangeInType = type;
}

//==========================================================================================
// �V�[���ύX(���j�o�[�T���g�����W�V����)
//==========================================================================================
void cSceneManager::ChangeSceneUniTrans(SCENE_ID id, std::string ruleFilename)
{
	m_eNextScene = id;
	m_eChangeOutType = CHANGE_TYPE::UNITRANS;
	m_eChangeInType = CHANGE_TYPE::UNITRANS;
	m_sTransOutFileName = ruleFilename;
	m_sTransInFileName = ruleFilename;
}

//==========================================================================================
// �X�^�b�N���Ă���V�[���̍Ō�����擾
//==========================================================================================
SCENE_ID cSceneManager::GetStackSceneID(void)
{
	if (m_nStackCount < 1) return m_eCurrentScene;

	if (m_listChildObject.empty()) return m_eCurrentScene;
	auto end = m_listChildObject.end();
	end--;

	IBaseScene* scene = (IBaseScene*)(*end);

	return scene->GetSceneID();
}
//==========================================================================================
// �V�[���̃X�^�b�N
//==========================================================================================
void cSceneManager::PushScene(SCENE_ID id)
{
	// ���t���[�����ɂ��łɃv�b�V������Ă���
	if (m_bPush || m_ePushSceneID != SCENE_ID::NONE) return;

	// ���O�̃V�[���̍X�V���~�߂�
	if (!m_listChildObject.empty())
	{
		auto end = m_listChildObject.end();
		end--;

		IBaseScene* scene = (IBaseScene*)(*end);
		scene->SetObjetState(OBJECT_STATE::WAIT);
	}

	// �v�b�V���t���O��ON
	m_bPush = true;

	// �X�^�b�N����V�[��ID��ۑ�
	m_ePushSceneID = id;

	m_nStackCount++;
}
//==========================================================================================
// �X�^�b�N�����V�[���̍폜
//==========================================================================================
void cSceneManager::PopScene(void)
{
	// �q�̃V�[����1�̏ꍇ�̓|�b�v�ł��Ȃ�
	if (m_nStackCount <= 1)
		return;

	// �����̃V�[���̃C�e���[�^�擾
	auto it = m_listChildObject.rbegin();

	IBaseScene* scene = (IBaseScene*)(*it);

	// �����̃V�[�����폜�Ώۂɐݒ�
	scene->DeleteObject();

	// �P�O�̃V�[�����擾
	scene = (IBaseScene*)(*(++it));

	// �P�O�̃V�[�����A�N�e�B�u��ԂɕύX
	scene->SetObjetState(OBJECT_STATE::ACTIVE);

	m_nStackCount--;
}
//==========================================================================================
// ���Z�b�g
//==========================================================================================
void cSceneManager::Reset(CHANGE_TYPE changeType)
{
	// �w�肵���t�F�[�h�ŃV�[�������Z�b�g����(�f�t�H���g����)
	m_eChangeOutType = changeType;
	PrepareFadeOut();
}
//==========================================================================================
// �V�[������
// id : ��������V�[��ID
// return : ���������V�[���̃|�C���^
//==========================================================================================
IBaseScene* cSceneManager::CreateScene(SCENE_ID id)
{
	IBaseScene* pscene = nullptr;
	switch (id)
	{
	case SCENE_ID::TITLE:			pscene = CreateObject<cTitle>(this);			break;
	case SCENE_ID::GAMEMAIN:		pscene = CreateObject<cGameMain>(this);			break;
	case SCENE_ID::EFFEKSEER_TEST:	pscene = CreateObject<cEffekseerTest>(this);	break;
	case SCENE_ID::PAUSE:			pscene = CreateObject<cPause>(this);			break;
	}
	if (pscene != nullptr) pscene->SetSceneID(id);
	return pscene;
}
//==========================================================================================
// �t�F�[�h�A�E�g�O����
//==========================================================================================
void cSceneManager::PrepareFadeOut(void)
{
	m_eState = STATE::FADEOUT;

	cSpriteObject* obj = (cSpriteObject*)FindChild("black");
	obj->SetAlpha(0);
	switch (m_eChangeOutType)
	{
	case CHANGE_TYPE::NOFADE:
		obj->SetVisible(false);
		break;
	case CHANGE_TYPE::FADE:
		obj->SetVisible(true);
		break;
	case CHANGE_TYPE::UNITRANS:
		if (m_pTransObj == nullptr)
		{
			m_pTransObj = new cTransition(m_sTransOutFileName, obj, cTransition::TransDirection::TRANS_OUT, (float)m_nFadeOutTime);
			m_pTransObj->Initialize();
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
	cTimer* timer = (cTimer*)FindChild("FadeInTimer");

	switch (m_eChangeInType)
	{
		// �t�F�[�h�C�����o�Ȃ�
	case CHANGE_TYPE::NOFADE:
		m_eState = STATE::UPDATE;
		break;
		// �t�F�[�h�C��
	case CHANGE_TYPE::FADE:
		if (timer == nullptr)
		{
			timer = CreateObject<cTimer>(this, "FadeInTimer");
			timer->Setup(m_nFadeOutTime);
		}
		timer->Update();
		alpha = (int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 0.0f, 255.0f);
		if (alpha <= 0)
		{
			alpha = 0;
			timer->DeleteObject();
			m_eState = STATE::UPDATE;
		}
		obj->SetAlpha(alpha);
		break;
	case CHANGE_TYPE::UNITRANS:
		if (m_pTransObj != nullptr)
		{
			m_pTransObj->Update();
			if (m_pTransObj->IsEnd())
			{
				m_eState = STATE::UPDATE;
				SAFE_DELETE(m_pTransObj);
			}
		}
		else
		{
			m_eState = STATE::UPDATE;
		}
		break;
	}
}

//==========================================================================================
// �V�[���X�V
//==========================================================================================
void cSceneManager::UpdateScene(void)
{
	// �v�b�V������������
	if (m_bPush)
	{
		// �V�����V�[���𐶐����ăX�^�b�N����
		IBaseScene* pscene = CreateScene(m_ePushSceneID);
		if (pscene)
		{
			pscene->Initialize();
		}
		m_ePushSceneID = SCENE_ID::NONE;
		m_bPush = false;
	}
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
	cSpriteObject* obj = (cSpriteObject*)FindChild("black");
	int alpha = obj->GetAlpha();
	cTimer* timer = (cTimer*)FindChild("FadeOutTimer");

	switch (m_eChangeOutType)
	{
		// �t�F�[�h�A�E�g���o�Ȃ�
	case CHANGE_TYPE::NOFADE:
		m_eState = STATE::TRANSITION;
		break;
		// �t�F�[�h�A�E�g
	case CHANGE_TYPE::FADE:
		if (timer == nullptr)
		{
			timer = CreateObject<cTimer>(this, "FadeOutTimer");
			timer->Setup(m_nFadeOutTime);
		}
		timer->Update();
		alpha = (int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 255.0f, 0.0f);
		if (alpha > 255)
		{
			alpha = 255;
			timer->DeleteObject();
			m_eState = STATE::TRANSITION;
		}

		obj->SetAlpha(alpha);
		break;
	case CHANGE_TYPE::UNITRANS:
		if (m_pTransObj != nullptr)
		{
			m_pTransObj->Update();
			if (m_pTransObj->IsEnd())	m_eState = STATE::TRANSITION;
		}
		else
		{
			m_eState = STATE::TRANSITION;
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

	// �t�F�[�h�p�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "black", "data\\graphic\\black.png");
	obj->SetAlpha(255);
	obj->SetPriority(60000);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	CreateScene(m_eNextScene);

	switch (m_eChangeOutType)
	{
	case CHANGE_TYPE::NOFADE: obj->SetVisible(false); break;
	case CHANGE_TYPE::FADE:	obj->SetVisible(true); break;
	case CHANGE_TYPE::UNITRANS:
		m_pTransObj = new cTransition(m_sTransOutFileName, obj, cTransition::TransDirection::TRANS_IN, (float)m_nFadeInTime);
		m_pTransObj->Initialize();
		obj->SetVisible(false);
		break;
	}

	m_eCurrentScene = m_eNextScene;

	m_eState = STATE::FADEIN;

	m_nStackCount = 1;

	IBaseObject::Initialize();

	IBaseObject::Update();

}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cSceneManager::cSceneManager(void) :
	m_eCurrentScene(SCENE_ID::NONE),
	m_eNextScene(SCENE_ID::TITLE),
	m_eState(STATE::TRANSITION),
	m_eChangeInType(CHANGE_TYPE::NOFADE),
	m_eChangeOutType(CHANGE_TYPE::NOFADE),
	m_nFadeInTime(DEFAULT_FADE_TIME),
	m_nFadeOutTime(DEFAULT_FADE_TIME),
	m_ePushSceneID(SCENE_ID::NONE),
	m_bPush(false),
	m_nStackCount(0),
	m_pTransObj(nullptr),
	m_sTransOutFileName(""),
	m_sTransInFileName("")
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cSceneManager::cSceneManager(IBaseObject* parent) :
	cSceneManager()
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cSceneManager::cSceneManager(IBaseObject* parent, const std::string& name) :
	cSceneManager(parent)
{
}

//==========================================================================================
// �R�s�[�R���X�g���N�^
//==========================================================================================
cSceneManager::cSceneManager(const cSceneManager& t) :
	cSceneManager()
{
}
