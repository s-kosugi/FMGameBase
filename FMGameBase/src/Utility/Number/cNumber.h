#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cNumber.h													*/
/*  @brief		:	�����I�u�W�F�N�g											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "BaseObject/cSpriteObject.h"

//================================================================================================
// �����N���X
class cNumber : public cSpriteObject
{
public:
	cNumber(IBaseObject* parent, std::string objectname, std::string filename);
	~cNumber(void);


	void Initialize(void) override;
	void Update(void) override;
	IBaseObject* Finalize(void) override;

	// �����̐���
	void CreateNumber(short maxdigit, int value);

	// ���l�̐ݒ�
	inline void SetValue(int value) { m_nValue = value; };

	// �`��D��x�̐ݒ�
	void SetPriority( int priority );

protected:
	static const int	MAX_DIGIT;		// �ő包�������l

	int					m_nValue;		// �\�����鐔�l
	int					m_nMaxDigit;	// �ő包��
};
//================================================================================================