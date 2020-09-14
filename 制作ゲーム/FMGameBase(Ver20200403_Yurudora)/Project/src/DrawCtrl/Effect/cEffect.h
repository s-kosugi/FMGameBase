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
#include "..\..\Utility\Vector\cVector3.h"
#include "SceneManager/SceneID.h"

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

	// エフェクトの停止
	void Stop( void );

	//---------------------------------------------------------------------------------------------
	// Getter
	inline cVector3 GetAngle(void) { return m_vAngle; };
	inline cVector3 GetScale(void) { return m_vScale; };

	inline int		GetPlayingHandle(void) { return m_nPlayingEffectHandle; };

	// エフェクトが再生終了したかどうか
	bool			IsEffectEnd(void);
	// ループするエフェクトかどうか
	inline bool		IsLoop(void) { return m_bLoop; };

	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetAngle(cVector3 angle) { m_vAngle = angle; };
	inline void SetScale(cVector3 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = m_vScale.z = scale; };

	// 再生シーンのセット
	void SetPlayScene(SCENE_ID id);

protected:

	//---------------------------------------------------------------------------------------------
	// エフェクト表示情報
	cVector3	m_vAngle;				// 回転角度
	cVector3	m_vScale;				// 拡大縮小
	bool		m_bLoop;				// ループフラグ

private:
	int			m_nPlayingEffectHandle; // 再生中エフェクトハンドル

	bool		m_bStop;			// 再生停止フラグ

	SCENE_ID	m_ePlayScene;		// 再生シーン -1 : 全てのシーン それ以外 : 該当シーンでのみ再生
};
//================================================================================================