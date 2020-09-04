/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletManager.cpp											*/
/*  @brief		:	íeä«óùÉNÉâÉX												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "cBulletManager.h"

#include "AngleBullet\cAngleBullet.h"
#include "HomingBullet\cHomingBullet.h"
#include "HomingBullet\HomingLaser\cHomingLaser.h"
#include "SnipeBullet\cSnipeBullet.h"
#include "HomingBullet\HomingLaserTale\cHomingLaserTale.h"
#include "BossLaserBullet\cBossLaserBullet.h"

//==========================================================================================
// èâä˙âª
//==========================================================================================
void cBulletManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "BulletManager";

}

//==========================================================================================
// çXêV
//==========================================================================================
void cBulletManager::Update(void)
{
	IBaseObject::Update();
}

//==========================================================================================
// îjä¸
//==========================================================================================
IBaseObject * cBulletManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}
//==========================================================================================
// íeÇÃê∂ê¨
// type : íeÇÃéÌóﬁ  startPos : íeÇÃäJénà íu  hitCategory : íeÇÃìñÇΩÇËîªíËãÊï™(HIT_PLAYER or HIT_ENEMY) speed : íeÇÃà⁄ìÆë¨ìx color : íeÇÃêF
// ñﬂÇËíl : ê∂ê¨ÇµÇΩíeÇÃÉ|ÉCÉìÉ^
//==========================================================================================
cBulletBase* cBulletManager::Create(BulletType type, const cVector2& startPos, int hitCategory, float speed, unsigned int color,const std::string& filename)
{
	cBulletBase* pObj = nullptr;
	switch (type)
	{
	case BT_ANGLE:
		if( filename == "none" ) pObj = CreateObject<cAngleBullet>(this);
		else pObj = CreateDrawObject<cAngleBullet>(this,"AngleBullet",filename);
		break;
	case BT_HOMING_BULLET:
		if( filename == "none") pObj = CreateObject<cHomingBullet>(this);
		else pObj = CreateDrawObject<cHomingBullet>(this, "HomingBullet", filename);
		break;
	case BT_HOMING_LASER:
		if( filename == "none") pObj = CreateObject<cHomingLaser>(this);
		else pObj = CreateDrawObject<cHomingLaser>(this, "HomingLaser", filename);
		break;
	case BT_SNIPE_BULLET:
		if( filename == "none" )pObj = CreateObject<cSnipeBullet>(this);
		else pObj = CreateDrawObject<cSnipeBullet>(this, "SnipeBullet", filename);
		break;
	case BT_HOMING_LASER_TALE:
		if( filename == "none" )pObj = CreateObject<cHomingLaserTale>(this);
		else pObj = CreateDrawObject<cHomingLaserTale>(this, "HomingLaserTale", filename);
		break;
	case BT_BOSS_LASER:
		if (filename == "none")pObj = CreateObject<cBossLaserBullet>(this);
		else pObj = CreateDrawObject<cBossLaserBullet>(this, "BossLaserBullet", filename);
		break;
	}

	if( pObj == nullptr ) return nullptr;
	pObj->SetPos(startPos);
	pObj->SetHitCate((cHitObject::HitCategory)hitCategory);
	pObj->SetSpeed(speed);
	pObj->SetDrawColor( color );

	pObj->Initialize();
	return pObj;
}

//==========================================================================================
// nWayíeÇÃê∂ê¨
// bulletNum : íeÇÃî≠éÀêî angleInterval : î≠éÀäpìxä‘äu startAngle : äJénäpìx color : íeêF
//==========================================================================================
void cBulletManager::CreateNWayBullet(const cVector2 & startPos, int hitCategory, float speed, const int bulletNum, float angleInterval, float startAngle, unsigned int color, BulletType type,const std::string& filename)
{
	cAngleBullet* pObj = nullptr;

	// ãÙêîíeÇæÇ¡ÇΩÇÁäJénäpìxÇïœçXÇ∑ÇÈ
	if (bulletNum % 2 == 0) startAngle = startAngle - angleInterval / 2.0f;

	for (int i = 0; i < bulletNum; i++)
	{
		pObj = (cAngleBullet*)Create(type, startPos, hitCategory, speed,color,filename);
		if (pObj == nullptr) return;

		if (bulletNum % 2 == 1)
		{
			// äÔêîíeÇÃÇPî≠ñ⁄
			if (i == 0)
			{
				pObj->SetShootAngle(startAngle);
				continue;
			}
		}
		// äÔêîî≠ñ⁄
		if (i % 2 == 1)	pObj->SetShootAngle(startAngle + ((int)((i + 1) / 2)) * angleInterval);
		// ãÙêîî≠ñ⁄
		else pObj->SetShootAngle(startAngle - ((int)((i + 1) / 2)) * angleInterval);
	}
}
