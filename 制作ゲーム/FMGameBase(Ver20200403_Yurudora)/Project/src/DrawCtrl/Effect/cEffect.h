#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffect.h													*/
/*  @brief		:	�G�t�F�N�g�I�u�W�F�N�g�N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/14													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\IDrawBase.h"
#include "..\..\Utility\Vector\cVector3.h"
#include "SceneManager/SceneID.h"

//================================================================================================
// �G�t�F�N�g�I�u�W�F�N�g�N���X
class cEffect : public IDrawBase
{
	friend class cDrawCtrl;		// �`�摀��N���X�݂̂ɂ���ăn���h���̑�����s��
public:
	cEffect(const std::string& filename);
	~cEffect();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	// �G�t�F�N�g�̒�~
	void Stop( void );

	//---------------------------------------------------------------------------------------------
	// Getter
	inline cVector3 GetAngle(void) { return m_vAngle; };
	inline cVector3 GetScale(void) { return m_vScale; };

	inline int		GetPlayingHandle(void) { return m_nPlayingEffectHandle; };

	// �G�t�F�N�g���Đ��I���������ǂ���
	bool			IsEffectEnd(void);
	// ���[�v����G�t�F�N�g���ǂ���
	inline bool		IsLoop(void) { return m_bLoop; };

	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetAngle(cVector3 angle) { m_vAngle = angle; };
	inline void SetScale(cVector3 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = m_vScale.z = scale; };

	// �Đ��V�[���̃Z�b�g
	void SetPlayScene(SCENE_ID id);

protected:

	//---------------------------------------------------------------------------------------------
	// �G�t�F�N�g�\�����
	cVector3	m_vAngle;				// ��]�p�x
	cVector3	m_vScale;				// �g��k��
	bool		m_bLoop;				// ���[�v�t���O

private:
	int			m_nPlayingEffectHandle; // �Đ����G�t�F�N�g�n���h��

	bool		m_bStop;			// �Đ���~�t���O

	SCENE_ID	m_ePlayScene;		// �Đ��V�[�� -1 : �S�ẴV�[�� ����ȊO : �Y���V�[���ł̂ݍĐ�
};
//================================================================================================