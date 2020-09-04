#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.h													*/
/*  @brief		:	�Q�[�����C���V�[��											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// �Q�[�����C���V�[��
class cGameMain : public IBaseScene
{
public:
	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize( void );
	void Update( void );
	IBaseObject* Finalize( void );

	// �Q�[����Ԃ̐ݒ�
	enum class GAME_STATE
	{
		START = 0,
		PLAY,
		OVER
	};

	// ��Փx�̎擾
	inline int			GetDifficult( void ) { return m_nDifficult; };

	// �Q�[����Ԃ̎擾
	inline GAME_STATE	GetGameState( void ) { return m_eGameState;};

	// �Q�[����Ԃ̐ݒ�
	inline void			SetGameState( GAME_STATE st ) { m_eGameState = st; };

	// �n�ʂ̃��C���̎擾
	inline int			GetLandingLine( void ){ return LANDING_LINE; };

private:
	// �Q�[���J�n
	void Start(void);
	// �Q�[����
	void Play(void);
	// �Q�[���I�[�o�[
	void Over(void);

	int			m_nDifficult;			// ��Փx ���������Ȃ��قǈՂ���
	GAME_STATE	m_eGameState;			// �Q�[�����

	//--------------------------------------------------------------------------------------------
	// �萔
	static const float LEVELUP_TIME;	// ��Փx���オ��܂ł̎���(�b)
	static const int MAX_DIFFICULT;		// �ő��Փx
	static const float GAMEOVER_TIME;	// �Q�[���I�[�o�[��Ԃ̎���
	static const int LANDING_LINE;		// �n�ʂ̃��C��
	static const float GAMESTART_TIME;	// �Q�[���X�^�[�g��Ԃ̎���
};
//================================================================================================