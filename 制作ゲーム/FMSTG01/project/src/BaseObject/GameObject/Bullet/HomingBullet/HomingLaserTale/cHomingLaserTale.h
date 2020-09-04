#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingLaserTale.h											*/
/*  @brief		:	�z�[�~���O���[�U�[(���Ђ�t)�N���X							*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/11													*/
/*																				*/
/*==============================================================================*/

#include "..\cHomingBullet.h"
#include <vector>

//================================================================================================
// �z�[�~���O���[�U�[(���Ђ�t)�N���X
class cHomingLaserTale : public cHomingBullet
{
public:
	cHomingLaserTale(IBaseObject* parent);
	cHomingLaserTale(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cHomingLaserTale(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// ���[�U�[�ړ�����
	struct History {
		cVector2 vPos;
		float	  fAngle;
	};

	// ���[�U�[�I�u�W�F�N�g�̏o������ݒ�
	inline void SetLaserNum(unsigned int num) { m_nLaserNum = num; };

	// �����[�U�[�̏o������
	inline void SetNextPopTime(unsigned int time) { m_nNextPopTime = time; };
private:
	// �ړ������̕ۑ�
	void SaveHistory( void );

	// ���[�U�[�̔��ړ�
	// return : �폜�������[�U�[������ꍇ��true
	bool MoveLaserTale(void);

	// ���[�U�[�̔�����
	void CreateLaserTale(void);

	// �ړ����W�ۑ��̈�
	std::vector<History> m_listHistory;
	// ���[�U�[�̔��������ԋL���̈�
	std::vector<unsigned int> m_listTaleCreateTime;

	// �����[�U�[�̏o������
	unsigned short m_nNextPopTime;

	// ���[�U�[�̐����^�C�}�[
	unsigned int m_nLaserLifeTime;

	// �z�[�~���O���[�U�[�̎c��
	unsigned int m_nLaserNum;

	//-------------------------------------------------------------------------------------------
	// �萔
	static const float HIT_RANGE;		// �����蔻��̑傫��
	static const int PRIORITY;			// �\���D��x
	static const int NEXT_LASER_TIME;	// �����[�U�[�̃|�b�v���ԏ����l
	static const int DEFAULT_ATK;		// �f�t�H���g�U����
};
//================================================================================================