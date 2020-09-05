#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cModel.h													*/
/*  @brief		:	���f���I�u�W�F�N�g�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/05/22													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <iostream>
#include "..\IDrawBase.h"
#include "..\..\Utility\Vector\cVector3.h"

//================================================================================================
// ���f���N���X
class cModel : public IDrawBase
{
	friend class cDrawCtrl;		// �`�摀��N���X�݂̂ɂ���ăn���h���̑�����s��
public:
	cModel(const std::string& filename);
	~cModel();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// Getter
	inline cVector3 GetAngle(void) { return m_vAngle; };
	inline cVector3 GetScale(void) { return m_vScale; };
	
	//---------------------------------------------------------------------------------------------
	// Setter
	inline void SetAngle(cVector3 angle) { m_vAngle = angle; };
	inline void SetScale(cVector3 scale) { m_vScale = scale; };
	inline void SetScale(float scale) { m_vScale.x = m_vScale.y = m_vScale.z = scale; };

protected:

	//---------------------------------------------------------------------------------------------
	// ���f���\�����
	cVector3	m_vAngle;				// ��]�p�x
	cVector3	m_vScale;				// �g��k��

private:

};
//================================================================================================