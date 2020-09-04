/*==============================================================================*/
/*																				*/
/*	@file title	:	cNumber.cpp													*/
/*  @brief		:	�����I�u�W�F�N�g											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "cNumber.h"
#include <string>

//==========================================================================================
// �萔
//==========================================================================================
const int cNumber::MAX_DIGIT = 3;

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cNumber::cNumber(IBaseObject* parent, std::string objectname, std::string filename) :
	cSpriteObject(parent, objectname, filename),
	m_nMaxDigit(MAX_DIGIT),
	m_nValue(0)
{

}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cNumber::~cNumber(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cNumber::
Initialize(void)
{
	// ���̃N���X���g�̕\���͂��Ȃ�
	m_bVisible = false;

	cSpriteObject::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cNumber::Update(void)
{
	int i = 0;
	int value = m_nValue;
	for (auto it = m_listChildObject.begin(); it != m_listChildObject.end(); it++, i++)
	{
		cSpriteObject* pNumber = ((cSpriteObject*)*it);
		int num = value % 10;
		int width = pNumber->GetSpriteSize().x;

		// ���l�̏ꏊ�̐ݒ�
		pNumber->SetPos(m_vPos.x - width * i, m_vPos.y);
		pNumber->SetSrcRect(num * width, 0, width, pNumber->GetSpriteSize().y);

		pNumber->SetDrawColor(m_nColor);

		value /= 10;
	}
	cSpriteObject::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cNumber::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
//==========================================================================================
//  �����̐���
//  filename : �\������摜
//  maxdigit : �ő包��
//  value : �\�����鐔�l
//==========================================================================================
void cNumber::CreateNumber(short maxdigit, int value)
{
	for (int i = 0; i < maxdigit; i++)
	{
		std::string num;
		num = std::to_string(i);
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, m_sObjectName + num, m_sFileName);
		obj->Initialize();
		// �摜���P�������ɐݒ肷��
		obj->SetSrcRect(0, 0, obj->GetSrcRect().right / 10, obj->GetSrcRect().bottom);
		obj->SetPriority(GetPriority());
	}
	m_nMaxDigit = maxdigit;
	m_nValue = value;
}

//==========================================================================================
//  �`��D��x�̐ݒ�
//==========================================================================================
void cNumber::SetPriority( int priority )
{
	for( auto it : m_listChildObject )
	{
		cSpriteObject* obj = (cSpriteObject*)it;
		obj->SetPriority(priority);
	}
	IDrawBase::SetPriority(priority);
}
