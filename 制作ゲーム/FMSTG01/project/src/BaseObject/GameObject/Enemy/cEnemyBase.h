#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyBase.h												*/
/*  @brief		:	敵ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\cHitObject.h"

//================================================================================================
// 敵ベースクラス
class cEnemyBase : public cHitObject
{
public:
	cEnemyBase(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~cEnemyBase(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

protected:
	cVector2   m_vPosUp;		// 移動値

	int		   m_nScore;		// 獲得スコア
};
//================================================================================================