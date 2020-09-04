#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreManager.h												*/
/*  @brief		:	�X�R�A�Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/01/13													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"

class cScoreManager : public IBaseSingleton<cScoreManager>
{
public:
	// ������
	void Initialize(void);

	// �j��
	IBaseObject* Finalize(void);

	// �X�R�A���Z�b�g
	inline void ResetScore(void) { m_nCurrentScore = 0; };

	// �X�R�A���Z
	inline void AddScore(int score) { m_nCurrentScore += score; };

	inline int GetScore(void) { return m_nCurrentScore; };
	inline int GetHiScore(void) { return m_nHiScore; };
	inline int GetTimeBonus(void) { return m_nTimeBonus; };

	// �^�C���{�[�i�X�Z�b�g
	inline void SetTimeBonus(int bonus) { m_nTimeBonus = bonus; };

private:

	// ���݃X�R�A
	int m_nCurrentScore;

	// �n�C�X�R�A
	int m_nHiScore;

	// �^�C���{�[�i�X
	int m_nTimeBonus;
};