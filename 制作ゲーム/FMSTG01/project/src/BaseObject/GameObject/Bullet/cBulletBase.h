#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletBase.h												*/
/*  @brief		:	�e�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cHitObject.h"

//================================================================================================
// �e�x�[�X�N���X
class cBulletBase : public cHitObject
{
public:
	cBulletBase(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~cBulletBase(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline void SetSpeed(float speed) { m_fSpeed = speed;};
	inline void SetPosUp(cVector2 vPos) { m_vPosUp = vPos; };

protected:
	// �e�������������̏���
	void HitProc( void );

	// �ړ���̃X�v���C�g��]����
	void RotateMoveAfter(void);

	// �e�̈ړ����x
	float m_fSpeed;

	// �e�̈ړ��x�N�g��
	cVector2 m_vPosUp;
};
//================================================================================================