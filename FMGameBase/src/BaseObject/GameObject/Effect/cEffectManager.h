#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.h											*/
/*  @brief		:	�G�t�F�N�g�Ǘ��N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "EffectID.h"
#include "..\..\..\Utility\Vector\cVector2.h"

class cEffectObject;

class cEffectManager : public IBaseObject
{
public:

	// ������
	void Initialize(void) override;

	// �X�V
	void Update(void) override;

	// �j��
	IBaseObject* Finalize(void) override;

	// ����
	cEffectObject* Create(EFFECT_ID id,cVector2 pos);
	
	// �G�t�F�N�g�t�@�C���Ǎ�
	void LoadEffect( EFFECT_ID id );

	// �S�G�t�F�N�g�t�@�C���Ǎ�
	void LoadAllEffect( void );

	// �G�t�F�N�g�t�@�C�����̎擾
	inline std::string GetEffectFilename(EFFECT_ID id) { return EFFECT_FILE_NAME[(int)id]; };

private:
	
	// �G�t�F�N�g�t�@�C�����e�[�u��
	static const std::string EFFECT_FILE_NAME[(int)EFFECT_ID::MAX];

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cEffectManager(void) { };     //  ������̐������֎~
	cEffectManager(IBaseObject* parent) {  };
	cEffectManager(IBaseObject* parent, const std::string& name) { };
	~cEffectManager(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cEffectManager(const cEffectManager& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cEffectManager& operator = (const cEffectManager& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:

	static cEffectManager& GetInstance(void) {
		static cEffectManager instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
//-----------------------------------------------------------------------------------------------------
};