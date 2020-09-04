#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSnipeBullet.h												*/
/*  @brief		:	�_�������e�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\cBulletBase.h"

//================================================================================================
// �_�������e�N���X
class cSnipeBullet : public cBulletBase
{
public:
	cSnipeBullet(IBaseObject* parent);
	cSnipeBullet(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cSnipeBullet(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// ���ˊp�x�̐ݒ�
	void SetShootAngle(float angle);

	// �ǔ��Ώۂֈړ�����x�N�g�������߂�
	void CalcTargetVector(const cVector2& tPos);

private:
	//-------------------------------------------------------------------------------------------
	// �萔
	static const float HIT_RANGE;	// �����蔻��̑傫��
	static const int PRIORITY;		// �\���D��x
	static const int DEFAULT_ATK;	// �f�t�H���g�U����
};
//================================================================================================