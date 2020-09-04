/*==============================================================================*/
/*																				*/
/*	@file title	:	cGame.cpp													*/
/*  @brief		:	�Q�[���N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/14													*/
/*																				*/
/*==============================================================================*/

#include "cGame.h"
#include "SoundCtrl\cSoundCtrl.h"
#include "DrawCtrl\cDrawCtrl.h"
#include "MovieManager/cMovieManager.h"
#include "Input\cControllerManager.h"
#include "CsvReader\cCsvReader.h"
#include "ScoreManager\cScoreManager.h"
#include "SceneManager\cSceneManager.h"
#include "Pause\cPause.h"
#include <time.h>
#include "Utility\memory.h"
#include "Utility\utility.h"

#ifdef DEBUG
#include "DebugFunc\cDebugFunc.h"
#endif

cGame::~cGame()
{
}
//==========================================================================================
//  ������
//==========================================================================================
void cGame::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "Game";

	// FPS
	m_nFPS = DEFAULT_FPS;

	// 1�t���[�����̍X�V��
	m_nOneFrameUpdate = 1;

	// �v���C�G���A�̐ݒ�(UI�\���̈悪���邱�Ƃ�z��)
	m_PlayArea = { 0,0,PLAYAREA_RIGHT,PLAYAREA_BOTTOM };

	// �`�摀��N���X
	AddChild(&cDrawCtrl::GetInstance());

	// ����Ǘ��N���X
	AddChild(&cMovieManager::GetInstance());

	// �T�E���h����N���X
	AddChild(&cSoundCtrl::GetInstance());
	// �S�T�E���h�̓ǂݍ���
	cSoundCtrl::GetInstance().LoadAll();

	// ���͊Ǘ��N���X
	AddChild(&cControllerManager::GetInstance());

	// CSV�ǂݍ��݃N���X
	AddChild(&cCsvReader::GetInstance());

	// �X�R�A�Ǘ��N���X
	AddChild(&cScoreManager::GetInstance());

	// �V�[���}�l�[�W���[�N���X
	AddChild(&cSceneManager::GetInstance());

	// �|�[�Y�N���X
	AddChild(&cPause::GetInstance());

#ifdef DEBUG
	// �f�o�b�O�@�\�N���X
	AddChild(&cDebugFunc::GetInstance());
#endif

	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cGame::Update(void)
{
	if (cMovieManager::GetInstance().GetPlayState() == cMovieManager::PlayState::STATE_PLAY)
	{
		// ���[�r�[�Đ�
		cMovieManager::GetInstance().Play();

		// ���͂���邽�߂ɍX�V����
		cControllerManager::GetInstance().Update();

		// �����ꂩ�̃L�[�������ꂽ�烀�[�r�[�I��
		if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_ANY))
			cMovieManager::GetInstance().Stop();
	}
	else if (cPause::GetInstance().IsPause())
	{
		// �|�[�Y��

		// ���͂���邽�߂ɍX�V����
		cControllerManager::GetInstance().Update();

		// �|�[�Y�N���X�̍X�V
		cPause::GetInstance().Update();

		// �|�[�Y����
		if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_PAUSE))
			cPause::GetInstance().EndPause();
	}
	else
	{
		for (int i = 0; i < m_nOneFrameUpdate; i++)
		{
			// �ʏ�̍X�V
			IBaseObject::Update();
		}
	}
}
//==========================================================================================
//  �`��
//==========================================================================================
void cGame::Draw(void)
{
	// �`��
	cDrawCtrl::GetInstance().Draw();

#ifdef DEBUG
	cDebugFunc::GetInstance().Draw();
#endif
}
//==========================================================================================
//  �I��
//==========================================================================================
IBaseObject* cGame::Finalize(void)
{
	IBaseObject::Finalize();

	return nullptr;
}

//==========================================================================================
// �����̔���
//==========================================================================================
int cGame::Random(int min, int max)
{
	static unsigned int cnt = 0;
	int range;

	if (cnt == 0) {
		srand((unsigned int)time(NULL));
		cnt = 1;
	}
	if( min >= max ) return 0;
	range = max - min + 1;
	return((rand() % range) + min);
}
