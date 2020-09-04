#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSceneManager.h												*/
/*  @brief		:	�V�[���Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"
#include "SceneID.h"
#include "..\DrawCtrl\Transition\cTransition.h"
#include "Scene/IBaseScene.h"

//===============================================================================
// �V�[���Ǘ��N���X
class cSceneManager : public IBaseObject
{
public:
	void Initialize(void);
	void Update(void);

	// �V�[���ύX���o�^�C�v
	enum class CHANGE_TYPE
	{
		NOFADE,			// �t�F�[�h����
		FADE,			// �t�F�[�h
		UNITRANS,		// ���j�o�[�T���g�����W�V����
	};

	// �V�[���ύX
	void ChangeScene(SCENE_ID id, CHANGE_TYPE type = CHANGE_TYPE::FADE);
	// �V�[���ύX(���j�o�[�T���g�����W�V����)
	void ChangeSceneUniTrans(SCENE_ID id, std::string ruleFilename);


	// ���݃V�[���̎擾
	inline SCENE_ID GetCurrentSceneID(void) { return m_eCurrentScene; };
	// �X�^�b�N���Ă���V�[�����擾(�Ō��)
	SCENE_ID GetStackSceneID(void);

	// �t�F�[�h�A�E�g�^�C�v�̕ύX
	inline void SetFadeOutType(CHANGE_TYPE type) { m_eChangeOutType = type; };
	// �t�F�[�h�C���^�C�v�̕ύX
	inline void SetFadeInType(CHANGE_TYPE type) { m_eChangeInType = type; };
	// �t�F�[�h�A�E�g���Ԃ̕ύX
	inline void SetFadeOutTime(float time) { m_nFadeOutTime = time; };
	// �t�F�[�h�C�����Ԃ̕ύX
	inline void SetFadeInTime(float time) { m_nFadeInTime = time; };
	// �t�F�[�h�A�E�g�g�����W�V�����t�@�C���̕ύX
	inline void SetFadeOutTrans(std::string filename) { m_sTransOutFileName = filename; };
	// �t�F�[�h�C���g�����W�V�����t�@�C���̕ύX
	inline void SetFadeInTrans(std::string filename) { m_sTransInFileName = filename; };

	// �V�[���X�^�b�N�֘A
	void		PushScene(SCENE_ID id);
	void		PopScene(void);

	// ���݂̃V�[�������Z�b�g����
	void Reset(CHANGE_TYPE changeType = CHANGE_TYPE::NOFADE);

private:

	// �V�[������
	IBaseScene* CreateScene(SCENE_ID id);

	// �t�F�[�h�A�E�g�O����
	void PrepareFadeOut(void);

	//------------------------------------------------------------------------------
	// �V�[����ԕʏ���
	void FadeIn(void);
	void UpdateScene(void);
	void FadeOut(void);
	void TransitionScene(void);
	//------------------------------------------------------------------------------

	enum class STATE
	{
		FADEIN,		// �t�F�[�h�C��
		UPDATE,		// �V�[���X�V
		FADEOUT,	// �t�F�[�h�A�E�g
		TRANSITION,	// �V�[���J��
	};

	SCENE_ID		m_eCurrentScene;		// �V�[��ID
	SCENE_ID		m_eNextScene;			// ���V�[��ID
	STATE			m_eState;				// �V�[�����
	CHANGE_TYPE		m_eChangeOutType;		// �V�[���ύX(�t�F�[�h�A�E�g)���o�^�C�v
	CHANGE_TYPE		m_eChangeInType;		// �V�[���ύX(�t�F�[�h�C��)���o�^�C�v
	cTransition* m_pTransObj;			// �g�����W�V�����N���X
	std::string		m_sTransOutFileName;	// ���[���摜(�t�F�[�h�A�E�g)�t�@�C����
	std::string		m_sTransInFileName;		// ���[���摜(�t�F�[�h�A�E�g)�t�@�C����
	float			m_nFadeInTime;			// �t�F�[�h�C������
	float			m_nFadeOutTime;			// �t�F�[�h�A�E�g����
	SCENE_ID		m_ePushSceneID;			// �v�b�V������V�[��ID
	bool			m_bPush;				// �V�[���̃v�b�V�����s��ꂽ���ǂ���
	short			m_nStackCount;			// �V�[���X�^�b�N����Ă��鐔���J�E���g����

	//------------------------------------------------------------------------------
	// �萔
	// �����t�F�[�h�b��
	static const float    DEFAULT_FADE_TIME;

	//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cSceneManager(void);     //  ������̐������֎~
	cSceneManager(IBaseObject* parent);
	cSceneManager(IBaseObject* parent, const std::string& name);
	~cSceneManager(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cSceneManager(const cSceneManager& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cSceneManager& operator = (const cSceneManager& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cSceneManager& GetInstance(void) {
		static cSceneManager instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};