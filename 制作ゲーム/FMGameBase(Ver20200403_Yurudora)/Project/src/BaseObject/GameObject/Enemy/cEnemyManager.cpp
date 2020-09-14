/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.cpp											*/
/*  @brief		:	�G�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cEnemyManager.h"
#include "..\..\..\SceneManager\cSceneManager.h"
#include "..\..\..\ScoreManager\cScoreManager.h"
#include "..\..\..\SceneManager\Scene\GameMain\cGameMain.h"
#include "RedFairy/cRedFairy.h"
#include "BlueFairy/cBlueFairy.h"

//==========================================================================================
// �萔
//==========================================================================================
const int cEnemyManager::DEFAULT_POP_INTERVAL = 120;  // �����o���Ԋu
const int cEnemyManager::DIFFICULT_POP_RATE = 10;	  // ��Փx�ɂ��G�̏o���p�x�̔{��

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEnemyManager::cEnemyManager( IBaseObject* pObj )
	:IBaseObject( pObj , "EnemyManager")
	, m_nTimer( 0 )
{
}
//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEnemyManager::~cEnemyManager( void )
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEnemyManager::Initialize(void)
{
	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnemyManager::Update(void)
{
	m_nTimer++;
	if(GetParent()->GetObjectName() == "GameMain")
	{
		// ��Փx�ɂ���ēG�̏o���p�x��ύX����
		cGameMain* gm = (cGameMain*)GetParent();
		if( m_nTimer % (DEFAULT_POP_INTERVAL - gm->GetDifficult() * DIFFICULT_POP_RATE) == 0)
			Create( (EnemyID)(rand() % (int)EnemyID::MAX) );
	}
	

	IBaseObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cEnemyManager::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
// �G����
// return : ���������G�̃|�C���^ ��������Ȃ������ꍇ��nullptr
//==========================================================================================
IEnemyBase* cEnemyManager::Create(EnemyID id)
{
	IEnemyBase* pObj = nullptr;
	switch (id)
	{
	case EnemyID::RED_FAIRY:
		pObj = CreateObject<cRedFairy>(this);
		pObj->Initialize();
		break;
	case EnemyID::BLUE_FAIRY:
		pObj = CreateObject<cBlueFairy>(this);
		pObj->Initialize();
		break;
	}

	return pObj;
}

//==========================================================================================
// �����蔻��
// vec �����蔻�������I�u�W�F�N�g�̈ʒu
// dist �����蔻�������I�u�W�F�N�g�̔��a
// return true �v���C���[�̍U������������ false �v���C���[�̍U����������Ȃ�����
//==========================================================================================
bool cEnemyManager::JudgeHit( const cVector2 & vec, float dist )
{
	for( auto it = m_listChildObject.begin(); it != m_listChildObject.end(); it++ )
	{
		IEnemyBase* enm = (IEnemyBase*)(*it);
		if( dist + enm->GetDist() > enm->GetPos().CalcTwoPointDist(vec) )
		{
			// �U�������������̂œG�����S��Ԃɂ���
			enm->Dead();

			// �X�R�A�����Z����
			cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild( "ScoreManager" );
			if( sm ) sm->AddScore( 1 );
			return true;
		}
	}
	return false;
}

//==========================================================================================
// �v���C���[�Ƃ̓����蔻��
// vec �v���C���[�̈ʒu
// dist �v���C���[�̓����蔻�蔼�a
// return true �v���C���[���G�̍U���͈͓̔� false �v���C���[���G�̍U���͈̔͊O
//==========================================================================================
bool cEnemyManager::JudgePlayer( const cVector2 & vec, float dist )
{
	for( auto it = m_listChildObject.begin(); it != m_listChildObject.end(); it++ )
	{
		IEnemyBase* enm = (IEnemyBase*)(*it);
		if( dist + enm->GetDist() > enm->GetPos().CalcTwoPointDist(vec) )
		{
			// �Y���̓G���U����Ԃɂ���
			enm->StartAttack();
			return true;
		}
	}
	return false;
}
