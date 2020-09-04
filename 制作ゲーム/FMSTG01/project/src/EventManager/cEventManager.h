#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEventManager.h												*/
/*  @brief		:	�C�x���g�Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/09													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"
#include <string>
#include <vector>

class cEventManager : public IBaseSingleton<cEventManager>
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �C�x���g�̊J�n
	void StartEvent(short no);

private:
	// �C�x���g�\����
	struct Event
	{
		unsigned int StartTime;		// �J�n����
		unsigned int EndTime;		// �I������
		int			 EvtNo;			// �C�x���g�ԍ�
		short		 Interval;		// �����Ԋu
		int			 PosX;			// �����ʒuX
		int			 PosY;			// �����ʒuY
	};

	// �C�x���g�t�@�C�����
	enum EventFileType
	{
		EVT_ENM = 0,		// �G
		EVT_PER,			// ���o
		EVT_MAX,
	};

	// �t�@�C��������
	std::string GenerateFilePath( short no , EventFileType type );

	// �C�x���g����
	void Create(std::vector<std::string>& readBuf);

	// �C�x���g���s
	void ExecEvent( Event& evt );

	// ���݂̃X�e�[�W�ԍ�
	short		 m_nStageNo;
	// �C�x���g�o�ߎ���
	unsigned int m_nEventTimer;
	// �C�x���g�\���̔z��
	std::vector<Event> m_ArEvent;


	// �萔
	const short  MAX_READ_STAGE = 99;		// �ő�X�e�[�W�Ǎ���
	const short	 MAX_EVENT_MENBER = 6;		// �C�x���g�\���̂̃����o�[��

	// �����_�����W�𔻒肷��l
	const int RANDOM_SENTINEL = 999999;
};