#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cMovieManager.h												*/
/*  @brief		:	����Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/06													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"
#include "MovieID.h"

class cMovieManager : public IBaseSingleton<cMovieManager>
{
public:
	// ����̍Đ����
	enum PlayState {
		STATE_WAIT = 0,
		STATE_PLAY,
		STATE_STOP,
	};

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// ����t�@�C���̓ǂݍ���
	void Load(std::string filename);
	void Load(MovieID id);

	// ����̍Đ��J�n
	void Start( void );

	// ����̍Đ�
	void Play(void);

	// ����̒�~
	void Stop(void);

	// ����f�[�^�̉��
	void Unload( void );

	// ����̍Đ���Ԃ��擾
	inline PlayState GetPlayState(void) { return m_ePlayState; };

private:
	int			m_nGraphHandle;		// ����t�@�C���̃n���h��
	PlayState	m_ePlayState;		// ����̍Đ����

	// ����Đ����̎��s���x
	static const int PLAYMOVIE_FPS = 30;
	// �n���h�����擾
	static const int LOADMOVIE_NONE = -1;

	// ����t�@�C�����e�[�u��
	std::string MOVIEFILE_TABLE[MOVIE_MAX] =
	{
		"data\\movie\\Start.avi",
	};
};