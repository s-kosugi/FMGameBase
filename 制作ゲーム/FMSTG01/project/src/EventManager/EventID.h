#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	EventID.h													*/
/*  @brief		:	イベントIDリスト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/09													*/
/*																				*/
/*==============================================================================*/

enum EventID
{
	EVENT_ID_ENM_WHITECORE,		// 0:白コアの敵出現
	EVENT_ID_ENM_SWIMMINGFLOAT,	// 1:ビート板の敵出現
	EVENT_ID_ENM_BLUECORE,		// 2:青コアの敵出現
	EVENT_ID_ENM_YELLOWCORE,	// 3:黄コアの敵出現
	EVENT_ID_ENM_REDCORE,		// 4:赤コアの出現
	EVENT_ID_ENM_GREENCORE,		// 5:緑コアの出現
	EVENT_ID_ENM_GREENCORE_RIGHT,// 6:右からの動き用緑コアの出現
	EVENT_ID_ENM_BOSSFIVETUBE,	// 7:ボス戦艦の出現

	EVENT_ID_WARNING,			 // 8:ワーニング表示
	EVENT_ID_WARNING_SOUND_LOOP, // 9:ワーニング音ループ
	EVENT_ID_WARNING_SOUND_STOP, // 10:ワーニング音ループストップ
	EVENT_ID_MAINMUSIC,			 // 11:メインBGM再生
	EVENT_ID_BGM_STOP,			 // 12:BGM停止

	EVENT_ID_MAX
};