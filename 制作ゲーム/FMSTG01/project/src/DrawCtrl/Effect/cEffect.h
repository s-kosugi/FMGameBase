#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffect.h													*/
/*  @brief		:	エフェクトオブジェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/14													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\IDrawBase.h"
#include "EffekseerForDXLib.h"
#include "..\..\Utility\Vector\cVector3.h"

//================================================================================================
// エフェクトオブジェクトクラス
class cEffect : public IDrawBase
{
	friend class cDrawCtrl;		// 描画操作クラスのみによってハンドルの操作を行う
public:
	cEffect(const std::string& filename);
	~cEffect();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// Getter
	inline cVector3 GetAngle(void) { return m_vAngle; };
	inline cVector3 GetScale(void) { return m_vScale; };

	// エフェクトが再生終了したかどうか
	inline bool		 IsEffectEnd(void) { return IsEffekseer2DEffectPlaying(m_nPlayingEffectHandle) == -1 && m_nPlayingEffectHandle != -1 ? true : false; };


	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetAngle(cVector3 angle) { m_vAngle = angle; };
	inline void SetScale(cVector3 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = m_vScale.z = scale; };

protected:

	//---------------------------------------------------------------------------------------------
	// エフェクト表示情報
	cVector3	m_vAngle;				// 回転角度
	cVector3	m_vScale;				// 拡大縮小

private:
	int			m_nPlayingEffectHandle; // 再生中エフェクトハンドル

};
//================================================================================================