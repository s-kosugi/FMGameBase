#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingLaser.h												*/
/*  @brief		:	�z�[�~���O���[�U�[�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "..\cHomingBullet.h"
#include <vector>

//================================================================================================
// �z�[�~���O���[�U�[�N���X
class cHomingLaser : public cHomingBullet
{
public:
	cHomingLaser(IBaseObject* parent);
	cHomingLaser(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cHomingLaser(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// ���[�U�[�ړ�����
	struct VectorHistory {
		cVector2 vPos;
		cVector2 vPosUp;
	};

	// ���[�U�[�̈ړ��������擾
	inline VectorHistory GetVectorHistory(void) { return (VectorHistory)(*m_listVectorHistory.begin()); };

	// �O���[�U�[�̃|�C���^���Z�b�g
	inline void SetPrevLaserPointer(cHomingLaser* pObj) { m_pPrevLaser = pObj; };

	// ���[�U�[�I�u�W�F�N�g�̏o������ݒ�
	inline void SetLaserNum(unsigned int num) { m_nLaserNum = num ;};

	// �����[�U�[�̏o������
	inline void SetNextPopTime(unsigned int time) { m_nNextPopTime = time; };
private:

	// �O���[�U�[�������Ă��邩�ǂ����𒲂ׂ�
	bool IsSearchPrevLaserAlive(void);

	// �����[�U�[�̐���
	void CreateNextLaser( void );
	


	// 1�O�̃��[�U�[�ւ̃|�C���^
	cHomingLaser* m_pPrevLaser;
	// �ړ����W�ۑ��̈�
	std::vector<VectorHistory> m_listVectorHistory;

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