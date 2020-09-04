/*==============================================================================*/
/*																				*/
/*	@file title	:	cSprite.cpp													*/
/*  @brief		:	�X�v���C�g�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include "cSprite.h"
#include "..\cDrawCtrl.h"
#include "Utility/StrControl/StrControl.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cSprite::cSprite(const std::string& filename):
	m_SrcRect({ 0,0,0,0 }),
	m_vCenter( 0.0f,0.0f ),
	m_vAnchor( 0.0f,0.0f ),
	m_vScale( 1.0f,1.0f ),
	m_BlendMode(DX_BLENDMODE_ALPHA),
	m_fAngle(0.0f),
	IDrawBase(filename)
{
	// ASS�t�@�C���łȂ��ꍇ�ɂ͂��̂܂ܕ`�����o�^
	if (!Ends_With(filename, ".ass"))
		cDrawCtrl::GetInstance().RegistDrawObject(*this,filename);
}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cSprite::~cSprite(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cSprite::
Initialize(void)
{
	IDrawBase::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cSprite::Update(void)
{
	IDrawBase::Update();
}
//==========================================================================================
//  ���
//==========================================================================================
void cSprite::Finalize(void)
{
	IDrawBase::Finalize();
}
//==========================================================================================
// �X�v���C�g�̋�`�����Z�b�g
//==========================================================================================
void cSprite::SetSrcRect(RECT rect)
{
	m_SrcRect = rect;
	// Rect���ς�����̂ŃX�v���C�g�̒��S�ʒu�������I�ɕς���
	SetCenter(GetSpriteSize().x / 2.0f, GetSpriteSize().y / 2.0f);
}
//==========================================================================================
// �X�v���C�g�̋�`�����Z�b�g
//==========================================================================================
void cSprite::SetSrcRect(int Startx, int Starty, int Sizex, int Sizey)
{
	m_SrcRect.left = Startx;
	m_SrcRect.right = m_SrcRect.left + Sizex;
	m_SrcRect.top = Starty;
	m_SrcRect.bottom = m_SrcRect.top + Sizey;

	// Rect���ς�����̂ŃX�v���C�g�̒��S�ʒu�������I�ɕς���
	SetCenter( GetSpriteSize().x / 2.0f, GetSpriteSize().y / 2.0f );
}

//=========================================================================
// �X�v���C�g�̃T�C�Y�̎擾
// return POINT
//=========================================================================
POINT cSprite::GetSpriteSize(void)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if (IsFileLoaded())
	{
		pt.x = (m_SrcRect.right - m_SrcRect.left);
		pt.y = (m_SrcRect.bottom - m_SrcRect.top);
	}
	else
	{
		//ErrorLogAdd("GetSpriteSize Error! m_nGraphHandle is None\n");
	}
	return pt;
}