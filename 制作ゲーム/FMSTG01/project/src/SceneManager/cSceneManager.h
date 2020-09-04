#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSceneManager.h												*/
/*  @brief		:	シーン管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"
#include "SceneID.h"
#include "..\DrawCtrl\Transition\cTransition.h"

//===============================================================================
// シーン管理クラス
class cSceneManager : public IBaseSingleton<cSceneManager>
{
public:
	void Initialize(void);
	void Update( void );
	IBaseObject* Finalize(void);

	// シーン変更演出タイプ
	enum CHANGE_TYPE
	{
		CHANGE_NOFADE,			// フェード無し
		CHANGE_FADE,			// フェード
		CHANGE_UNITRANS,		// ユニバーサルトランジション
	};
	
	// シーン変更
	inline void ChangeScene(SCENE_ID id, CHANGE_TYPE type = CHANGE_FADE) { m_eNextScene = id; m_eChangeType = type; };
	inline SCENE_ID GetCurrentSceneID(void) {return m_eCurrentScene;};

	// 現在のシーンをリセットする
	void Reset(CHANGE_TYPE changeType = CHANGE_NOFADE);

private:

	// シーン生成
	void CreateScene(SCENE_ID id);

	// フェードアウト前準備
	void PrepareFadeOut(void);

	//------------------------------------------------------------------------------
	// シーン状態別処理
	void FadeIn(void);
	void UpdateScene(void);
	void FadeOut(void);
	void TransitionScene(void);
	//------------------------------------------------------------------------------

	enum STATE
	{
		STATE_FADEIN,		// フェードイン
		STATE_UPDATE,		// シーン更新
		STATE_FADEOUT,		// フェードアウト
		STATE_TRANSITION,	// シーン遷移
	};

	SCENE_ID m_eCurrentScene;		// シーンID
	SCENE_ID m_eNextScene;			// 次シーンID
	STATE	 m_eState;				// シーン状態
	CHANGE_TYPE m_eChangeType;		// シーン変更演出タイプ
	cTransition* m_pTransObj;		// トランジションクラス

	//------------------------------------------------------------------------------
	// 定数
	// フェードスピード
	static const int    FADE_SPEED = 5;

	//------------------------------------------------------------------------------

};