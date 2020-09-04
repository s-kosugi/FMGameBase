#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletManager.h											*/
/*  @brief		:	�e�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "BulletID.h"
#include "..\..\..\Utility\Vector\cVector2.h"

// �e�x�[�X�N���X�̑O���錾
class cBulletBase;

class cBulletManager : public IBaseSingleton<cBulletManager>
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �e����
	// type : �e�̎��  startPos : �e�̊J�n�ʒu  hitCategory : �e�̓����蔻��敪(HIT_PLAYER or HIT_ENEMY) speed : �e�̈ړ����x
	// �߂�l : ���������e�̃|�C���^
	cBulletBase* Create( BulletType type, const cVector2& startPos , int hitCategory,float speed, unsigned int color = 0x00ffffff, const std::string& filename = "none");

	// nWay�e�̐���
	// bulletNum : �e�̔��ː� angleInterval : ���ˊp�x�Ԋu startAngle : �J�n�p�x color : �e�F
	void CreateNWayBullet(const cVector2& startPos, int hitCategory, float speed, const int bulletNum, float angleInterval, float startAngle, unsigned int color = 0x00ffffff, BulletType type = BT_ANGLE,const std::string& = "none");
	
private:

};