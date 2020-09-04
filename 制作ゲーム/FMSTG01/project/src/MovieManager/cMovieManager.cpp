/*==============================================================================*/
/*																				*/
/*	@file title	:	cMovieManager.cpp											*/
/*  @brief		:	����Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/06													*/
/*																				*/
/*==============================================================================*/

#include "cMovieManager.h"
#include "..\cGame.h"
#include <DxLib.h>


//==========================================================================================
// �萔

//==========================================================================================
// ������
//==========================================================================================
void cMovieManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "MovieManager";
	m_ePlayState = STATE_WAIT;
	m_nGraphHandle = LOADMOVIE_NONE;

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cMovieManager::Update(void)
{
	IBaseObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cMovieManager::Finalize(void)
{
	IBaseObject::Finalize();

	Unload();

	return nullptr;
}
//==========================================================================================
// ����t�@�C���̓ǂݍ���
//==========================================================================================
void cMovieManager::Load(std::string filename)
{
	// ���ɓǂݍ��܂�Ă��铮�悪����ꍇ�͍폜���Ă��烍�[�h
	if (m_nGraphHandle != LOADMOVIE_NONE) DeleteGraph(m_nGraphHandle);

	m_nGraphHandle = LoadGraph(filename.c_str());
	m_ePlayState = STATE_WAIT;
}
//==========================================================================================
// ����t�@�C���̓ǂݍ���
//==========================================================================================
void cMovieManager::Load(MovieID id)
{
	Load(MOVIEFILE_TABLE[id]);
}
//==========================================================================================
// ����̍Đ��J�n
//==========================================================================================
void cMovieManager::Start(void)
{
	if ( m_nGraphHandle == LOADMOVIE_NONE ) return;

	if (0 == GetMovieStateToGraph(m_nGraphHandle) && m_ePlayState == STATE_WAIT)
	{
		// �Đ��J�n
		PlayMovieToGraph(m_nGraphHandle);
		m_ePlayState = STATE_PLAY;
	}
}
//==========================================================================================
// ����f�[�^�̍Đ�
//==========================================================================================
void cMovieManager::Play(void)
{
	if( m_nGraphHandle == LOADMOVIE_NONE ) return;

	// ����Đ����͎��s���x�𗎂Ƃ�
	cGame::GetInstance().SetFPS(PLAYMOVIE_FPS);

	// �Đ��I��	
	if(0 == GetMovieStateToGraph(m_nGraphHandle))
	{
		// ���悪�I�������̂Œ�~
		Stop();
		return;
	}
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);
	
	// ����̕`��
	DrawExtendGraph(0,0,cGame::GetInstance().GetWindowWidth(),cGame::GetInstance().GetWindowHeight(),m_nGraphHandle,FALSE);

}
//==========================================================================================
// �����~
//==========================================================================================
void cMovieManager::Stop(void)
{
	m_ePlayState = STATE_STOP;
	cGame::GetInstance().ResetFPS();

	Unload();
}
//==========================================================================================
// ����f�[�^�̉��
//==========================================================================================
void cMovieManager::Unload(void)
{
	if (m_nGraphHandle != LOADMOVIE_NONE) DeleteGraph(m_nGraphHandle);
	m_nGraphHandle = LOADMOVIE_NONE;
}
