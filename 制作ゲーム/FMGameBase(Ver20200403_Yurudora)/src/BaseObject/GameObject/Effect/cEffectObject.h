#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectObject.h												*/
/*  @brief		:	�G�t�F�N�g�I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "..\..\..\DrawCtrl\Effect\cEffect.h"

//================================================================================================
// �G�t�F�N�g�I�u�W�F�N�g
// �P�N���X�ɂ��P�̃G�t�F�N�g�����������ꍇ�Ɏg�p����B
class cEffectObject : public IBaseObject, public cEffect
{
public:
	cEffectObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cEffectObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

};
//================================================================================================

//================================================================================================
// �I�u�W�F�N�g�����֐�
//================================================================================================
// �I�u�W�F�N�g����
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g���Ɖ摜�t�@�C�������w�肷��B
// return : ���������I�u�W�F�N�g
template <class T> T* CreateEffectObject(IBaseObject* parent, const std::string& name, const std::string& filename)
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T(parent, name, filename);

	// �e������΃��X�g�ɒǉ�
	if (parent) parent->AddChild(t);

	// �I�u�W�F�N�g�̕ԋp
	return t;
}
