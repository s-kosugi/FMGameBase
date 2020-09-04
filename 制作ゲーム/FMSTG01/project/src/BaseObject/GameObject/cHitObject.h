#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHitObject.h												*/
/*  @brief		:	�����蔻��I�u�W�F�N�g�N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\cSpriteObject.h"

//================================================================================================
// �����蔻��I�u�W�F�N�g�N���X
class cHitObject : public cSpriteObject
{
public:
	cHitObject(IBaseObject* parent,const std::string object_name,const std::string graphic_file_name);
	~cHitObject(void);
	
	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �����蔻��敪
	enum HitCategory {
		HIT_NONE = 0,
		HIT_PLAYER,
		HIT_ENEMY,
	};
	// �I�u�W�F�N�g�̏��
	enum State {
		STATE_NORMAL = 0,	// �ʏ���(�����蔻�肠��)
		STATE_FLASH,		// ���G�ł̓_�ŏ��(�����蔻��Ȃ��j
		STATE_HIT,			// �������Ă��Ė��G���(�����蔻��Ȃ�)
		STATE_DEAD			// ���S��(�����蔻��Ȃ�)
	};

	// �����蔻�菈��
	bool CheckHitObject( cHitObject& obj );

	inline void  SetHp(int Hp) { m_nHp = Hp; };
	inline void  GetMaxHp(int Hp) { m_nMaxHp = Hp; }
	inline void  SetAtk(int Atk) { m_nAtk = Atk; };
	inline void  SetHitRange(float Range) { m_fHitRange = Range; };
	inline void  SetHitCate(HitCategory cate) { m_eHitCate = cate; };
	inline void  SetState(State state) { m_eState = state; };
	inline void  SetAreaOutAdjust(int adjust) { m_nAreaOutAdjust = adjust; };

	inline int   GetHp(void) { return m_nHp; };
	inline int   GetMaxHp(void) { return m_nMaxHp; }
	inline int   GetAtk(void) { return m_nAtk; } ;
	inline float GetHitRange(void) { return m_fHitRange; };
	inline HitCategory GetHitCate(void) { return m_eHitCate; };
	inline State GetState(void) { return m_eState; };
	inline int	 GetAreaOutAdjust(void) { return m_nAreaOutAdjust; };

protected:
	// �G���A�A�E�g�����A��������ɃG���A�A�E�g�����ꍇ�ɃI�u�W�F�N�g�����������ꍇ�Ɏg�p���邱��
	// ���G���A�A�E�g���̏���
	void		 AreaOutLeftProc(void);
	// ��G���A�A�E�g���̏���
	void		 AreaOutUpProc(void);
	// �E�G���A�A�E�g���̏���
	void		 AreaOutRightProc(void);
	// ���G���A�A�E�g���̏���
	void		 AreaOutBottomProc(void);
	// �S�����G���A�A�E�g���̏���
	void		 AreaOutAllProc(void);

	// HP
	int			m_nHp;
	// �ő�HP
	int			m_nMaxHp;
	// �U����
	int			m_nAtk;
	// �����蔻��敪
	HitCategory m_eHitCate;
	// �����蔻��̑傫��(���a)
	float		m_fHitRange;
	// �I�u�W�F�N�g�̏��
	State		m_eState;
	// �G���A�A�E�g���e�l
	int			m_nAreaOutAdjust;

#ifdef DEBUG
	cSpriteObject* m_pDebugHitObj;
#endif
};
//================================================================================================