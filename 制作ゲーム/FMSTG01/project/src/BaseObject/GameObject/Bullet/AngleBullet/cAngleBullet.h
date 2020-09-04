#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cAngleBullet.h												*/
/*  @brief		:	�p�x�w��e�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cBulletBase.h"

//================================================================================================
// �p�x�w��e�N���X
class cAngleBullet : public cBulletBase
{
public:
	cAngleBullet(IBaseObject* parent);
	cAngleBullet(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cAngleBullet(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// ���ˊp�x�̃Z�b�g
	// angle : �x���@�̊p�x,0�x���^��
	void SetShootAngle(float angle);

private:
	static const float HIT_RANGE;	// �����蔻��̑傫��
	static const int DEFAULT_ATK;	// �f�t�H���g�U����
	static const int PRIORITY;		// �\���D��x

};
//================================================================================================