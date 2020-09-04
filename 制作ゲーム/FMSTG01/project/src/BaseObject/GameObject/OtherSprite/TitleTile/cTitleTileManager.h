#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleTileManager.h											*/
/*  @brief		:	�^�C�g���^�C���Ǘ�											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/28													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\IBaseObject.h"

//================================================================================================
// �^�C�g���^�C���Ǘ��N���X
class cTitleTileManager : public IBaseObject
{
public:
	cTitleTileManager(IBaseObject* parent);
	~cTitleTileManager(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �^�C���o���J�n
	inline void StartPop(void) { m_eState = STATE_TILE_POP; };

	// �^�C������J�n
	inline void StartCrumble(void) { m_eState = STATE_CRUMBLE; };

	// �^�C���̏o���������擾
	inline bool IsPopComp(void) { return m_bPopComp; };
private:

	enum TILE_STATE
	{
		STATE_WAIT = -1,
		STATE_TILE_POP = 0,
		STATE_CRUMBLE,
	};

	static const int TILE_SIZE = 64;
	static const int TILE_ADJUST = 32;		// �Q��ڈȍ~�̃^�C���␳�l
	static const int TILE_HEIGHT = 48;

	static const int TILE_POP_INTERVAL = 1;
	static const short TILE_SAME_POP = 2;
	static const int TILE_CRUMBLE_INTERVAL = 1;
	static const short TILE_SAME_CRUMBLE = 2;

	void Pop( void );
	void Crumble( void );

	
	int						m_nCounter;
	TILE_STATE				m_eState;
	bool					m_bPopComp;		// �^�C���o�������t���O
};
//================================================================================================