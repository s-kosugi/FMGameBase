#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	BulletID.h													*/
/*  @brief		:	弾IDリスト													*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/27													*/
/*																				*/
/*==============================================================================*/

enum BulletType {
	BT_ANGLE = 0,	// 方向指定弾
	BT_HOMING_BULLET,// ホーミング弾
	BT_HOMING_LASER,// ホーミングレーザー
	BT_SNIPE_BULLET,// 狙い撃ち弾
	BT_HOMING_LASER_HEAD, // ホーミングレーザー(先頭のみ)
	BT_HOMING_LASER_TALE, // ホーミングレーザー(尾ひれ付)
	BT_BOSS_LASER,		  // ボスレーザー
	BT_MAX
};