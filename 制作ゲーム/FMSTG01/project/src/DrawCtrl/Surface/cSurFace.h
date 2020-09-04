#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSurface.h													*/
/*  @brief		:	�T�[�t�F�C�X�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/02/26													*/
/*																				*/
/*==============================================================================*/

#include "..\IDrawBase.h"
#include "..\..\Utility\Vector\cVector3.h"

//================================================================================================
// �T�[�t�F�C�X�N���X
// m_cBeginPoint�ɓo�^����Ă���Priority����cSurface��Priority�܂ł͈̔͂̕`��I�u�W�F�N�g���P�I�u�W�F�N�g�Ƃ��đ��삪�ł���
// ��ɉ�ʌ��ʂ⑽�l���v���C�ł̉�ʕ����Ɏg��

class cSurface : public IDrawBase
{
public:
	cSurface(void);
	~cSurface();

	void Create(int width, int height, int beginPriority, int endPriority, bool alpha = true);
	void Delete(void);

	// Getter
	inline cVector3		GetAngle(void) { return m_vAngle; };
	inline cVector2		GetCenter(void) { return m_vCenter; };
	inline RECT			GetRect(void) { return m_Rect; };
	inline int			GetBlendMode(void) { return m_nBlendMode; };
	inline cVector2		GetScale(void) { return m_vScale; };
	inline IDrawBase*	GetBeginPointer(void) { return &m_cBeginPoint; };

	// Setter
	inline void SetAngle(cVector3 angle) { m_vAngle = angle; };
	inline void SetCenter(float x, float y) { m_vCenter.x = x; m_vCenter.y = y; };
	inline void SetCenter(cVector2 center) { m_vCenter = center; };
	inline void SetRect(RECT rect) { m_Rect = rect; };
	inline void SetBlendMode(int mode) { m_nBlendMode = mode; };
	inline void SetScale(cVector2 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = scale; };
	inline void SetBeginPriority(int pri) { m_cBeginPoint.SetPriority(pri); };

private:
	cVector3  m_vAngle;			// ��]
	cVector2  m_vCenter;		// ���S�ʒu
	RECT	  m_Rect;			// �`���`�̎n�_�ƏI�_
	int		  m_nBlendMode;		// �`��u�����h���[�h
	cVector2  m_vScale;			// �g��k��

	IDrawBase m_cBeginPoint;	// �T�[�t�F�C�X�̕`��J�n�|�C���g�̐ݒ�(Priority�Ŏw��)
};