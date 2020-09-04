#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cResult.h													*/
/*  @brief		:	���U���g�V�[��												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/11													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// ���U���g�V�[��
class cResult : public IBaseScene
{
public:
	cResult(IBaseObject* parent);
	~cResult(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// ���U���g�V�[�����
	enum class RESULT_STATE
	{
		START,
		PAPER,		// ���o��
		SCORETEXT,	// �X�R�A�����o��
		HISCORETEXT,// �n�C�X�R�A�����o��
		NEWRECORD,  // �n�C�X�R�A�X�V
		WAIT,
	};

	// ��ԕʏ���
	// �J�n��
	void Start(void);
	// ���o��
	void Paper(void);
	// �X�R�A�����o��
	void ScoreText(void);
	// �n�C�X�R�A�����o��
	void HiScoreText(void);
	// �n�C�X�R�A�X�V
	void NewRecord(void);
	// ���͑҂����
	void Wait(void);


	// ���U���g�V�[�����
	RESULT_STATE m_eResultState;

	// �n�C�X�R�A
	int			 m_nHiScore;

	// �萔
	static const float		PAPER_START_POSX;
	static const float		PAPER_START_POSY;
};
//================================================================================================