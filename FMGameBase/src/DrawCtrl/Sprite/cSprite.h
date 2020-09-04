#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSprite.h													*/
/*  @brief		:	�X�v���C�g�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\IDrawBase.h"

//================================================================================================
// �`��X�v���C�g�N���X
class cSprite : public IDrawBase
{
public:
    cSprite(const std::string& filename);
	~cSprite();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// Getter
	POINT				GetSpriteSize(void);
	inline RECT			GetSrcRect(void) { return m_SrcRect; };
	inline cVector2		GetCenter(void) { return m_vCenter; };
	inline cVector2		GetAnchor(void) { return m_vAnchor; };
	inline int			GetBlendMode(void) { return m_BlendMode; };
	inline cVector2		GetScale(void) { return m_vScale; };
	inline float		GetAngle(void) { return m_fAngle; };
    

	//---------------------------------------------------------------------------------------------
	// Setter
	void		SetSrcRect(RECT rect);
	void		SetSrcRect(int Startx, int Starty, int Sizex, int Sizey);
	inline void SetCenter(cVector2 vec) { m_vCenter = vec; };
	inline void SetCenter(float x, float y) {m_vCenter.x = x; m_vCenter.y = y;};
	inline void SetAnchor(cVector2 vec) { m_vAnchor = vec; };
	inline void SetAnchor(float x, float y) { m_vAnchor.x = x; m_vAnchor.y = y; };
	inline void SetBlendMode(int mode) {m_BlendMode = mode;};
	inline void SetScale(cVector2 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = scale; };
	inline void SetAngle(float angle) { m_fAngle = angle; };

protected:

	//---------------------------------------------------------------------------------------------
	// �X�v���C�g�\�����
	RECT		m_SrcRect;				// �`���`�̎n�_�ƏI�_
	cVector2	m_vCenter;				// �摜�̒��S�ʒu
	cVector2	m_vAnchor;				// ��]�Ɗg��̒��S�ʒu�AvCenter����̍�����vAnchor�ƂȂ�
	int			m_BlendMode;			// �`��u�����h���[�h
	cVector2	m_vScale;				// �g��k��
	float		m_fAngle;				// �X�v���C�g�̉�]�p�x

};
//================================================================================================