#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IDrawBase.h													*/
/*  @brief		:	�`��x�[�X�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/14													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\Utility\Vector\cVector2.h"


//===============================================================================
// �`����
enum DrawType
{
	DRAW_TYPE_SPRITE = 0,
	DRAW_TYPE_EFFECT,
	DRAW_TYPE_SURFACE,
	DRAW_TYPE_BEGINSURFACE,
	DRAW_TYPE_TRANSITION,
};

//================================================================================================
// �`��x�[�X�N���X
class IDrawBase
{
	friend class cDrawCtrl;		// �`�摀��N���X�݂̂ɂ���ăn���h���̑�����s��
public:
	IDrawBase();
	IDrawBase(const std::string& filename);
	virtual ~IDrawBase();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	inline bool IsFileLoaded(void) { if(m_nGraphHandle != LOADGRAPH_NONE) return true; return false;};
	//---------------------------------------------------------------------------------------------
	// Getter
	inline cVector2 GetPos(void) { return m_vPos; };
	inline int GetPriority(void) { return m_nPri; };
	inline bool GetVisible(void) { return m_bVisible; };
	inline unsigned int GetDrawColor(void) { return m_nColor; };
	inline unsigned int GetAlpha(void) { return m_nColor >> 24; };
	inline unsigned int GetColorRed(void) { return (m_nColor & 0x00ff0000) >> 16; };
	inline unsigned int GetColorGreen(void) { return (m_nColor & 0x0000ff00) >> 8; };
	inline unsigned int GetColorBlue(void) { return (m_nColor & 0x000000ff); };


	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetPos(cVector2 vPos) { m_vPos = vPos; };
	inline void SetPos(float x, float y) { m_vPos.x = x; m_vPos.y = y; };
	inline void SetPosX(float x) { m_vPos.x = x; };
	inline void SetPosY(float y) { m_vPos.y = y; };
	void SetPriority(int pri);
	inline void SetVisible(bool visible) { m_bVisible = visible; };
	inline void SetDrawColor(unsigned int color) { m_nColor = color; };
	inline void SetAlpha(unsigned int alpha) { m_nColor = (m_nColor & 0x00ffffff) | (alpha << 24); };
	inline void SetColorRed(unsigned int red) { m_nColor = (m_nColor & 0x00ff0000) | (red << 16); };
	inline void SetColorGreen(unsigned int green) { m_nColor = (m_nColor & 0x0000ff00) | (green << 8); };
	inline void SetColorBlue(unsigned int blue) { m_nColor = (m_nColor & 0x000000ff) | (blue); };

	//---------------------------------------------------------------------------------------------
	// �萔

	// �F�̒�`
	static const unsigned int COLOR_DEFAULT = 0xffffffff;
	static const unsigned int COLOR_RED = 0xffff0000;
	static const unsigned int COLOR_GREEN = 0xff00ff00;
	static const unsigned int COLOR_BLUE = 0xff0000ff;
	static const unsigned int COLOR_PURPLE = 0xffff00ff;
	static const unsigned int COLOR_YELLOW = 0xffffff00;
	static const unsigned int COLOR_BLACK = 0xff262626;

	// �����x�̒�`
	static const unsigned int ALPHA_MAX = 0xff;
protected:

	//---------------------------------------------------------------------------------------------
	// �X�v���C�g�\�����
	cVector2	m_vPos;					// �\���ʒu
	std::string m_sFileName;			// �t�@�C����
	unsigned int m_nColor;				// �F 0xARGB
	bool		m_bVisible;				// �\���L��
	bool		m_bUnload;				// �A�����[�h�t���O true : �I�u�W�F�N�g�폜���Ƀ���������A�����[�h����

private:
	int			m_nPri;					// �`��D��x
	int			m_nGraphHandle;			// �ǂݍ��ݍς݂̕`��̃n���h���B�����[�h�̏ꍇ��-1 cDrawCtrl�Őݒ肷��
	DrawType	m_eDrawType;			// �`����


	//---------------------------------------------------------------------------------------------
	// �萔
	static const int LOADGRAPH_NONE = -1;			// �`��t�@�C���̃��[�h���s�܂��͖����[�h
};
//================================================================================================