#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	SoundID.h													*/
/*  @brief		:	サウンドIDリスト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/27													*/
/*																				*/
/*==============================================================================*/

enum SoundID 
{
	SOUND_BOM,			// 爆発音
	SOUND_PI,			// ピッ
	SOUND_LOCK,			// ロックオン(ピピッ(連続))
	SOUND_LASER,		// レーザー用(シュワー)
	SOUND_SHOT,			// ショット(シャッ)
	SOUND_BOSSCHARGE,	// ボスチャージ
	SOUND_BOSSBEAM,		// ボス大型ビーム
	SOUND_BIGBOM,		// 大爆発
	SOUND_PIRO,			// ピロッ
	SOUND_DIGI,			// スコアボーナス決定
	SOUND_KACHI,		// カチッ
	SOUND_WARNING,		// ワーニング
	SOUND_SHOOT,		// ボスエリアアウトショット用

	SOUND_TITLE,		// タイトルBGM
	SOUND_STAGE1,		// ステージ1用BGM
	SOUND_BOSS,			// ボスBGM

	SOUND_MAX
};