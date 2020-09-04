#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTargetEffect.h												*/
/*  @brief		:	�^�[�Q�b�g�G�t�F�N�g�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "..\cSpEffectObject.h"

//================================================================================================
// �^�[�Q�b�g�G�t�F�N�g�G�t�F�N�g�N���X
class cTargetEffect : public cSpEffectObject
{
public:
	cTargetEffect(IBaseObject* parent);
	~cTargetEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �ǔ��Ώۂ������Ă��邩�ǂ���
	bool IsSearchTargetAlive(void);

	// �ǔ��Ώۂ̏d���`�F�b�N
	static bool CheckDupulication(cSpriteObject* pObj);

	inline void SetTargetObject(cSpriteObject* pObj) { m_pTargetObj = pObj ;};

	inline cSpriteObject* GetTargetObject(void) { return m_pTargetObj; };
private:
	// �^�[�Q�b�g�X�v���C�g�̃A�j���[�V�������
	enum TARGET_ANM_STATE
	{
		TG_APPEAR,		// �o��
		TG_FLASH,		// �_��
		TG_NORMAL,		// �ʏ�
	};

	// �萔	
	// �\���D��x
	const int	PRIORITY = 500;

	// �F
	const unsigned int SPRITE_COLOR = 0xffff8888;
	// �^�[�Q�b�g�T�C�g��]�l
	const float ANGLE_ADD = 1.0f;
	// �������ԃf�t�H�l
	const unsigned int LIFE_TIME = 180;
	// �g�嗦�����l
	const float SCALE_RATE = 3.0f;
	// �G�t�F�N�g�����S�ɏo������܂ł̎���
	const unsigned int   APPEAR_TIME = 30;
	// �~�����̑傫���ő�l
	const float  CIRCLE_SCALE_MAX = 2.4f;
	// �~�����̃^�[�Q�b�g���b�N�I����Ԃ̐F
	const unsigned int CIRCLE_DICISION_COLOR = 0xff88ff88;

	// �_�ŊԊu
	const int	FLASH_INTERVAL = 9;
	// �_�ŏI������
	const unsigned int FLASH_TIME = 50;
	// �~�����̊g�k�Ԋu
	const int CIRCLE_SCALE_INTERVAL = 40;
	// �~�����̊g�k�͈�
	const float CIRCLE_SCALE_RANGE = 0.1f;
	
	// �A�j���[�V�������
	TARGET_ANM_STATE m_eAnimState;

	// �Ǐ]����I�u�W�F�N�g�̃|�C���^
	cSpriteObject* m_pTargetObj;

	// ��������
	unsigned int m_nLifeTime;

	// �T�[�N���X�v���C�g�̃|�C���^
	cSpriteObject* m_pCircleSprite;


	// ��ԕʏ���
	// �o��������
	void Appear( void );
	// �_�Ŏ�����
	void Flash( void );
	// �ʏ펩����
	void Normal( void );

};
//================================================================================================