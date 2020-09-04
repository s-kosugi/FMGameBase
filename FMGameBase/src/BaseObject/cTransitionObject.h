#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransitionObject.h											*/
/*  @brief		:	�g�����W�V�����I�u�W�F�N�g									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/02/12													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"
#include "..\DrawCtrl\Transition\cTransition.h"
#include "..\DrawCtrl\Sprite\cSprite.h"

//================================================================================================
// �`��I�u�W�F�N�g
// �P�N���X�ɂ��P�̃X�v���C�g�����������ꍇ�Ɏg�p����B
class cTransitionObject : public IBaseObject, public cTransition
{
public:

	//---------------------------------------------
	// �R���X�g���N�^
	// parent : �e�I�u�W�F�N�g
	// name : �I�u�W�F�N�g��
	// ruleFIlename : ���[���摜�t�@�C����
	// spriteFileName : �X�v���C�g�摜�̃t�@�C����
	// dir : �g�����W�V��������
	// transtime : �g�����W�V��������
	cTransitionObject(IBaseObject* parent, const std::string& objectname, const std::string& ruleFilename, const std::string& spriteFileName, TransDirection dir, float transtime);
	//---------------------------------------------
	// �R���X�g���N�^
	// parent : �e�I�u�W�F�N�g
	// name : �I�u�W�F�N�g��
	// ruleFIlename : ���[���摜�t�@�C����
	// transObj : �J�ڐ�I�u�W�F�N�g
	// dir : �g�����W�V��������
	// transtime : �g�����W�V��������
	cTransitionObject(IBaseObject* parent, const std::string& objectname, const std::string& ruleFilename, IDrawBase* pTransObj, TransDirection dir, float transtime);

	~cTransitionObject(void);


	virtual void Initialize(void);
	virtual void Initialize(const cVector2& pos);
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

private:
	cSprite* m_pSprite;			// �摜�N���X�ւ̃|�C���^
};
//================================================================================================

//================================================================================================
// �I�u�W�F�N�g�����֐�
//================================================================================================
// �g�����W�V�����I�u�W�F�N�g����
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g�ƃg�����W�V�����ɕK�v�ȍ��ڂ��w�肷��B
// parent : �e�I�u�W�F�N�g
// name : �I�u�W�F�N�g��
// ruleFIlename : ���[���摜�t�@�C����
// spriteFileName : �X�v���C�g�摜�̃t�@�C����
// dir : �g�����W�V��������
// transtime : �g�����W�V��������(�b)
// return : ���������I�u�W�F�N�g
template <class T> T* CreateTransitionObject(IBaseObject* parent, const std::string& name, const std::string& ruleFilename, const std::string& spriteFileName, cTransition::TransDirection dir, float transtime)
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T(parent, name, ruleFilename, spriteFileName, dir, transtime);

	// �e������΃��X�g�ɒǉ�
	if (parent) parent->AddChild(t);

	// �I�u�W�F�N�g�̕ԋp
	return t;
}

// �g�����W�V�����I�u�W�F�N�g����
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g�ƃg�����W�V�����ɕK�v�ȍ��ڂ��w�肷��B
// parent : �e�I�u�W�F�N�g
// name : �I�u�W�F�N�g��
// ruleFIlename : ���[���摜�t�@�C����
// �J�ڐ�摜�|�C���^
// dir : �g�����W�V��������
// transtime : �g�����W�V��������
// return : ���������I�u�W�F�N�g
template <class T> T* CreateTransitionObject(IBaseObject* parent, const std::string& name, const std::string& ruleFilename, IDrawBase* pTransObj, cTransition::TransDirection dir, float transtime)
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T(parent, name, ruleFilename, pTransObj, dir, transtime);

	// �e������΃��X�g�ɒǉ�
	if (parent) parent->AddChild(t);

	// �I�u�W�F�N�g�̕ԋp
	return t;
}
