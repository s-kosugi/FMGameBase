#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossLaserBullet.h											*/
/*  @brief		:	�{�X���[�U�[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/24													*/
/*																				*/
/*==============================================================================*/

#include "..\cBulletBase.h"

//================================================================================================
// �{�X���[�U�[�N���X
class cBossLaserBullet : public cBulletBase
{
public:
	cBossLaserBullet(IBaseObject* parent);
	cBossLaserBullet(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cBossLaserBullet(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// ���[�U�[�z�u�̊J�n
	void StartConfig( float fAngle  );

	// ���ˊp�x�̃Z�b�g
	// angle : �x���@�̊p�x,0�x���^��
	void SetShootAngle(float angle);

	// �I�u�W�F�N�g�̐�������
	inline void SetLifeCounter(short time) { m_nLifeCounter = time; };

private:
	static const float HIT_RANGE;	// �����蔻��̑傫��
	static const int DEFAULT_ATK;	// �f�t�H���g�U����
	static const int PRIORITY;		// �\���D��x
	static const short DEFAULT_LIFETIME; // �f�t�H���g��������

	short			 m_nLifeCounter;	// �I�u�W�F�N�g�̐�������

};
//================================================================================================