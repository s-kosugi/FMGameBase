#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.h													*/
/*  @brief		:	�Q�[�����C���V�[��											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\BaseObject\IBaseObject.h"

//================================================================================================
// �Q�[�����C���V�[��
class cGameMain : public IBaseObject
{
public:
	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// �����蔻�菈��
	void CheckHitProc( void );

	// ���@�ƓG�̓����蔻��(�T�u���[�`��)
	void CheckHitPlayer(void);

	// �G�Ǝ��@�̒e�̓����蔻��(�T�u���[�`��)
	void CheckHitEnemy( void );

};
//================================================================================================