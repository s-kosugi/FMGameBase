#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cText.h														*/
/*  @brief		:	�e�L�X�g�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/08/23													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\IDrawBase.h"

//================================================================================================
// �e�L�X�g�`��N���X
class cText : public IDrawBase
{
public:
	cText(const std::string& text);
	cText(const std::string& text,const std::string& fontname,int fontsize,int Thick,int FontType,int EdgeSize,int Italic);
	~cText();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// Getter
	inline std::string GetText(void) { return m_sText; };
	inline unsigned int GetEdgeColor(void) { return m_nEdgeColor; };
	inline int	GetVerticalFlag(void) { return m_nVerticalFlag; };		// �c�����ɕ`�悷�邩�̐ݒ� FALSE : ������ TRUE : �c����

	int GetWidth(void);		// ������̕����擾����B�w��̃t�H���g�f�[�^�ŕ`�悷�镶����̕�(�h�b�g�P��)�𓾂�

	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetText(std::string text) { m_sText = text; };					// ������̐ݒ� �f�t�H���g�t�H���g�ł͖���
	inline void SetEdgeColor(unsigned int color) { m_nEdgeColor = color; };		// ���̐F�̐ݒ� �f�t�H���g�t�H���g�ł͖���
	inline void SetVerticalFlag(int flag) { m_nVerticalFlag = flag; };			// �c�������ǂ����̐ݒ� FALSE : ������ TRUE : �c���� �f�t�H���g�t�H���g�ł͖���

protected:

	//---------------------------------------------------------------------------------------------
	// �e�L�X�g�\�����
	std::string		m_sText;		// �e�L�X�g���e

	unsigned int	m_nEdgeColor;	// �����̉��̐F
	int				m_nVerticalFlag;// �c�������ǂ��� FALSE : ������ TRUE : �c����
};
//================================================================================================