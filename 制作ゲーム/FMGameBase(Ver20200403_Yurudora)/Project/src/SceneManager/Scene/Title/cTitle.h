#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.h													*/
/*  @brief		:	�^�C�g���V�[��												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// �^�C�g���V�[��
class cTitle : public IBaseScene
{
public:
	cTitle(IBaseObject* parent);
	~cTitle(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	void AnimationPushZKey( void );	// PushZKey�̃A�j���[�V��������
	void AnimationTitleLogo( void );// �^�C�g�����S�̃A�j���[�V��������
	void AnimationSurface( void );	// �T�[�t�F�C�X�̃A�j���[�V��������



	static const float	PUSH_Z_TIME;	// PushZKey�̃A�j���[�V��������
	static const float	TITLELOGO_TIME;	// �^�C�g�����S�̃A�j���[�V��������
	static const float	SURFACE_TIME;	// �T�[�t�F�C�X�̃A�j���[�V��������
};
//================================================================================================