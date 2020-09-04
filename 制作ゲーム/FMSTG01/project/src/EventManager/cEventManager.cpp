/*==============================================================================*/
/*																				*/
/*	@file title	:	cEventManager.cpp											*/
/*  @brief		:	�C�x���g�Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/09													*/
/*																				*/
/*==============================================================================*/

#include "cEventManager.h"
#include "..\CsvReader\cCsvReader.h"
#include "..\BaseObject\GameObject\Enemy\cEnemyManager.h"
#include "..\BaseObject\GameObject\Enemy\GreenCore\cEnmGreenCore.h"
#include "..\BaseObject\GameObject\SpEffect\cSpEffectManager.h"
#include "..\SoundCtrl\cSoundCtrl.h"
#include "EventID.h"

//==========================================================================================
// ������
//==========================================================================================
void cEventManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "EventManager";

	m_nEventTimer = 0;

	IBaseObject::Initialize();
}
//==========================================================================================
// �X�V
//==========================================================================================
void cEventManager::Update(void)
{
	if(m_ArEvent.size() == 0) return;

	for (unsigned int i = 0; i < m_ArEvent.size();i++)
	{
		// ���s���ԓ���
		if (m_ArEvent[i].StartTime <= m_nEventTimer && m_ArEvent[i].EndTime >= m_nEventTimer)
		{
			// ���s�Ԋu���ɃC�x���g����
			if ( (m_nEventTimer - m_ArEvent[i].StartTime) % m_ArEvent[i].Interval == 0)
			{
				ExecEvent( m_ArEvent[i]);
			}
		}
	}

	m_nEventTimer++;

}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cEventManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// �C�x���g�J�n
// no : �X�e�[�W�ԍ����Z�b�g
//==========================================================================================
void cEventManager::StartEvent(short no)
{
	if( no < 0 || no > MAX_READ_STAGE || no == m_nStageNo) return;

	m_nStageNo = no;
	m_nEventTimer = 0;

	// �C�x���g�z���������
	m_ArEvent.clear();

	// �C�x���g�t�@�C����ǂݍ���
	cCsvReader& cr = cCsvReader::GetInstance();

	for (int i = 0; i < EVT_MAX; i++)
	{
		// �C�x���g�t�@�C�����̍쐬
		std::string filepath = GenerateFilePath(no,(EventFileType)i);

		std::vector<std::string> buf;
		// �C�x���g�t�@�C���̓Ǎ�
		cr.LoadFile(filepath,buf);

		// �C�x���g����
		this->Create(buf);
	}
}

//==========================================================================================
// �t�@�C��������
// no : �X�e�[�W�ԍ�
// type : �C�x���g�t�@�C�����
// return : ���������t�@�C����
//==========================================================================================
std::string cEventManager::GenerateFilePath(short no, EventFileType type)
{
	// �t�@�C�������쐬
	std::string filepath;

	filepath = "data\\event\\";
	// �A�Ԃ̂Q���ڂ��쐬
	if (no <= 10) filepath += "0";
	else filepath += ((short)(no / 10) + '0');

	// �A�Ԃ̂P���ڂ��쐬
	filepath += (no % 10) + '0';

	switch (type)
	{
	case EVT_ENM:
		filepath += "_enemy.evt";
		break;
	case EVT_PER:
		filepath += "_per.evt";
		break;
	}

	return filepath;
}

//==========================================================================================
// �C�x���g����
// readBuf : CSV�t�@�C������ǂݍ��񂾕�����f�[�^
//==========================================================================================
void cEventManager::Create(std::vector<std::string>& readBuf)
{
	if (readBuf.size() == 0) return;

	Event evt;
	for (unsigned int i = 0; i < readBuf.size(); i++)
	{
		// �e�\���̂̃����o�[�Ƀo�b�t�@�̃f�[�^������
		switch (i%MAX_EVENT_MENBER)
		{
		case 0:
			evt.StartTime = std::stoi(readBuf[i]);
			break;
		case 1:
			evt.EndTime = std::stoi(readBuf[i]);
			break;
		case 2:
			evt.EvtNo = std::stoi(readBuf[i]);
			break;
		case 3:
			evt.Interval = std::stoi(readBuf[i]);
			break;
		case 4:
			evt.PosX = std::stoi(readBuf[i]);
			break;
		case 5:
			evt.PosY = std::stoi(readBuf[i]);
			break;
		}

		// �Ō�̃����o�[�̑�����I�������z��֒ǉ�
		if (i % MAX_EVENT_MENBER == MAX_EVENT_MENBER - 1)
		{
			m_ArEvent.push_back(evt);
		}
	}
	return;
}

//==========================================================================================
// �C�x���g���s
// no : �C�x���g�ԍ�
//==========================================================================================
void cEventManager::ExecEvent(Event& evt)
{
	if( evt.EvtNo < 0  || evt.EvtNo >= EVENT_ID_MAX) return;

	cEnemyManager& em = cEnemyManager::GetInstance();
	cSpEffectManager& spef = cSpEffectManager::GetInstance();
	cSpriteObject* pObj = nullptr;

	switch (evt.EvtNo)
	{
		case EVENT_ID_ENM_WHITECORE:
			pObj = em.Create(EnemyID::ENM_ID_WHITE_CORE);
			break;
		case EVENT_ID_ENM_SWIMMINGFLOAT:
			pObj = em.Create(EnemyID::ENM_ID_SWIMMING_FLOAT);
			break;
		case EVENT_ID_ENM_BLUECORE:
			pObj = em.Create(EnemyID::ENM_ID_BLUE_CORE);
			break;
		case EVENT_ID_ENM_YELLOWCORE:
			pObj = em.Create(EnemyID::ENM_ID_YELLOW_CORE);
			break;
		case EVENT_ID_ENM_REDCORE:
			pObj = em.Create(EnemyID::ENM_ID_RED_CORE);
			break;
		case EVENT_ID_ENM_GREENCORE:
			pObj = em.Create(EnemyID::ENM_ID_GREEN_CORE);
			break;
		case EVENT_ID_ENM_GREENCORE_RIGHT:
			pObj = em.Create(EnemyID::ENM_ID_GREEN_CORE);
			((cEnmGreenCore*)pObj)->SetAiNo(1);
			break;
		case EVENT_ID_ENM_BOSSFIVETUBE:
			pObj = em.Create(EnemyID::ENM_ID_BOSS_FIVETUBE);
			cSoundCtrl::GetInstance().BGMPlay(SOUND_BOSS);
			break;
		case EVENT_ID_WARNING:
			pObj = spef.Create(SpEffectID::SPEFFECT_WARNING, cVector2(0.0f,0.0f));
			break;
		case EVENT_ID_WARNING_SOUND_LOOP:
			cSoundCtrl::GetInstance().Play(SOUND_WARNING,true);
			break;
		case EVENT_ID_WARNING_SOUND_STOP:
			cSoundCtrl::GetInstance().Stop(SOUND_WARNING);
			break;
		case EVENT_ID_MAINMUSIC:
			cSoundCtrl::GetInstance().BGMPlay(SOUND_STAGE1);
			break;
		case EVENT_ID_BGM_STOP:
			cSoundCtrl::GetInstance().BGMStop();
			break;
	}
	if( pObj == nullptr ) return;

	// ���W�̔z�u
	if(evt.PosX == RANDOM_SENTINEL ) pObj->SetRandomPosX();
	else pObj->SetPosX((float)evt.PosX);
	if(evt.PosY == RANDOM_SENTINEL) pObj->SetRandomPosY();
	else pObj->SetPosY((float)evt.PosY);

}
