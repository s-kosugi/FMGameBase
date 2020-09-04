#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cControllerManager.h										*/
/*  @brief		:	���͊Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"

class cControllerManager : public IBaseSingleton<cControllerManager>
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �L�[��`
	enum KEY_DEFINE
	{
		KEY_LEFT = 0,
		KEY_UP,
		KEY_RIGHT,
		KEY_DOWN,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_PAUSE,


		KEY_ANY,		// �S�ẴL�[

		KEY_MAX = KEY_ANY
	};

	// �L�[�����`�F�b�N(1P+�L�[�{�[�h�p)
	bool CheckButton(KEY_DEFINE kcode);
	bool CheckTriger(KEY_DEFINE kcode);
	bool CheckRelease(KEY_DEFINE kcode);
};