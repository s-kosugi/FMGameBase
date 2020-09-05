#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cModel.h													*/
/*  @brief		:	モデルオブジェクトクラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/05/22													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\IDrawBase.h"
#include "..\..\Utility\Vector\cVector3.h"

//================================================================================================
// モデルクラス
class cModel : public IDrawBase
{
	friend class cDrawCtrl;		// 描画操作クラスのみによってハンドルの操作を行う
public:
	cModel(const std::string& filename);
	~cModel();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// Getter
	inline cVector3 GetAngle(void) { return m_vAngle; };
	inline cVector3 GetScale(void) { return m_vScale; };
	
	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetAngle(cVector3 angle) { m_vAngle = angle; };
	inline void SetScale(cVector3 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = m_vScale.z = scale; };

protected:

	//---------------------------------------------------------------------------------------------
	// モデル表示情報
	cVector3	m_vAngle;				// 回転角度
	cVector3	m_vScale;				// 拡大縮小

private:

};
//================================================================================================