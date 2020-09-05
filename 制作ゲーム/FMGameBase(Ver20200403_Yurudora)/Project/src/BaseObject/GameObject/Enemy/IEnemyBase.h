#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IEnemyBase.h												*/
/*  @brief		:	�G�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �G�x�[�X�N���X
class IEnemyBase : public cSpriteObject
{
public:
	IEnemyBase(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~IEnemyBase(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// ���S����
	virtual void Dead( void );

	// �U���J�n
	virtual void StartAttack(void);		

	// �����蔻��̔��a���擾
	inline float GetDist( void ) { return m_fDist; };
protected:
	cVector2	m_vPosUp;		// �ړ��l
	int			m_nScore;		// �l���X�R�A
	float		m_fDist;		// �����蔻��̔��a


	// �G���A�A�E�g����
	void AreaOutLeftProc( void );
	void AreaOutUpProc( void );
	void AreaOutRightProc( void );
	void AreaOutBottomProc( void );
	void AreaOutAllProc( void );

	static const int	AREAOUT_ADJUST;	// �G���A�A�E�g����
	static const int	ATTACK_POS;		// �U�����W
	static const float	HIT_DIST;		// �����蔻��̔��a
};
//================================================================================================