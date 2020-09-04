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
#include "EffekseerForDXLib.h"
#include "..\..\Utility\Vector\cVector3.h"

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

	//---------------------------------------------------------------------------------------------
	// Getter
	inline cVector3 GetAngle(void) { return m_vAngle; };
	inline cVector3 GetScale(void) { return m_vScale; };

	// �G�t�F�N�g���Đ��I���������ǂ���
	inline bool		 IsEffectEnd(void) { return IsEffekseer2DEffectPlaying(m_nPlayingEffectHandle) == -1 && m_nPlayingEffectHandle != -1 ? true : false; };


	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetAngle(cVector3 angle) { m_vAngle = angle; };
	inline void SetScale(cVector3 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = m_vScale.z = scale; };

protected:

	//---------------------------------------------------------------------------------------------
	// �G�t�F�N�g�\�����
	cVector3	m_vAngle;				// ��]�p�x
	cVector3	m_vScale;				// �g��k��

private:
	int			m_nPlayingEffectHandle; // �Đ����G�t�F�N�g�n���h��

};
//================================================================================================