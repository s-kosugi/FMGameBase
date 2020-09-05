#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.h													*/
/*  @brief		:	タイトルシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// タイトルシーン
class cTitle : public IBaseScene
{
public:
	cTitle(IBaseObject* parent);
	~cTitle(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	void AnimationPushZKey( void );	// PushZKeyのアニメーション処理
	void AnimationTitleLogo( void );// タイトルロゴのアニメーション処理
	void AnimationSurface( void );	// サーフェイスのアニメーション処理



	static const float	PUSH_Z_TIME;	// PushZKeyのアニメーション時間
	static const float	TITLELOGO_TIME;	// タイトルロゴのアニメーション時間
	static const float	SURFACE_TIME;	// サーフェイスのアニメーション時間
};
//================================================================================================