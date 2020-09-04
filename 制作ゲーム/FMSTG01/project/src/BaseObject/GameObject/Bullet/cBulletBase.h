#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletBase.h												*/
/*  @brief		:	弾ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cHitObject.h"

//================================================================================================
// 弾ベースクラス
class cBulletBase : public cHitObject
{
public:
	cBulletBase(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~cBulletBase(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline void SetSpeed(float speed) { m_fSpeed = speed;};
	inline void SetPosUp(cVector2 vPos) { m_vPosUp = vPos; };

protected:
	// 弾が当たった時の処理
	void HitProc( void );

	// 移動後のスプライト回転処理
	void RotateMoveAfter(void);

	// 弾の移動速度
	float m_fSpeed;

	// 弾の移動ベクトル
	cVector2 m_vPosUp;
};
//================================================================================================