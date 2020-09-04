#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cAnimSpObject.h												*/
/*  @brief		:	�A�j���[�V�����`��I�u�W�F�N�g								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/14													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"
#include "..\DrawCtrl\Sprite\cAnimSprite.h"

//================================================================================================
// �A�j���[�V�����`��I�u�W�F�N�g
// �P�N���X�ɂ��P�̃X�v���C�g�����������ꍇ�Ɏg�p����B
class cAnimSpObject : public IBaseObject, public cAnimSprite
{
public:
	cAnimSpObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cAnimSpObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

};
//================================================================================================
