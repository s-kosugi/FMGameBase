#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cMouse.h													*/
/*  @brief		:	�}�E�X���̓N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseSingleton.h"
#include <DxLib.h>

class cMouse : public IBaseSingleton<cMouse>
{
public :
	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �}�E�X�{�^�������`�F�b�N
	bool CheckButton(unsigned int kcode); // �����Ă��邩
	bool CheckTriger(unsigned int kcode); // �������u��
	bool CheckRelease(unsigned int kcode); // �������u��

	// �}�E�X���W�̐ݒ�
	void SetPoint( int x, int y);
	void SetPoint( POINT pt);

	// �}�E�X���W�̎擾
	POINT GetPoint( void );

	// MouseButton state
	int m_nButtonState;
	int m_nPrevButtonState;
};