/*==============================================================================*/
/*																				*/
/*	@file title	:	IEnemyBase.cpp												*/
/*  @brief		:	�G�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "IEnemyBase.h"
#include "..\Effect\cEffectManager.h"
#include "..\..\..\cGame.h"
#include "..\..\..\SceneManager\cSceneManager.h"
#include "..\..\..\SceneManager\Scene\GameMain\cGameMain.h"
#include "..\Player\cPlayer.h"

//==========================================================================================
// �萔
//==========================================================================================
const int  IEnemyBase::AREAOUT_ADJUST = 100; // �G���A�A�E�g����
const int  IEnemyBase::ATTACK_POS = 300;	 // �U�����W
const float IEnemyBase::HIT_DIST = 130.0f;	 // �����蔻��̔��a

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
IEnemyBase::IEnemyBase(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cSpriteObject(parent, object_name, graphic_file_name),
	m_vPosUp(0.0f,0.0f),
	m_nScore(0),
	m_fDist( HIT_DIST )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
IEnemyBase::~IEnemyBase(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void IEnemyBase::Initialize(void)
{
	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void IEnemyBase::Update(void)
{
	cGameMain* gm = (cGameMain*)GetParent()->GetParent();

	// �Q�[���v���C���ɂ̂ݓG�𓮂���
	if( gm->GetGameState() == cGameMain::GAME_STATE::PLAY)
	{
		m_vPos += m_vPosUp;
	}
	
	// ��ʍ��ɃG���A�A�E�g������G���폜����
	AreaOutLeftProc();

	cSpriteObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* IEnemyBase::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// ���S����
//==========================================================================================
void IEnemyBase::Dead( void )
{
	DeleteObject();
}

//==========================================================================================
// �U���J�n�֐�
//==========================================================================================
void IEnemyBase::StartAttack( void )
{
	// �G�t�F�N�g�����ʒu�Z�o
	cVector2 vec = m_vPos;
	vec.x -= ATTACK_POS;

	// �U���G�t�F�N�g����
	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	if( em ) em->Create(EFFECT_ID::HIT,vec);
}

//==========================================================================================
// ���G���A�A�E�g����
//==========================================================================================
void IEnemyBase::AreaOutLeftProc(void)
{
	if (m_vPos.x + GetSpriteSize().x / 2 < ((cGame*)GetRoot())->GetPlayArea().left - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// ��G���A�A�E�g����
//==========================================================================================
void IEnemyBase::AreaOutUpProc(void)
{
	if (m_vPos.y + GetSpriteSize().y / 2 < ((cGame*)GetRoot())->GetPlayArea().top - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// �E�G���A�A�E�g����
//==========================================================================================
void IEnemyBase::AreaOutRightProc(void)
{
	if (m_vPos.x - GetSpriteSize().x / 2 > ((cGame*)GetRoot())->GetPlayArea().right + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// ���G���A�A�E�g����
//==========================================================================================
void IEnemyBase::AreaOutBottomProc(void)
{
	if (m_vPos.y - GetSpriteSize().y / 2 > ((cGame*)GetRoot())->GetPlayArea().bottom + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// �S�����G���A�A�E�g����
//==========================================================================================
void IEnemyBase::AreaOutAllProc(void)
{
	AreaOutLeftProc();
	AreaOutUpProc();
	AreaOutRightProc();
	AreaOutBottomProc();
}