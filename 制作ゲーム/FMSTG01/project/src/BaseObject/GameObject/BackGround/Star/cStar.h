#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStar.h														*/
/*  @brief		:	���I�u�W�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/10													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// ���I�u�W�F�N�g�N���X
class cStar : public cSpriteObject
{
public:
	cStar(IBaseObject* parent);
	~cStar(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	void FlashColor( void );

private:
	enum StarType {
		TYPE_SMALL,
		TYPE_MIDIUM,
		TYPE_LARGE,

		TYPE_MAX
	};

	// ���̎��
	StarType m_eStarType;

	// �ړ����x
	cVector2 m_vPosUp;

	// ���̐F���L�����Ă����ϐ�
	unsigned int m_nSaveColor;

	// �F�̑����l
	float		m_fColorIncrement;

	// �_�ł�������ׂ̃J�E���^�[
	float m_fFlashCounter;

	// �萔
	const float SMALL_STAR_SPEED = 1.0f;
	const float MIDIUM_STAR_SPEED = 1.5f;
	const float LARGE_STAR_SPEED = 2.0f;
	const int	PRIORITY = -50;
};
//================================================================================================