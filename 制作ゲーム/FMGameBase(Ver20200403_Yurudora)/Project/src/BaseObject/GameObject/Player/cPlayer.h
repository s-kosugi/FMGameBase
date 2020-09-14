#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �v���C���[�N���X
class cPlayer : public cSpriteObject
{
public:
	cPlayer( IBaseObject* parent );
	~cPlayer( void );

	void Initialize( void );
	void Update( void );
	IBaseObject* Finalize( void );


	// �v���C���[�̓����蔻��擾
	inline int GetPlayerDist( void ) { return PLAYER_DIST; };
private:

	cVector2	m_vPosUp;			// �ړ����x
	cVector2	m_vAccele;			// �����x
	bool		m_bLand;			// �ڒn�t���O
	int			m_nFailedTimer;		// �U�����s�^�C�}�[


	void JumpWalk( void );			// �W�����v�ړ�
	void Attack( void );			// �U��

	//--------------------------------------------------------------------------------------------
	// �萔
	static const float	START_POS_X;			// �Q�[���J�n�ʒux
	static const float	START_POS_Y;			// �Q�[���J�n�ʒuy
	static const int	PRIORITY = 200;			// �\���D��x
	static const int	LANDING_LINE = 100;		// �ڒn���C��
	static const float	JUMP_POWER;				// �W�����v��
	static const float	GRAVITY;				// �d�͉����x
	static const int	ATTACK_POS = 300;		// �U���G�t�F�N�g�Đ��ʒu
	static const int	ATTACK_RANGE = 200;		// �v���C���[�̍U���͈�
	static const int	FAILED_TIME = 60;		// �U�����s���̍U���s�\����
	static const int	PLAYER_DIST = 200;		// �v���C���[�{�̂̓����蔻�蔼�a


	//--------------------------------------------------------------------------------------------

};
//================================================================================================