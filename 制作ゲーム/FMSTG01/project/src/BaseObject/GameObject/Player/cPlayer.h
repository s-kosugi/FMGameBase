#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\cHitObject.h"

//================================================================================================
// �v���C���[�N���X
class cPlayer : public cHitObject
{
public:
	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �{���c���̎擾
	inline short GetBomNum( void ){ return m_nBomNum; };

private:
	//-----------------------------------------------------------------------
	// �萔

	// HP
	const int MAX_HP = 1000;

	// �ړ����x
	const float MOVE_SPEED = 5.0f;

	// �Q�[���J�n�ʒu
	const float START_POS_X = 300.0f;
	const float START_POS_Y = 700.0f;
	// �\���D��x
	const int	PRIORITY = 350;

	// �摜�̃T�C�Y
	const short SIZE_X = 64;
	const short SIZE_Y = 64;

	// �A�j���[�V��������
	const short ANIM_NUM = 3;

	// �A�j���[�V��������
	const short ANIM_TIME = 4;

	// �����蔻��̑傫��
	const float HIT_RANGE = 15.0f;

	// ���G����(�_���[�W��)
	const int FLASH_MAX_TIME = 60;

	// �t���b�V���̓_�ŊԊu
	const int FLASH_INTERVAL = 5;

	// ���̔����J�nHP�̊���
	const float SMOKE_START_RATE = 0.3f;
	// ���̔����Ԋu
	const short SMOKE_START_INTERVAL = 30;
	// ���̐F
	const unsigned int SMOKE_COLOR = 0xffffffff;

	// ���S��̑ҋ@����
	const int DEAD_WAIT_TIME = 60;

	// ���@�̒e�̓������ː�
	static const int   BULLET_NUM = 4;
	// �e�̈ړ����x
	const float BULLET_SPEED = 18.0f;
	// ���@�̒e�̐F
	const unsigned int BULLET_COLOR = 0xffaaaaff;
	// ���@�̒e���ˈʒu�e�[�u��
	cVector2 SHOT_START_POS[BULLET_NUM] = { { -20.0f,0.0f } ,{ -12.0f,-4.0f } ,{ 12.0f,-4.0f } ,{ 19.0f,0.0f } };
	// ���@�̍��E��Nway�e�̐�
	const short			NWAY_BULLET_NUM = 3;
	// nWay�e�̔��ˊԊu
	const float			NWAY_BULLET_ANGLE_INTERVAL = 8.0f;
	// nWay�e�̊J�n�p�x
	const float			NWAY_BULLET_START_ANGLE = 15.0f;
	// �ʏ�V���b�g���ˊԊu
	const short			SHOT_INTERVAL = 12;

	// �z�[�~���O�e�̈ړ����x
	const float HOMING_BULLET_SPEED = 9.0f;
	// �z�[�~���O�e�̉�]�p�x
	const float HOMING_ROTATE = 5.0f;
	// �z�[�~���O�e�̍ő吔
	const unsigned int HOMING_MAX_NUM = 5;
	// �z�[�~���O�e�̐F
	const unsigned int HOMING_COLOR = 0xffffaaff;
	// �z�[�~���O���[�U�[�̏o���Ԋu
	const unsigned int HOMING_NEXT_POPTIME = 2;
	// ���[�U�[���ˏ�Ԏ���
	const short LASER_STATE_TIME = 240;
	// ���[�U�[�̔��ˊԊu
	const short LASER_SHOOT_INTERVAL = 10;
	// ���[�U�[���ˊp�x�͈̔�
	const int   LASER_ANGLE_RANGE = 80;
	// ���[�U�[�̃G���A�A�E�g�␳�l
	const int	LASER_AREAOUT_ADJUST = 80;
	// ���[�U�[�̍U����
	const int	LASER_ATK = 500;
	// �{�����̏����l
	const short DEFAULT_BOM_NUM = 5;

	//-----------------------------------------------------------------------
	// ��ԕʏ���
	void Normal( void );
	void Hit( void );
	void Flash( void );
	void Dead( void );

	// �L�[���쏈��
	void OperationKey( void );
	// �͈͊O����
	void ProcAreaOut( void );
	// ����������
	void AppeaSmoke( void );
	// ���[�U�[���ˏ���
	void ShootLaser( void );

	// ���̔����^�C�}�[
	short m_nSmokeTimer;

	// ���G����
	int m_nFlashTimer;

	// ���S��ҋ@����
	int m_nDeadTimer;

	// �ʏ�e���ˊԊu�^�C�}�[
	short m_nShotCoolTime;

	// ���[�U�[���ˏ�ԊǗ��^�C�}�[
	short m_nLaserTimer;

	// �{���̎c��
	short m_nBomNum;


	// �o�����o���̈ړ���
	cVector2 m_vPosUp;

	// �o�����o�t���O
	bool  m_bAppear;
};
//================================================================================================