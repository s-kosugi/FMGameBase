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
	// �A�j���[�V�������
	struct Animation {
		POINT		StartPos;			// �p�[�c�̊J�n�_
		POINT		Size;				// 1�����̑傫��
		short		AnimMax;			// �A�j���[�V��������
		short		AnimTime;			// 1�A�j���[�V�������̎���

		short		AnimFrame;			// ���݂̃A�j���[�V�����t���[��(�����ڂ�)
		short		TimerCount;			// ���݂̃A�j���[�V�����^�C�}�[
	};
	
	//---------------------------------------------------------------------------------------------
	// �X�v���C�g�^�C�v
	enum SpriteType {
		SPTYPE_NORMAL = 0,		// �ʏ�̕`��
		SPTYPE_CIRCLEGAUGE,		// �~�`�Q�[�W
	};
	//---------------------------------------------------------------------------------------------
	// Getter
	POINT GetSpriteSize(void);
	inline RECT GetSrcRect(void) { return m_SrcRect; };
	inline cVector2 GetCenter(void) { return m_vCenter; };
	inline int GetBlendMode(void) { return m_BlendMode; };
	inline cVector2 GetScale(void) { return m_vScale; };
	inline float GetAngle(void) { return m_fAngle; };

	inline float GetStartAngle(void) { return m_fStartAngle; };
	inline float GetEndAngle(void) { return m_fEndAngle; };
	inline SpriteType GetSpriteType(void) { return m_eSpType; };


	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetSrcRect(RECT rect) { m_SrcRect = rect;};
	void SetSrcRect(int Startx, int Starty, int Sizex, int Sizey);
	inline void SetCenter(cVector2 vec) { m_vCenter = vec; };
	inline void SetCenter(float x, float y) {m_vCenter.x = x; m_vCenter.y = y;};
	inline void SetBlendMode(int mode) {m_BlendMode = mode;};
	inline void SetScale(cVector2 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = scale; };
	inline void SetAngle(float angle) { m_fAngle = angle; };

	inline void SetStartAngle(float angle) { m_fStartAngle = angle; };
	inline void SetEndAngle(float angle) { m_fEndAngle = angle; };
	inline void SetAnimation(Animation anim) { m_Animation = anim; };
	void SetAnimation( int Startx,int Starty,int width, int height,short AnimMax,short AnimTime );

protected:

	//---------------------------------------------------------------------------------------------
	// �X�v���C�g�\�����
	RECT		m_SrcRect;				// �`���`�̎n�_�ƏI�_
	cVector2	m_vCenter;				// ��]�Ɗg��̒��S�ʒu
	int			m_BlendMode;			// �`��u�����h���[�h
	cVector2	m_vScale;				// �g��k��
	float		m_fAngle;				// �X�v���C�g�̉�]�p�x

	float		m_fStartAngle;			// �~�O���t�̊J�n�p�x
	float		m_fEndAngle;			// �~�O���t�̏I���p�x
	
	Animation	m_Animation;			// �A�j���[�V�������\����
	SpriteType	m_eSpType;				// �X�v���C�g�^�C�v
};
//================================================================================================