#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cControllerManager.h										*/
/*  @brief		:	���͊Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"

class cControllerManager : public IBaseObject
{
public:
	// ������
	void Initialize(void) override;

	// �X�V
	void Update(void) override;

	// �L�[��`
	enum class KEY_DEFINE
	{
		KEY_LEFT = 0,
		KEY_UP,
		KEY_RIGHT,
		KEY_DOWN,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_PAUSE,


		KEY_ANY,		// �S�ẴL�[

		KEY_MAX = KEY_ANY
	};

	// �L�[�����`�F�b�N(1P+�L�[�{�[�h�p)
	bool CheckButton(KEY_DEFINE kcode);
	bool CheckTrigger(KEY_DEFINE kcode);
	bool CheckRelease(KEY_DEFINE kcode);

	// �U���J�n
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	// Power : 0 �` 1000
	// Time : �U������
	void StartVibration(int InputType, int Power, int Time);

	// �U����~
	// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
	void StopVibration(int InputType);

	//-----------------------------------------------------------------------------------------------------
	// �V���O���g���p
private:
	cControllerManager(void) { };     //  ������̐������֎~
	cControllerManager(IBaseObject* parent) {  };
	cControllerManager(IBaseObject* parent, const std::string& name) { };
	~cControllerManager(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cControllerManager(const cControllerManager& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cControllerManager& operator = (const cControllerManager& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) override { IBaseObject::Finalize(); return nullptr; };

	static cControllerManager& GetInstance(void) {
		static cControllerManager instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};