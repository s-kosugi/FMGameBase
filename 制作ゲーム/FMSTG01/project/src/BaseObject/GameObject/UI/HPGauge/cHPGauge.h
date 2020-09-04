#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGauge.h													*/
/*  @brief		:	HP�Q�[�W�I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// HP�Q�[�W�N���X
class cHPGauge : public cUIObject
{
public:
	cHPGauge(IBaseObject* parent);
	~cHPGauge(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	const int PRIORITY = 2003;
	const float START_ANGLE = 0.0f;		// 0����ԏ��100��1�T����p�x 
	const float END_ANGLE = 75.0f;

	const float EFFECT_START_DIFF = 60.0f;	// �G�t�F�N�g��\������ʒu�̍���
};
//================================================================================================