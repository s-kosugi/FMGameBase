/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.cpp											*/
/*  @brief		:	�G�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cEnemyManager.h"
#include "WhiteCore\cEnmWhiteCore.h"
#include "SwimmingFloat\cEnmSwimmingFloat.h"
#include "BlueCore\cEnmBlueCore.h"
#include "YellowCore\cEnmYellowCore.h"
#include "RedCore\cEnmRedCore.h"
#include "GreenCore\cEnmGreenCore.h"
#include "BossFiveTube\cBossFiveTube.h"
#include "BossFiveTube\BossLeftBattery\cBossLeftBattery.h"
#include "BossFiveTube\BossRightBattery\cBossRightBattery.h"

//==========================================================================================
// ������
//==========================================================================================
void cEnemyManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "EnemyManager";

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnemyManager::Update(void)
{

	IBaseObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cEnemyManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// �G����
// return : ���������G�̃|�C���^ ��������Ȃ������ꍇ��nullptr
//==========================================================================================
cEnemyBase* cEnemyManager::Create(EnemyID id)
{
	cEnemyBase* pObj = nullptr;
	switch (id)
	{
		case ENM_ID_WHITE_CORE:
			pObj = CreateObject<cEnmWhiteCore>(this);
			pObj->Initialize();
			break;
		case ENM_ID_SWIMMING_FLOAT:
			pObj = CreateObject<cEnmSwimmingFloat>(this);
			pObj->Initialize();
			break;
		case ENM_ID_BLUE_CORE:
			pObj = CreateObject<cEnmBlueCore>(this);
			pObj->Initialize();
			break;
		case ENM_ID_YELLOW_CORE:
			pObj = CreateObject<cEnmYellowCore>(this);
			pObj->Initialize();
			break;
		case ENM_ID_BOSS_FIVETUBE:
			pObj = CreateObject<cBossFiveTube>(this);
			pObj->Initialize();
			break;
		case ENM_ID_BOSS_FIVETUBE_RIGHTBAT:
			pObj = CreateObject<cBossRightBattery>(this);
			pObj->Initialize();
			break;
		case ENM_ID_BOSS_FIVETUBE_LEFTBAT:
			pObj = CreateObject<cBossLeftBattery>(this);
			pObj->Initialize();
			break;
		case ENM_ID_RED_CORE:
			pObj = CreateObject<cEnmRedCore>(this);
			pObj->Initialize();
			break;
		case ENM_ID_GREEN_CORE:
			pObj = CreateObject<cEnmGreenCore>(this);
			pObj->Initialize();
			break;
	}

	return pObj;
}