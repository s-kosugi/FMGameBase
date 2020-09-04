#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cSurfaceObject.h											*/
/*  @brief		:	�T�[�t�F�C�X�I�u�W�F�N�g									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/03/03													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"
#include "DrawCtrl/Surface/cSurface.h"

//================================================================================================
// �`��I�u�W�F�N�g
// �P�N���X�ɂ��P�̃T�[�t�F�C�X�����������ꍇ�Ɏg�p����B
class cSurfaceObject : public IBaseObject, public cSurface
{
public:

	//---------------------------------------------
	// �R���X�g���N�^
	// parent : �e�I�u�W�F�N�g
	// name : �I�u�W�F�N�g��
	// width : �T�[�t�F�C�X�̉���
	// height : �T�[�t�F�C�X�̍���
	// beginPriority : �T�[�t�F�C�X�Ɋ܂߂�J�n�̕`��D��x
	// endPriority : �T�[�t�F�C�X�Ɋ܂߂�I���̕`��D��x
	// alpha : �����x��L���ɂ��邩�ǂ��� (TRUE : �L�� )
	cSurfaceObject(IBaseObject* parent, const std::string& objectname, int width, int height, int beginPriority, int endPriority, int alpha);
	~cSurfaceObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

};
//================================================================================================

//================================================================================================
// �I�u�W�F�N�g�����֐�
//================================================================================================
// �T�[�t�F�C�X�I�u�W�F�N�g����
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g�ƃT�[�t�F�C�X�ɕK�v�ȍ��ڂ��w�肷��B
// parent : �e�I�u�W�F�N�g
// name : �I�u�W�F�N�g��
// width : �T�[�t�F�C�X�̉���
// height : �T�[�t�F�C�X�̍���
// beginPriority : �T�[�t�F�C�X�Ɋ܂߂�J�n�̕`��D��x
// endPriority : �T�[�t�F�C�X�Ɋ܂߂�I���̕`��D��x
// alpha : �����x��L���ɂ��邩�ǂ��� (TRUE : �L�� )
// return : ���������I�u�W�F�N�g
template <class T> T* CreateSurfaceObject(IBaseObject* parent, const std::string& name, int width, int height, int beginPriority, int endPriority, int alpha)
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T(parent, name, width, height, beginPriority, endPriority, alpha);

	// �e������΃��X�g�ɒǉ�
	if (parent) parent->AddChild(t);

	// �I�u�W�F�N�g�̕ԋp
	return t;
}

template <class T> T* CreateSurfaceObject(IBaseObject* parent, const std::string& name, int width, int height, int beginPriority, int endPriority)
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T(parent, name, width, height, beginPriority, endPriority, TRUE);

	// �e������΃��X�g�ɒǉ�
	if (parent) parent->AddChild(t);

	// �I�u�W�F�N�g�̕ԋp
	return t;
}

