/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.cpp											*/
/*  @brief		:	�G�t�F�N�g�Ǘ��N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "cEffectManager.h"
#include "HitEffect\cHitEffect.h"
#include "BomEffect\cBomEffect.h"
#include "SlashEffect/cSlashEffect.h"
#include "GetScoreEffect/cGetScoreEffect.h"
#include "LandingEffect/cLandingEffect.h"
#include "IceAttackEffect/cIceAttackEffect.h"
#include "FlameEffect/cFlameEffect.h"
#include "FlameHitEffect/cFlameHitEffect.h"
#include "DrawCtrl/cDrawCtrl.h"

#pragma warning(disable: 26495)
#include "EffekseerForDXLib.h"

//==========================================================================================
// �萔
//==========================================================================================

const std::string cEffectManager::EFFECT_FILE_NAME[] = {
	"data\\effect\\hit_player.efkefc",
	"data\\effect\\bom.efk",
	"data\\effect\\slash.efkefc",
	"data\\effect\\get_score.efkefc",
	"data\\effect\\landing.efkefc",
	"data\\effect\\IceAttack.efkefc",
	"data\\effect\\flame.efkefc",
	"data\\effect\\flame.efkefc"
};

//==========================================================================================
// ������
//==========================================================================================
void cEffectManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "EffectManager";

	// �S�G�t�F�N�g�̃��[�h
	LoadAllEffect();

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEffectManager::Update(void)
{
	IBaseObject::Update();

	// �G�t�F�N�V�A�̍X�V
	UpdateEffekseer2D();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cEffectManager::Finalize(void)
{
	// �S�G�t�F�N�g�̒�~
	for( auto it : m_listChildObject )
	{
		( (cEffectObject*)it )->Stop();
	}

	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// ����
//==========================================================================================
cEffectObject* cEffectManager::Create(EFFECT_ID id,cVector2 pos)
{
	cEffectObject* obj = nullptr;
	switch (id)
	{
	case EFFECT_ID::HIT: obj = CreateObject<cHitEffect>(this); break;
	case EFFECT_ID::BOM: obj = CreateObject<cBomEffect>(this); break;
	case EFFECT_ID::SLASH: obj = CreateObject<cSlashEffect>(this); break;
	case EFFECT_ID::GETSCORE: obj = CreateObject<cGetScoreEffect>(this); break;
	case EFFECT_ID::LANDING: obj = CreateObject<cLandingEffect>(this); break;
	case EFFECT_ID::ICEATTACK: obj = CreateObject<cIceAttackEffect>(this); break;
	case EFFECT_ID::FLAME: obj = CreateObject<cFlameEffect>(this); break;
	case EFFECT_ID::FLAME_HIT: obj = CreateObject<cFlameHitEffect>(this); break;
	}

	if (obj != nullptr)
	{
		obj->Initialize();
		obj->SetPos(pos);
	}
	return obj;
}

//==========================================================================================
// �G�t�F�N�g�t�@�C���̓Ǎ�
//==========================================================================================
void cEffectManager::LoadEffect(EFFECT_ID id)
{
	cDrawCtrl::GetInstance().LoadDrawFile(EFFECT_FILE_NAME[(int)id], DRAWTYPE::EFFECT);
}

//==========================================================================================
// �S�t�@�C���̓Ǎ�
//==========================================================================================
void cEffectManager::LoadAllEffect(void)
{
	for (int i = 0; i < (int)EFFECT_ID::MAX; i++)
	{
		LoadEffect((EFFECT_ID)i);
	}
}