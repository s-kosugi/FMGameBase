#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransition.h												*/
/*  @brief		:	�g�����W�V�����N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/11													*/
/*																				*/
/*==============================================================================*/

#include "..\IDrawBase.h"
#include "Utility/Timer/cTimer.h"

//================================================================================================
// �g�����W�V�����N���X
// ���j�o�[�T���g�����W�V�������s���A�o����������o�̐�����s��

class cTransition : public IDrawBase
{
public:
	// �g�����W�V�������s������
	enum class TransDirection {
		TRANS_IN = 0,
		TRANS_OUT,
	};

	// -------------------------------------------------------------------------------------------
	// �R���X�g���N�^
	// filename  : ���[���摜�̃t�@�C����
	// pObj      : �u�����h���錳�摜�̃I�u�W�F�N�g�̃|�C���^
	// dir       : TRANS_IN �t�F�[�h�C��   TRANS_OUT �t�F�[�h�A�E�g
	// transtime : �g�����W�V��������
	cTransition(const std::string& filename, IDrawBase* pObj, TransDirection dir, float transtime);

	// �f�X�g���N�^
	~cTransition();

	// ������
	void Initialize(void);
	// �X�V
	void Update(void);
	// �j��
	void Finalize(void);


	//---------------------------------------------------------------------
	// �萔

	// DrawBlendGraph�Ŏg�����E��
	enum class BorderRange {
		RANGE_1 = 1,
		RANGE_64 = 64,
		RANGE_128 = 128,
		RANGE_255 = 255,
	};

	// Getter
	inline IDrawBase* GetTransObject(void) { return m_pTransObj; };
	inline float		GetBorderParam(void) { return m_fBorderParam; };
	inline BorderRange	GetBorderRange(void) { return m_eBorderRange; };

	// �g�����W�V�������I���������ǂ����H
	//  ret : true �I������ false : �Đ���
	bool				IsEnd(void);

	// Setter
	inline void SetTransTime(float time) { m_fTransTime = time; };
	inline void SetTransDirection(TransDirection value) { m_eTransDirection = value; value == TransDirection::TRANS_IN ? m_fBorderParam = 0.0f : m_fBorderParam = (float)BORDER_MAX; };
	inline void SetBorderParam(float param) { m_fBorderParam = param; };
	inline void SetBorderRange(BorderRange range) { m_eBorderRange = range; };

private:
	//---------------------------------------------------------------------
	// �萔

	static const float	BORDER_MAX;			// ���E�ʒu�̍ő�l
	static const int	DEFAULT_PRIORITY;	// �\���D��x



	IDrawBase* m_pTransObj;		// �J�ڐ�̉摜�̃|�C���^
	BorderRange		m_eBorderRange;		// DrawBlendGraph�Ŏg�����E��
	float			m_fBorderParam;		// DrawBlendGraph�Ŏg�����E�ʒu
	TransDirection	m_eTransDirection;	// �g�����W�V�������s������(�t�F�[�h�C�����A�E�g��)
	float			m_fTransTime;		// ���v�g�����W�V��������(�b)
	cTimer			m_cTimer;			// �g�����W�V�����^�C�}�[
};