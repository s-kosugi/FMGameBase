#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cRedFairy.h													*/
/*  @brief		:	�ԗd���N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/23													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemyBase.h"

//================================================================================================
// �ԗd���N���X
class cRedFairy : public IEnemyBase
{
public:
	cRedFairy(IBaseObject* parent);
	~cRedFairy(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	void Dead( void ) override;

	void StartAttack(void)override;

private:
	
	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;

	// �ړ����x
	static const float	MOVE_SPEED;

	// �o�E���h�p�^�C�}�[
	static const float  BOUND_TIME;

	// �o��Y���W����
	static const int	BOUND_START_POS;

	//--------------------------------------------------------------------------------------------
	// �ϐ�
	float				m_fFrameBuffer;		//	�O�t���[���̈ړ��ʂ̕ۑ��o�b�t�@
};
//================================================================================================