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

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cSprite::cSprite(const std::string& filename) :
	m_SrcRect({ 0,0,0,0 }),
	m_vCenter( 0.0f,0.0f ),
	m_vScale( 1.0f, 1.0f ),
	m_BlendMode(DX_BLENDMODE_ALPHA),
	m_fStartAngle(0.0f),
	m_fEndAngle(0.0f),
	m_fAngle(0.0f),
	m_Animation({ {0,0},{0,0},0,0,0,0 }),
	m_eSpType(SPTYPE_NORMAL),
	IDrawBase(filename)
{
	// �`�����o�^
	cDrawCtrl::GetInstance().RegistDrawObject(*this,filename);
}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cSprite::~cSprite(void)
{
	cDrawCtrl::GetInstance().RemoveDrawObject(this);
}

//==========================================================================================
//  ������
//==========================================================================================
void
cSprite::
Initialize(void)
{
	// �A�j���[�V�������Z�b�g����Ă�����\���摜���X�V����
	if ( 0 < m_Animation.AnimMax) {
		// �\�����W�X�V
		m_SrcRect.left = m_Animation.StartPos.x + m_Animation.AnimFrame * m_Animation.Size.x;
		m_SrcRect.right = m_SrcRect.left + m_Animation.Size.x;
		m_SrcRect.top = m_Animation.StartPos.y;
		m_SrcRect.bottom = m_SrcRect.top + m_Animation.Size.y;

		// �A�j���[�V�������Z�b�g����Ă����璆�S�ʒu��ύX����B(�����_�ȉ��l�̌ܓ�)
		m_vCenter.x = (float)((int)(m_Animation.Size.x / 2.0f + 0.5f));
		m_vCenter.y = (float)((int)(m_Animation.Size.y / 2.0f + 0.5f));
	}
	IDrawBase::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cSprite::Update(void)
{
	// �A�j���[�V�������Z�b�g����Ă镨�̂݃A�j���[�V��������������
	if ( 0 < m_Animation.AnimMax) {
		if (m_Animation.TimerCount >= m_Animation.AnimTime)
		{
			// �A�j���[�V�����X�V
			++m_Animation.AnimFrame %= m_Animation.AnimMax;
			// �^�C�}�[���Z�b�g
			m_Animation.TimerCount = 0;

			// �\�����W�X�V
			m_SrcRect.left = m_Animation.StartPos.x + m_Animation.AnimFrame * m_Animation.Size.x;
			m_SrcRect.right = m_SrcRect.left + m_Animation.Size.x;
			m_SrcRect.top = m_Animation.StartPos.y;
			m_SrcRect.bottom = m_SrcRect.top + m_Animation.Size.y;
		}
		m_Animation.TimerCount++;
	}
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
void cSprite::SetSrcRect(int Startx, int Starty, int Sizex, int Sizey)
{
	m_SrcRect.left = Startx;
	m_SrcRect.right = m_SrcRect.left + Sizex;
	m_SrcRect.top = Starty;
	m_SrcRect.bottom = m_SrcRect.top + Sizey;
}
//==========================================================================================
// �A�j���[�V�������̃Z�b�g
//==========================================================================================
void cSprite::SetAnimation(int Startx, int Starty, int width, int height, short AnimMax, short AnimTime)
{
	Animation anim;
	anim.StartPos.x = Startx;
	anim.StartPos.y = Starty;
	anim.Size.x = width;
	anim.Size.y = height;
	anim.AnimMax = AnimMax;
	anim.AnimTime = AnimTime;
	anim.AnimFrame = 0;
	anim.TimerCount = 0;
	m_Animation = anim;
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