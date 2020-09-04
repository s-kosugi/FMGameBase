/*==============================================================================*/
/*																				*/
/*	@file title	:	cScreenFlash.cpp											*/
/*  @brief		:	�X�N���[���_�ŃG�t�F�N�g�N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "cScreenFlash.h"
#include "..\..\Enemy\cEnemyManager.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\..\..\SoundCtrl\cSoundCtrl.h"
#include "..\cSpEffectManager.h"

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cScreenFlash::cScreenFlash(IBaseObject * parent)
	: cSpEffectObject(parent, "ScreenFlhash", "data\\graphic\\white.png"),
	m_nLifeTime( DEFAULT_LIFE_TIME ),
	m_nMaxLifeTime( DEFAULT_LIFE_TIME)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cScreenFlash::~cScreenFlash(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cScreenFlash::Initialize(void)
{
	m_nMaxLifeTime = m_nLifeTime = DEFAULT_LIFE_TIME;


	cSpEffectObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cScreenFlash::Update(void)
{
	m_nLifeTime--;

	SetAlpha((unsigned int)(((float)m_nLifeTime) / ((float)m_nMaxLifeTime) * 200.0f));

	if( m_nLifeTime <= 0 ) m_eObjectState = OBJECT_STATE_DEAD;

	cSpEffectObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cScreenFlash::Finalize(void)
{
	cSpEffectObject::Finalize();

	return this;
}