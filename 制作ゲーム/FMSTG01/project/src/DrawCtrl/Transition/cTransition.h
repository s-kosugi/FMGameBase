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
#include "..\..\Utility\Vector\cVector3.h"

//================================================================================================
// �g�����W�V�����N���X
// ��ʐ؂�ւ����ʗp

class cTransition : public IDrawBase
{
public:
	cTransition(const std::string& filename, IDrawBase* pObj);
	~cTransition();

	void Initialize(void);
	void Update(void);
	void Finalize(void);


	//---------------------------------------------------------------------
	// �萔
	static const std::string RULE_CHECKSPHERE;	// ���[���摜�t�@�C��(�`�F�b�N+����)

	// DrawBlendGraph�Ŏg�����E��
	enum BorderRange {
		RANGE_1 = 1,
		RANGE_64 = 64,
		RANGE_128 = 128,
		RANGE_255 = 255,
	};

	// �g�����W�V�������s������
	enum TransDirection {
		TRANS_IN = 0,
		TRANS_OUT,
	};

	// Getter
	inline IDrawBase*	GetTransObject( void ) { return m_pTransObj; };
	inline float		GetBorderParam( void ) { return m_fBorderParam; };
	inline BorderRange	GetBorderRange( void ) { return m_eBorderRange; };
	bool				IsEnd( void );

	// Setter
	inline void SetBorderParamAdd(float value) { m_fBorderParam_Add = value;};
	inline void SetTransDirection(TransDirection value) { m_eTransDirection = value; value == TRANS_IN ? m_fBorderParam = 0.0f : m_fBorderParam = (float)BORDER_MAX; };

private:
	//---------------------------------------------------------------------
	// �萔
	
	static const int		BORDER_MAX;			// ���E�ʒu�̍ő�l
	static const float		BORDER_ADD_DEFAULT;	// ���E�ʒu�̑����l�̏����l
	static const int		DEFAULT_PRIORITY;	// �\���D��x



	IDrawBase*		m_pTransObj;		// �J�ڐ�̉摜�̃|�C���^
	BorderRange		m_eBorderRange;		// DrawBlendGraph�Ŏg�����E��
	float			m_fBorderParam;		// DrawBlendGraph�Ŏg�����E�ʒu
	float			m_fBorderParam_Add;	// 1�t���[���ӂ�ő����鋫�E�ʒu�̑����l
	TransDirection	m_eTransDirection;	// �g�����W�V�������s������(�t�F�[�h�C�����A�E�g��)
};