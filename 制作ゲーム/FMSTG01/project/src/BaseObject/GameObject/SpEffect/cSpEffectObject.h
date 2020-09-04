#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectObject.h											*/
/*  @brief		:	�X�v���C�g�G�t�F�N�g�I�u�W�F�N�g							*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �X�v���C�g�G�t�F�N�g�I�u�W�F�N�g
// �P�N���X�ɂ��P�̃G�t�F�N�g�����������ꍇ�Ɏg�p����B
class cSpEffectObject : public cSpriteObject
{
public:
	cSpEffectObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cSpEffectObject(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:

};
//================================================================================================