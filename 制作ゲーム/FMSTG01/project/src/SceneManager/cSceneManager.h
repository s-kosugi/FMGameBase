#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSceneManager.h												*/
/*  @brief		:	�V�[���Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"
#include "SceneID.h"
#include "..\DrawCtrl\Transition\cTransition.h"

//===============================================================================
// �V�[���Ǘ��N���X
class cSceneManager : public IBaseSingleton<cSceneManager>
{
public:
	void Initialize(void);
	void Update( void );
	IBaseObject* Finalize(void);

	// �V�[���ύX���o�^�C�v
	enum CHANGE_TYPE
	{
		CHANGE_NOFADE,			// �t�F�[�h����
		CHANGE_FADE,			// �t�F�[�h
		CHANGE_UNITRANS,		// ���j�o�[�T���g�����W�V����
	};
	
	// �V�[���ύX
	inline void ChangeScene(SCENE_ID id, CHANGE_TYPE type = CHANGE_FADE) { m_eNextScene = id; m_eChangeType = type; };
	inline SCENE_ID GetCurrentSceneID(void) {return m_eCurrentScene;};

	// ���݂̃V�[�������Z�b�g����
	void Reset(CHANGE_TYPE changeType = CHANGE_NOFADE);

private:

	// �V�[������
	void CreateScene(SCENE_ID id);

	// �t�F�[�h�A�E�g�O����
	void PrepareFadeOut(void);

	//------------------------------------------------------------------------------
	// �V�[����ԕʏ���
	void FadeIn(void);
	void UpdateScene(void);
	void FadeOut(void);
	void TransitionScene(void);
	//------------------------------------------------------------------------------

	enum STATE
	{
		STATE_FADEIN,		// �t�F�[�h�C��
		STATE_UPDATE,		// �V�[���X�V
		STATE_FADEOUT,		// �t�F�[�h�A�E�g
		STATE_TRANSITION,	// �V�[���J��
	};

	SCENE_ID m_eCurrentScene;		// �V�[��ID
	SCENE_ID m_eNextScene;			// ���V�[��ID
	STATE	 m_eState;				// �V�[�����
	CHANGE_TYPE m_eChangeType;		// �V�[���ύX���o�^�C�v
	cTransition* m_pTransObj;		// �g�����W�V�����N���X

	//------------------------------------------------------------------------------
	// �萔
	// �t�F�[�h�X�s�[�h
	static const int    FADE_SPEED = 5;

	//------------------------------------------------------------------------------

};