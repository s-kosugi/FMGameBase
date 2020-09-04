#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.h												*/
/*  @brief		:	�G�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "EnemyID.h"
#include "Utility/Vector/cVector2.h"

// �O���錾
class IEnemyBase;

// �G�Ǘ��N���X
class cEnemyManager : public IBaseObject
{
public:
	// �R���X�g���N�^
	cEnemyManager( IBaseObject* pObj );
	~cEnemyManager( void );

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �G����
	IEnemyBase* Create( EnemyID id);

	// �����蔻��
	// vec �����蔻�������I�u�W�F�N�g�̈ʒu
	// dist �����蔻�������I�u�W�F�N�g�̔��a
	// return true �v���C���[�̍U������������ false �v���C���[�̍U����������Ȃ�����
	bool	JudgeHit( const cVector2& vec ,float dist ); 

	// �v���C���[�Ƃ̓����蔻��
	// vec �v���C���[�̈ʒu
	// dist �v���C���[�̓����蔻�蔼�a
	// return true �v���C���[���G�̍U���͈͓̔� false �v���C���[���G�̍U���͈̔͊O
	bool	JudgePlayer( const cVector2& vec ,float dist ); 
private:

	int		m_nTimer;		// �G�̏o������^�C�}�[

	static const int DEFAULT_POP_INTERVAL;			// �����o���Ԋu
	static const int DIFFICULT_POP_RATE;			// ��Փx�ɂ��G�̏o���p�x�̔{��

};