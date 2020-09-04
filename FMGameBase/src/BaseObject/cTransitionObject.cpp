/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransitionObject.cpp										*/
/*  @brief		:	�g�����W�V�����I�u�W�F�N�g									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/02/12													*/
/*																				*/
/*==============================================================================*/

#include "cTransitionObject.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTransitionObject::cTransitionObject(IBaseObject* parent, const std::string& objectname, const std::string& ruleFilename, const std::string& spriteFileName, TransDirection dir, float transTime) :
	IBaseObject(parent, objectname),
	cTransition(ruleFilename, m_pSprite = new cSprite(spriteFileName), dir, transTime)
{
	// ���摜�̃X�v���C�g�摜�͔�\���ɂ���
	m_pSprite->SetVisible(false);
}
//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTransitionObject::cTransitionObject(IBaseObject* parent, const std::string& objectname, const std::string& ruleFilename, IDrawBase* pTransObj, TransDirection dir, float transTime) :
	IBaseObject(parent, objectname),
	cTransition(ruleFilename, pTransObj, dir, transTime),
	m_pSprite(nullptr)
{
}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cTransitionObject::~cTransitionObject(void)
{
	SAFE_DELETE(m_pSprite);
}

//==========================================================================================
//  ������
//==========================================================================================
void
cTransitionObject::
Initialize(void)
{
	IBaseObject::Initialize();
	cTransition::Initialize();
}

//==========================================================================================
//  ������
//==========================================================================================
void cTransitionObject::Initialize(const cVector2& pos)
{
	m_vPos = pos;
	Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cTransitionObject::Update(void)
{
	IBaseObject::Update();
	cTransition::Update();

}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cTransitionObject::Finalize(void)
{
	IBaseObject::Finalize();
	cTransition::Finalize();
	return this;
}