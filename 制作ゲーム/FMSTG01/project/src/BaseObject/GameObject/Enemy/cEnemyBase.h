#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyBase.h												*/
/*  @brief		:	�G�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\cHitObject.h"

//================================================================================================
// �G�x�[�X�N���X
class cEnemyBase : public cHitObject
{
public:
	cEnemyBase(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~cEnemyBase(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

protected:
	cVector2   m_vPosUp;		// �ړ��l

	int		   m_nScore;		// �l���X�R�A
};
//================================================================================================