#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	IBaseScene.h												*/
/*  @brief		:	�V�[�����N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/20													*/
/*																				*/
/*==============================================================================*/

#include "..\SceneID.h"
#include "BaseObject/IBaseObject.h"

//================================================================================================
// �V�[�����N���X

class IBaseScene : public IBaseObject
{
public:
	// �R���X�g���N�^
	IBaseScene(IBaseObject* parent, const std::string& name);

	// �f�X�g���N�^
	virtual ~IBaseScene(void);

	// �V�[���ύX �X�^�b�N����Ă���V�[���͑S�Ĕj��
	void    Change(SCENE_ID id);

	// �V�[���̃X�^�b�N
	void    Push(SCENE_ID id);

	// �X�^�b�N���ꂽ�V�[���̍폜
	void    Pop(void);

	// �V�[��ID�̐ݒ�
	void	SetSceneID(SCENE_ID id);

	// �V�[��ID�̎擾
	inline SCENE_ID GetSceneID(void) { return m_eSceneID; };

private:
	SCENE_ID m_eSceneID;				// �V�[��ID
};
