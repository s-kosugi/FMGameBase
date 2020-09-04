/*==============================================================================*/
/*																				*/
/*	@file title	:	cSurface.cpp												*/
/*  @brief		:	�T�[�t�F�C�X�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/02/26													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include "cSurface.h"
#include "..\cDrawCtrl.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cSurface::cSurface(void) :
	IDrawBase(),
	m_vAngle( 0.0f,0.0f,0.0f ),
	m_vCenter(0.0f, 0.0f),
	m_vScale(1.0f, 1.0f),
	m_Rect({ 0,0,0,0 }),
	m_nBlendMode(DX_BLENDMODE_ALPHA)
{
	// �T�[�t�F�C�X�̓I�u�W�F�N�g�폜���Ƀ���������A�����[�h����
	m_bUnload = true;
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cSurface::~cSurface()
{
	Delete();
}
//==========================================================================================
//  �T�[�t�F�C�X�쐬
//==========================================================================================
void cSurface::Create(int width, int height, int beginPriority,int endPriority, bool alpha)
{
	// �`�����o�^
	cDrawCtrl::GetInstance().RegistSurface(*this,width,height,alpha);

	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = width;
	m_Rect.bottom = height;
	m_vCenter.x = width / 2.0f;
	m_vCenter.y = height/ 2.0f;

	SetPriority(endPriority);
	m_cBeginPoint.SetPriority(beginPriority);
}
//==========================================================================================
//  �T�[�t�F�C�X���
//==========================================================================================
void cSurface::Delete(void)
{
	// �`����̓o�^����
	cDrawCtrl::GetInstance().RemoveSurface(this);
}
