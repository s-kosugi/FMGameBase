#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	IBaseScene.h												*/
/*  @brief		:	シーン基底クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/20													*/
/*																				*/
/*==============================================================================*/

#include "..\SceneID.h"
#include "BaseObject/IBaseObject.h"

//================================================================================================
// シーン基底クラス

class IBaseScene : public IBaseObject
{
public:
	// コンストラクタ
	IBaseScene(IBaseObject* parent, const std::string& name);

	// デストラクタ
	virtual ~IBaseScene(void);

	// シーン変更 スタックされているシーンは全て破棄
	void    Change(SCENE_ID id);

	// シーンのスタック
	void    Push(SCENE_ID id);

	// スタックされたシーンの削除
	void    Pop(void);

	// シーンIDの設定
	void	SetSceneID(SCENE_ID id);

	// シーンIDの取得
	inline SCENE_ID GetSceneID(void) { return m_eSceneID; };

private:
	SCENE_ID m_eSceneID;				// シーンID
};
