#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cBomStock.h													*/
/*  @brief		:	�{���X�g�b�N�I�u�W�F�N�g									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// �{���X�g�b�N�N���X
class cBomStock : public cUIObject
{
public:
	cBomStock(IBaseObject* parent);
	~cBomStock(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	const int PRIORITY = 2001;

	const int CREATE_BOMVISIBLE_MAX = 6;		// �{���c�e�̍ő�\����

	const int STOCK_OFFSET_X = 30;				// �{���c�e�\�����ǂꂾ�����炷��
	const int STOCK_OFFSET_Y = 23;				// �{���c�e�\�����ǂꂾ�����炷��
	const int STOCK_INTERVAL_X = 28;			// �{���c�e��\������Ԋu
};
//================================================================================================