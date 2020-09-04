#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingBullet.h												*/
/*  @brief		:	�z�[�~���O�e�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "..\cBulletBase.h"

//================================================================================================
// �z�[�~���O�e�N���X
class cHomingBullet : public cBulletBase
{
public:
	cHomingBullet(IBaseObject* parent);
	cHomingBullet(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cHomingBullet(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// ��]����p�x�̐ݒ�
	inline void SetRotLimit(float rot) { m_fRotLimit = rot; };

	// �펞�T�[�`�t���O�̐ݒ�
	inline void SetAlwaysSearch(bool flg) { m_bAlwaysSearch = flg;};

	// ��ԋ߂��^�[�Q�b�g�ɐݒ肷��
	inline void SetNearTarget(void) { m_pTargettingObj = SearchTargettingObject();};

	// �����_���ȃ^�[�Q�b�g�ɐݒ肷��
	cSpriteObject* SetRandomTarget( void );

	// ���ˊp�x�̐ݒ�
	void SetShootAngle(float angle);

protected:
	// �z�[�~���O�̈ړ��x�N�g�������߂�
	void CalcHomingMove(cVector2& hVec, const cVector2& trgPos);

	// �ǔ��Ώۂֈړ�����x�N�g�������߂�
	void CalcTargetVector(const cVector2& tPos, cVector2& tVec);

	// �������p�x�����������ړ��x�N�g�������߂�
	void CalcRotateLimit(cVector2& rVec, const cVector2& srcVec, const cVector2& trgVec, const cVector2& trgPos);

	// �ǔ��Ώۂ����肷��
	cSpriteObject* SearchTargettingObject( void );
	// �ǔ��Ώۂ̓G��T��
	cSpriteObject* SearchTargettingEnemy( void );
	// �ǔ��Ώۂ����݂��Ă��邩�ǂ���
	bool IsSearchTargetAlive( void );
	

	// �������p�x
	float m_fRotLimit;

	// �펞�T�[�`�t���O
	bool m_bAlwaysSearch;

	// �ǔ��Ώ�
	cSpriteObject* m_pTargettingObj;

	// �e�̐�������
	int	 m_nLifeTime;

private:
	//-------------------------------------------------------------------------------------------
	// �萔
	static const float HIT_RANGE;		// �����蔻��̑傫��
	static const int   PRIORITY;		// �\���D��x
	static const float ROT_LIMIT;		// �������p�x�����l
	static const int   LIFE_TIME;		// �e�̐������ԏ����l
	static const int   DEFAULT_ATK;		// �f�t�H���g�U����

};
//================================================================================================