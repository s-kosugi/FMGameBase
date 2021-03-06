#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletManager.h											*/
/*  @brief		:	eÇNX												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "BulletID.h"
#include "..\..\..\Utility\Vector\cVector2.h"

// ex[XNXÌOûé¾
class cBulletBase;

class cBulletManager : public IBaseSingleton<cBulletManager>
{
public:
	// ú»
	void Initialize(void);

	// XV
	void Update(void);

	// jü
	IBaseObject* Finalize(void);

	// e¶¬
	// type : eÌíÞ  startPos : eÌJnÊu  hitCategory : eÌ½è»èæª(HIT_PLAYER or HIT_ENEMY) speed : eÌÚ®¬x
	// ßèl : ¶¬µ½eÌ|C^
	cBulletBase* Create( BulletType type, const cVector2& startPos , int hitCategory,float speed, unsigned int color = 0x00ffffff, const std::string& filename = "none");

	// nWayeÌ¶¬
	// bulletNum : eÌ­Ë angleInterval : ­ËpxÔu startAngle : Jnpx color : eF
	void CreateNWayBullet(const cVector2& startPos, int hitCategory, float speed, const int bulletNum, float angleInterval, float startAngle, unsigned int color = 0x00ffffff, BulletType type = BT_ANGLE,const std::string& = "none");
	
private:

};