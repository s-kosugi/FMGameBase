#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cNumber.h													*/
/*  @brief		:	�����I�u�W�F�N�g											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// �����N���X
class cNumber : public cUIObject
{
public:
	cNumber(IBaseObject* parent,std::string objectname,std::string filename);
	~cNumber(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �����̐���
	void CreateNumber(short maxdigit, int value);

	// ���l�̐ݒ�
	inline void SetValue(int value) { m_nValue = value; };

protected:
	static const int	MAX_DIGIT;		// �ő包�������l

	int					m_nValue;		// �\�����鐔�l
	int					m_nMaxDigit;	// �ő包��
};
//================================================================================================