#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTextObject.h												*/
/*  @brief		:	�e�L�X�g�I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/08/23													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseObject.h"
#include "DrawCtrl\Text\cText.h"

//================================================================================================
// �e�L�X�g�I�u�W�F�N�g
// �P�N���X�ɂ��P�̃e�L�X�g�����������ꍇ�Ɏg�p����B
class cTextObject : public IBaseObject, public cText
{
public:
	cTextObject(IBaseObject* parent, const std::string& objectname, const std::string& text);
	cTextObject(IBaseObject* parent, const std::string& objectname, const std::string& text, const std::string& fontname, int fontsize, int Thick, int FontType, int EdgeSize, int Italic);
	~cTextObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

private:

};
//================================================================================================

//================================================================================================
// �I�u�W�F�N�g�����֐�
//================================================================================================
// �f�t�H���g�t�H���g�ŃI�u�W�F�N�g����
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g���ƕ\���e�L�X�g���w�肷��B
// return : ���������I�u�W�F�N�g
template <class T> T* CreateTextObject(IBaseObject* parent, const std::string& name, const std::string& text)
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T(parent, name, text);

	// �e������΃��X�g�ɒǉ�
	if (parent) parent->AddChild(t);

	// �I�u�W�F�N�g�̕ԋp
	return t;
}

// �w��t�H���g�I�u�W�F�N�g����
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g���ƕ\���e�L�X�g��CreateFontToHandle�ŕK�v�Ȉ������w�肷��B
// fontname�̓t�H���g�����w��
// fontsize Thick FontType EdgeSize��-1�Ńf�t�H���g
// Italic��0���f�t�H���g
// return : ���������I�u�W�F�N�g
template <class T> T* CreateTextObject(IBaseObject* parent, const std::string& name, const std::string& text, const std::string& fontname, int fontsize, int Thick, int FontType, int EdgeSize, int Italic)
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T(parent, name, text, fontname, fontsize, Thick, FontType, EdgeSize, Italic);

	// �e������΃��X�g�ɒǉ�
	if (parent) parent->AddChild(t);

	// �I�u�W�F�N�g�̕ԋp
	return t;
}