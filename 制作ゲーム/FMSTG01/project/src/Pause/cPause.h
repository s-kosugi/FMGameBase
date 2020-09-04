#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPause.h													*/
/*  @brief		:	�|�[�Y�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/01/16													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"

class cPause : public IBaseSingleton<cPause>
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �|�[�Y�����ǂ������擾
	inline bool IsPause(void) { return m_bPause; };


	// �|�[�Y��Ԃ̊J�n
	void StartPause( void );

	// �|�[�Y��Ԃ̏I��
	void EndPause( void );
private:
	enum PauseState
	{
		PAUSE_STATE_START,
		PAUSE_STATE_WAIT
	};

	// ��ԕʏ���
	void Start( void );
	void Wait( void );

	static const int   PRIORITY = 4000;				// �\���D��x
	static const unsigned int MASK_MAX_ALPHA = 140;	// �}�X�N�̍ő哧���x
	static const int	PAUSE_COMP_TIME = 60;			// �|�[�Y��������

	static const float FONT_POS_X;
	static const float FONT_POS_Y;
	static const unsigned int FONT_COLOR;


	bool		m_bPause;			// �|�[�Y�����ǂ���
	int			m_nPauseCount;		// �|�[�Y�J�n����̌o�ߎ���
	PauseState  m_ePauseState;		// �|�[�Y��ʂ̏��
};