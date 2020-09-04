#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreManager.h												*/
/*  @brief		:	�X�R�A�Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/03													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"

// �X�R�A�Ǘ��N���X
class cScoreManager : public IBaseObject
{
public:
	// �R���X�g���N�^
	cScoreManager(IBaseObject* pObj);

	// �f�X�g���N�^
	~cScoreManager( void );

	// ������
	void Initialize( void );

	// �j��
	IBaseObject* Finalize( void );

	// �X�R�A���Z�b�g
	inline void ResetScore( void ) { m_nCurrentScore = 0; };

	// �X�R�A���Z
	inline void AddScore( int score ) { m_nCurrentScore += score; };

	// �X�R�A�擾
	inline int GetScore( void ) { return m_nCurrentScore; };


private:

	// ���݃X�R�A
	int m_nCurrentScore;

};