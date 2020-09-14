#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTimer.h													*/
/*  @brief		:	�^�C�}�[�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/01/14													*/
/*																				*/
/*==============================================================================*/
#include "BaseObject/IBaseObject.h"

//================================================================================================
// �^�C�}�[�N���X
class cTimer : public IBaseObject
{
public:
	cTimer( IBaseObject* parent, const std::string& name );
	~cTimer(void);

	// ������
	// limit : �v������(�b)
	void    Setup(float limit);
	// ������
	// limit : �v������(�b)
	// scale : �^�C���X�P�[��(1.0������)
	void    Setup(float limit, float scale);
	// �X�V
	void    Update(void) override;
	// ���Z�b�g
	inline void    Reset(void) override { m_fCurrentTime = 0.0f; };

	// �I������
	// ret : true �w�莞�Ԃ��o�߂��� false �w�莞�Ԃ��o�߂��Ă��Ȃ�
	inline bool    Finished(void)const { return (m_fCurrentTime >= m_fLimitTime); };

	// �I�����Ԃ̎擾
	inline float   GetTime(void) const		{ return m_fCurrentTime; };
	// �w�肵�����E���Ԃ̎擾
	inline float   GetLimit(void) const		{ return m_fLimitTime; };
	// �^�C���X�P�[�����擾
	inline float   GetTimeScale(void) const { return m_fTimeScale; };

	// ���E���Ԃ̐ݒ�
	void    SetLimit(float limit);
	// �^�C���X�P�[����ݒ�
	inline void    SetTimeScale(float scale) { m_fTimeScale = scale; };

private:
	static const float  DEFAULT_TIME_SCALE;		 // �����^�C���X�P�[��
	float               m_fCurrentTime;          // ���݂̎���
	float               m_fLimitTime;            // �ݒ莞��
	float               m_fTimeScale;            // �^�C���X�P�[��

};
//================================================================================================