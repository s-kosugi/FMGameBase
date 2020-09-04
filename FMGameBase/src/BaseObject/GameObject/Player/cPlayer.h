#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cAnimSpObject.h"

//================================================================================================
// �v���C���[�N���X
class cPlayer : public cAnimSpObject
{
public:
	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void) override;
	void Update(void) override;
	IBaseObject* Finalize(void) override;

private:
	// �v���C���[�̈ړ����x
	static const float MOVE_SPEED;

	// �Q�[���J�n�ʒu
	static const float START_POS_X;
	static const float START_POS_Y;
	// �\���D��x
	static const int	PRIORITY;

	// �͈͊O����
	void ProcAreaOut(void);

};
//================================================================================================