#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	EnemyID.h													*/
/*  @brief		:	敵IDリスト													*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/09													*/
/*																				*/
/*==============================================================================*/

enum EnemyID{
	ENM_ID_WHITE_CORE = 0,			// 白コアの敵
	ENM_ID_SWIMMING_FLOAT,			// ビート板の敵
	ENM_ID_BLUE_CORE,				// 青コアの敵
	ENM_ID_YELLOW_CORE,				// 黄コアの敵
	ENM_ID_RED_CORE,				// 赤コアの敵
	ENM_ID_GREEN_CORE,				// 緑コアの敵
	ENM_ID_BOSS_FIVETUBE,			// ボス戦艦
	ENM_ID_BOSS_FIVETUBE_RIGHTBAT,	// ボス戦艦の右砲台
	ENM_ID_BOSS_FIVETUBE_LEFTBAT,	// ボス戦艦の左砲台
	ENM_ID_MAX
};