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
#include "Input\Keyboard\cKeyboard.h"
#include "BaseObject/GameObject/Enemy/cEnemyManager.h"
#include "BaseObject/cSurfaceObject.h"
#include "BaseObject/cTransitionObject.h"

#include "BaseObject\GameObject\Player\cPlayer.h"
#include "BaseObject/GameObject/BackGround/cBackGround.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"
#include "ScoreManager/cScoreManager.h"
#include "BaseObject/GameObject/UI/cUIManager.h"
#include "BaseObject/GameObject/SpEffect/cSpEffectManager.h"
#include "SoundCtrl/cSoundCtrl.h"


//==========================================================================================
// �萔
//==========================================================================================
const float cGameMain::LEVELUP_TIME  = 10.0f;	// ��Փx���オ��܂ł̎���(�b)
const int cGameMain::MAX_DIFFICULT	 = 10;		// �ő��Փx
const float cGameMain::GAMEOVER_TIME = 4.0f;	// �Q�[���I�[�o�[��Ԃ̎���(�b)
const int cGameMain::LANDING_LINE = 100;		// �n�ʂ̍���
const float cGameMain::GAMESTART_TIME = 1.5f;	// �Q�[���X�^�[�g��Ԃ̎���(�b)

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
	, m_nDifficult(0)
	, m_eGameState(GAME_STATE::START)
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
	// �w�i�̐���
	cBackGround* obj = CreateObject<cBackGround>( this );
	obj->SetPos( 0.0f, (float)cGame::GetInstance().GetWindowHeight() / 2 );
	obj = CreateObject<cBackGround>( this );
	obj->SetPos( (float)cGame::GetInstance().GetWindowWidth(), (float)cGame::GetInstance().GetWindowHeight() / 2 );

	// �v���C���[�L�����N�^�[�̐���
	CreateObject<cPlayer>(this);

	// �G�Ǘ��N���X�̐���
	CreateObject<cEnemyManager>(this);

	// �X�R�A�̏�����
	cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	if( sm ) sm->ResetScore();

	// �X�v���C�g�G�t�F�N�g�Ǘ��N���X�̐���
	CreateObject<cSpEffectManager>(this);

	// UI�Ǘ��N���X�̐���
	cUIManager* um = CreateObject<cUIManager>(this);
	// �X�R�A�{�[�h�v�̐���
	um->Create( UIID::SCORE_BOARD, { 150, 100 } );

	

	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cGameMain::Update(void)
{
	IBaseObject::Update();

	// �Q�[�����[�h���̊e��ԏ���
	switch( m_eGameState )
	{
	case GAME_STATE::START: Start(); break;
	case GAME_STATE::PLAY: Play(); break;
	case GAME_STATE::OVER: Over(); 	break;
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

//==========================================================================================
//  �Q�[���J�n���
//==========================================================================================
void cGameMain::Start(void)
{
	cTimer* timer = (cTimer*)FindChild("StartTimer");
	cTimer* seTimer = (cTimer*)FindChild("SETimer");
	cSpriteObject* startLogo = (cSpriteObject*)FindChild("StartLogo");
	cGame* game = (cGame*)GetRoot();
	if (!timer)
	{
		// �Q�[���X�^�[�g�^�C�}�[�̍쐬
		timer = CreateObject<cTimer>(this, "StartTimer");
		timer->Setup(GAMESTART_TIME);

		// SE�Đ��J�n�^�C�}�[�̍쐬
		seTimer = CreateObject<cTimer>(this, "SETimer");
		seTimer->Setup(0.5f);

		
		if (!startLogo)
		{
			startLogo = CreateDrawObject<cSpriteObject>(this, "StartLogo", "data\\graphic\\start.png");
			startLogo->SetPos(game->GetWindowWidth() / 2.0f,game->GetWindowHeight() / 2.0f);
			startLogo->SetPriority(500);
		}
	}
	// �X�^�[�g�������A�j���[�V����������
	if (startLogo)
	{
		startLogo->SetScale(Easing::OutBounce(timer->GetTime(),timer->GetLimit(),1.0f,0.0f));
	}
	if (seTimer)
	{
		if (seTimer->Finished())
		{
			cSoundCtrl::GetInstance().Play(SOUND_ID::START);
			seTimer->DeleteObject();
		}
	}

	if (timer->Finished())
	{
		startLogo->DeleteObject();
		timer->DeleteObject();
		if (seTimer) seTimer->DeleteObject();
		// �Q�[����Ԃ��v���C���ɕύX����
		SetGameState(GAME_STATE::PLAY);
	}
}

//==========================================================================================
//  �Q�[���v���C���
//==========================================================================================
void cGameMain::Play(void)
{
	// �i�K�I�ɃQ�[���������邽�߂̏���
	cTimer* lvTimer = (cTimer*)FindChild("LevelUpTimer");
	if (lvTimer)
	{
		if (lvTimer->Finished())
		{
			// ���x���A�b�v�^�C�}�[�����������ē�Փx��1�i�K�グ��
			lvTimer->Reset();
			m_nDifficult++;
			if (m_nDifficult >= MAX_DIFFICULT) m_nDifficult = MAX_DIFFICULT;
		}
	}
	else
	{
		// ���x���A�b�v�^�C�}�[�̐���
		lvTimer = CreateObject<cTimer>(this, "LevelUpTimer");
		lvTimer->Setup(LEVELUP_TIME);
	}
}

//==========================================================================================
//  �Q�[���I�[�o�[���
//==========================================================================================
void cGameMain::Over(void)
{
	cGame* game = (cGame*)GetRoot();

	// �Q�[����ʂ��Z�s�A�J���[�ɂ���
	cSurfaceObject* surface = (cSurfaceObject*)FindChild("MonoSurface");
	cTransitionObject* transition = (cTransitionObject*)FindChild("Transition");
	if ( !surface )
	{
		// ���m�g�[���T�[�t�F�C�X���쐬
		surface = CreateSurfaceObject<cSurfaceObject>(this, "MonoSurface", game->GetWindowWidth(), game->GetWindowHeight(), -202, 501);
		surface->SetPos(game->GetWindowCenter());
		surface->SetFilterMode(cSurface::FILTER_MODE::MONO);
		surface->SetMonoBlue(-60);
		surface->SetMonoRed(7);

		// �g�����W�V�����p�T�[�t�F�C�X���쐬
		surface = CreateSurfaceObject<cSurfaceObject>(this, "SorceSurface", game->GetWindowWidth(), game->GetWindowHeight(), -201, 502);
		surface->SetPos(game->GetWindowCenter());
		surface->SetFilterMode(cSurface::FILTER_MODE::NONE);
		// �g�����W�V�����ŕ\������T�[�t�F�C�X�̈ה�\��
		surface->SetShow(false);

		// �g�����W�V�������쐬
		transition = CreateTransitionObject<cTransitionObject>(this,"Transition","data\\graphic\\rule_02.png",surface,cTransition::TransDirection::TRANS_IN,2.0f);
		transition->SetPriority(550);
	}

	// �g�����W�V�������I�������烊�U���g�V�[����Push����
	if (transition->IsEnd())
	{
		transition->DeleteObject();
		surface = (cSurfaceObject*)FindChild("SorceSurface");
		if(surface) surface->DeleteObject();

		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->PushScene(SCENE_ID::RESULT);
	}
}
