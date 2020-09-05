#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpriteObject.h												*/
/*  @brief		:	�`��I�u�W�F�N�g											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/01													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"
#include "..\DrawCtrl\Sprite\cSprite.h"

//================================================================================================
// �`��I�u�W�F�N�g
// �P�N���X�ɂ��P�̃X�v���C�g�����������ꍇ�Ɏg�p����B
class cSpriteObject : public IBaseObject, public cSprite
{
public:
	cSpriteObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cSpriteObject( void );


	virtual void Initialize( void );
	virtual void Initialize( const cVector2& pos );
	virtual void Update( void );
	virtual IBaseObject* Finalize( void );

private:

};
//================================================================================================

//================================================================================================
// �I�u�W�F�N�g�����֐�
//================================================================================================
// �I�u�W�F�N�g����
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g���Ɖ摜�t�@�C�������w�肷��B
// return : ���������I�u�W�F�N�g
template <class T> T* CreateDrawObject(IBaseObject* parent, const std::string& name, const std::string& filename)
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T(parent, name,filename);

	// �e������΃��X�g�ɒǉ�
	if (parent) parent->AddChild(t);

	// �I�u�W�F�N�g�̕ԋp
	return t;
}
