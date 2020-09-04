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
#include "Input\Keyboard\cKeyboard.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"
#include "SceneManager\cSceneManager.h"
#include "Utility\CsvReader\cCsvReader.h"
#include "DrawCtrl/Camera/cCamera.h"
#include "ScoreManager/cScoreManager.h"
#include <time.h>
#include "Utility\memory.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif // DEBUG

//==========================================================================================
// �萔
//==========================================================================================
const float             cGame::MAX_DELTA_TIME = 0.16f;		// �ő�f���^�^�C��
const float				cGame::ONE_MILL_SECOND = 1000.0f;	// �P�b
const int				cGame::CALC_FRAME_COUNT = 60;		// ���ς��v�Z����t���[���̐�
const int				cGame::WINDOW_SIZE_X = 1280;		// �E�B���h�E��
const int				cGame::WINDOW_SIZE_Y = 720;			// �E�B���h�E����

//==========================================================================================
//  ������
//==========================================================================================
void cGame::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "Game";

	// �E�B���h�E�̏����ʒu���o���Ă���
	int x, y = 0;
	GetWindowPosition(&x, &y);
	m_DefaultWindowPos = { x , y };

	// �`�摀��N���X
	AddChild(&cDrawCtrl::GetInstance());

	// �G�t�F�N�g�}�l�[�W���[�̒ǉ�
	AddChild( &cEffectManager::GetInstance() );

	// ����Ǘ��N���X
	AddChild(&cMovieManager::GetInstance());

	// �T�E���h����N���X
	AddChild(&cSoundCtrl::GetInstance());
	// �S�T�E���h�̓ǂݍ���
	cSoundCtrl::GetInstance().LoadAll();

	// ���͊Ǘ��N���X
	AddChild(&cControllerManager::GetInstance());

	// �V�[���}�l�[�W���[�N���X
	AddChild(&cSceneManager::GetInstance());

	// Csv�Ǎ��N���X
	AddChild(&cCsvReader::GetInstance());

	// �J�����N���X
	AddChild(&cCamera::GetInstance());

	// �X�R�A�Ǘ��N���X
	CreateObject<cScoreManager>(this);

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
	// �t���[���J�E���g�Z�o
	CalcFrameCount();

	for (int i = 0; i < m_nOneFrameUpdate; i++)
	{
		// �ʏ�̍X�V
		IBaseObject::Update();
	}

	// �V�X�e���L�[�̃`�F�b�N
	CheckSystemKey();
}
//==========================================================================================
//  �`��
//==========================================================================================
void cGame::Draw(void)
{
	cDrawCtrl::GetInstance().Draw();
#ifdef DEBUG
	cDebugFunc::GetInstance().Draw();
#endif
}

//==========================================================================================
// �����̔���
//==========================================================================================
int cGame::Random(int min, int max)
{
	int range;

	range = max - min;
	return GetRand(range) + min;
}
//==========================================================================================
// �E�B���h�E�̈ʒu�����_�ɂ���
//==========================================================================================
void cGame::SetWindowPosOrigin(void)
{
	SetWindowPosition(0, 0);
}

//==========================================================================================
// �E�B���h�E�̈ʒu�������ʒu�ɂ���B
//==========================================================================================
void cGame::SetWindowPosDefault(void)
{
	SetWindowPosition(m_DefaultWindowPos.x, m_DefaultWindowPos.y);
}

//==========================================================================================
// �X�V����t���[���J�E���g�̌v�Z
//==========================================================================================
void cGame::CalcFrameCount(void)
{
	// ���݂̎��Ԃ��擾
	int now_time = GetNowCount();

	// �v�Z�J�n��
	if (m_nFrameCount == 0)
	{
		m_nStartTime = now_time;
	}
	// �w�肳�ꂽ�t���[���J�E���g��
	else if (m_nFrameCount == CALC_FRAME_COUNT)
	{
		m_nFrameCount = 0;

		m_nStartTime = now_time;
	}

	// �t���[���J�E���g���X�V
	++m_nFrameCount;

	// �O�̏����Ƃ̎��Ԃ̍�
	int sub_time = now_time - m_nPrevTime;

	// �f���^�^�C�����Z�o
	m_fDeltaTime = (float)sub_time / ONE_MILL_SECOND;

	// �ő�f���^�^�C���Ő�������
	if (m_fDeltaTime > MAX_DELTA_TIME) m_fDeltaTime = MAX_DELTA_TIME;

	// ���̎��Ԃ�ۑ�
	m_nPrevTime = now_time;
}
//==========================================================================================
// �V�X�e���L�[�̃`�F�b�N
//==========================================================================================
void cGame::CheckSystemKey(void)
{
	// ALT+Enter�ŃE�B���h�E�ʒu�̐؂�ւ�
	if (cKeyboard::GetInstance().CheckButton(KEY_INPUT_LALT) || cKeyboard::GetInstance().CheckButton(KEY_INPUT_RALT))
	{
		if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_RETURN)) ChangeWindowPos();
	}
	// Esc�L�[�ŃQ�[���̏I��
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

//==========================================================================================
// �E�B���h�E�ʒu�̐؂�ւ�
//==========================================================================================
void cGame::ChangeWindowPos(void)
{
	int x, y = 0;
	GetWindowPosition(&x, &y);
	if (x == m_DefaultWindowPos.x && y == m_DefaultWindowPos.y)
	{
		SetWindowPosOrigin();
	}
	else
	{
		SetWindowPosDefault();
	}
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cGame::cGame(void):
	m_nFPS(DEFAULT_FPS),
	m_nOneFrameUpdate(1),
	m_fDeltaTime(0.0f),
	m_fDeltaTimeScale(1.0f),
	m_nFrameCount(0),
	m_nStartTime(0),
	m_nPrevTime(0),
	m_PlayArea({ 0,0,GetWindowWidth(),GetWindowHeight() })
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cGame::cGame(IBaseObject* parent):
	cGame::cGame()
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cGame::cGame(IBaseObject* parent, const std::string& name):
	cGame::cGame(parent)
{
}

//==========================================================================================
// �R�s�[�R���X�g���N�^
//==========================================================================================
cGame::cGame(const cGame& t):
	cGame::cGame()
{
}
