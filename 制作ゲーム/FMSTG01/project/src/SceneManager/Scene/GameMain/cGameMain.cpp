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
#include <DxLib.h>

#include "..\..\..\BaseObject\GameObject\BackGround\cBackGroundManager.h"
#include "..\..\..\BaseObject\GameObject\Player\cPlayer.h"
#include "..\..\..\BaseObject\GameObject\Enemy\cEnemyManager.h"
#include "..\..\..\BaseObject\GameObject\Bullet\cBulletManager.h"
#include "..\..\..\EventManager\cEventManager.h"
#include "..\..\..\BaseObject\GameObject\Effect\cEffectManager.h"
#include "..\..\..\BaseObject\GameObject\SpEffect\cSpEffectManager.h"
#include "..\..\..\BaseObject\GameObject\UI\cUIManager.h"

#include "..\..\..\ScoreManager\cScoreManager.h"
#include "..\..\..\Input\cControllerManager.h"
#include "..\..\..\Pause\cPause.h"

#include "..\..\..\SoundCtrl\cSoundCtrl.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseObject(parent, "GameMain")
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
	// �w�i�}�l�[�W���[�̒ǉ�
	AddChild(&cBackGroundManager::GetInstance());

	// �v���C���[�L�����N�^�[�̐���
	CreateObject<cPlayer>(this);

	// �G�}�l�[�W���[�̒ǉ�
	AddChild(&cEnemyManager::GetInstance());

	// �e�}�l�[�W���[�̒ǉ�
	AddChild(&cBulletManager::GetInstance());

	// �C�x���g�}�l�[�W���[�̒ǉ�
	AddChild(&cEventManager::GetInstance());

	// �X�e�[�W�P�̃C�x���g���J�n
	cEventManager::GetInstance().StartEvent(1);

	// �G�t�F�N�g�}�l�[�W���[�̒ǉ�
	AddChild(&cEffectManager::GetInstance());

	// �X�v���C�g�G�t�F�N�g�}�l�[�W���[�̒ǉ�
	AddChild(&cSpEffectManager::GetInstance());

	// UI�}�l�[�W���[�̒ǉ�
	AddChild(&cUIManager::GetInstance());

	// �X�R�A���Z�b�g
	cScoreManager::GetInstance().ResetScore();

	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cGameMain::Update(void)
{

	IBaseObject::Update();

	// �����蔻�菈��
	CheckHitProc();

	// �|�[�Y�J�n����
	if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_PAUSE))
		cPause::GetInstance().StartPause();

#ifdef DEBUG
	// �^�C�g���V�[����
	cKeyboard key = cKeyboard::GetInstance();
	if (key.CheckTriger(KEY_INPUT_RETURN))
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeScene(SCENE_ID_TITLE);
	}
#endif
}

//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{
	// ���t�F�[�h�A�E�g�֐���������ق������������B
	cSoundCtrl::GetInstance().BGMStop();

	IBaseObject::Finalize();
	return this;
}
//==========================================================================================
//  �����蔻�菈��
//==========================================================================================
void cGameMain::CheckHitProc(void)
{
	// ���@�ƓG�̓����蔻�菈��
	CheckHitPlayer();

	// �G�̓����蔻�菈��
	CheckHitEnemy();
	
}

//==========================================================================================
//  ���@�ƓG�̓����蔻��
//  ���@VS�G  ���@VS�G�̒e
//==========================================================================================
void cGameMain::CheckHitPlayer(void)
{
	cPlayer* player = (cPlayer*)FindChild("Player");
	if (nullptr == player) return;
	cEnemyManager& em = cEnemyManager::GetInstance();

	std::list<IBaseObject*>::iterator it = em.GetChildList()->begin();
	std::list<IBaseObject*>::iterator end = em.GetChildList()->end();

	while (it != end)
	{
		cHitObject* obj = (cHitObject*)(*it);
		// �G�ƃv���C���[�̓����蔻�������
		if (player->CheckHitObject(*obj))
		{
			// ��������
			return;
		}
		it++;
	}


	cBulletManager& bm = cBulletManager::GetInstance();
	std::list<IBaseObject*>::iterator bit = bm.GetChildList()->begin();
	std::list<IBaseObject*>::iterator bend = bm.GetChildList()->end();

	while (bit != bend)
	{
		cHitObject* obj = (cHitObject*)(*bit);
		if (obj->GetHitCate() == cHitObject::HIT_ENEMY)
		{
			// �v���C���[�ƓG�̒e�̓����蔻�������
			if (player->CheckHitObject(*obj))
			{
				// ��������
				return;
			}
		}
		bit++;
	}
}

//==========================================================================================
//  �G�Ǝ��@�̒e�̓����蔻��
//==========================================================================================
void cGameMain::CheckHitEnemy(void)
{
	cEnemyManager& em = cEnemyManager::GetInstance();
	std::list<IBaseObject*>::iterator it = em.GetChildList()->begin();
	std::list<IBaseObject*>::iterator end = em.GetChildList()->end();

	cBulletManager& bm = cBulletManager::GetInstance();
	std::list<IBaseObject*>::iterator bit = bm.GetChildList()->begin();
	std::list<IBaseObject*>::iterator bend = bm.GetChildList()->end();


	while (it != end)
	{
		cHitObject* obj = (cHitObject*)(*it);

		while (bit != bend)
		{
			cHitObject* bobj = (cHitObject*)(*bit);
			if (bobj->GetHitCate() == cHitObject::HIT_PLAYER)
			{
				// �S�I�u�W�F�N�g�Ɠ����蔻�������
				obj->CheckHitObject(*bobj);
				// �G�ƃv���C���[�̒e�����蔻�������
				//if (obj->CheckHitObject(*bobj))
				//{
				//	// ��������
				//	break;
				//}
			}
			bit++;
		}
		bit = bm.GetChildList()->begin();
		it++;
	}
}
