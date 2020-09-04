#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	EventID.h													*/
/*  @brief		:	�C�x���gID���X�g											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/09													*/
/*																				*/
/*==============================================================================*/

enum EventID
{
	EVENT_ID_ENM_WHITECORE,		// 0:���R�A�̓G�o��
	EVENT_ID_ENM_SWIMMINGFLOAT,	// 1:�r�[�g�̓G�o��
	EVENT_ID_ENM_BLUECORE,		// 2:�R�A�̓G�o��
	EVENT_ID_ENM_YELLOWCORE,	// 3:���R�A�̓G�o��
	EVENT_ID_ENM_REDCORE,		// 4:�ԃR�A�̏o��
	EVENT_ID_ENM_GREENCORE,		// 5:�΃R�A�̏o��
	EVENT_ID_ENM_GREENCORE_RIGHT,// 6:�E����̓����p�΃R�A�̏o��
	EVENT_ID_ENM_BOSSFIVETUBE,	// 7:�{�X��͂̏o��

	EVENT_ID_WARNING,			 // 8:���[�j���O�\��
	EVENT_ID_WARNING_SOUND_LOOP, // 9:���[�j���O�����[�v
	EVENT_ID_WARNING_SOUND_STOP, // 10:���[�j���O�����[�v�X�g�b�v
	EVENT_ID_MAINMUSIC,			 // 11:���C��BGM�Đ�
	EVENT_ID_BGM_STOP,			 // 12:BGM��~

	EVENT_ID_MAX
};