#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	BulletID.h													*/
/*  @brief		:	�eID���X�g													*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/27													*/
/*																				*/
/*==============================================================================*/

enum BulletType {
	BT_ANGLE = 0,	// �����w��e
	BT_HOMING_BULLET,// �z�[�~���O�e
	BT_HOMING_LASER,// �z�[�~���O���[�U�[
	BT_SNIPE_BULLET,// �_�������e
	BT_HOMING_LASER_HEAD, // �z�[�~���O���[�U�[(�擪�̂�)
	BT_HOMING_LASER_TALE, // �z�[�~���O���[�U�[(���Ђ�t)
	BT_BOSS_LASER,		  // �{�X���[�U�[
	BT_MAX
};