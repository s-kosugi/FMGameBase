/*==============================================================================*/
/*																				*/
/*	@file title	:	cSoundCtrl.cpp												*/
/*  @brief		:	�T�E���h����N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/30													*/
/*																				*/
/*==============================================================================*/

#include "cSoundCtrl.h"
#include <DxLib.h>

//==========================================================================================
// ������
//==========================================================================================
void cSoundCtrl::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "SoundCtrl";

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cSoundCtrl::Update(void)
{
	switch (m_eBgmState)
	{
	case BGMSTATE::NORMAL:
		break;
	case BGMSTATE::FADEOUT:
		UpdateFadeOut();
		break;
	case BGMSTATE::FADEIN:
		UpdateFadeIn();
		break;
	case BGMSTATE::CROSSFADE:
		UpdateCrossFade();
		break;
	}
	
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cSoundCtrl::Finalize(void)
{
	IBaseObject::Finalize();

	//------------------------------------------------------------------------------------
	// �ǂݍ��ݍς݃T�E���h�̉��
	if (!m_listSdLoaded.empty())
	{
		InitSoundMem();
		m_listSdLoaded.clear();
	}
	return nullptr;
}
//==========================================================================================
//	�T�E���h�̓ǂݍ���
//  �߂�l : �ǂݍ��ݍς݂̃T�E���h�n���h��
//==========================================================================================
int cSoundCtrl::Load(SOUND_ID id,int bufnum)
{
	return Load(SOUNDNAME_TABLE[(int)id]);;
}

//==========================================================================================
//	�T�E���h�̓ǂݍ���
//  �߂�l : �ǂݍ��ݍς݂̃T�E���h�n���h��
//==========================================================================================
int cSoundCtrl::Load(const std::string & filename,int bufnum)
{
	int handle = SearchSoundHandle(filename);
	if( handle != LOADSOUND_FAILED ) return handle;

	// �V�K�ǂݍ��݉��������X�g�ɒǉ�����
	SdLoaded load;
	load.FileName = filename;
	load.SoundHandle = LoadSoundMem(filename.c_str(), bufnum);

	// �T�E���h�n���h���ǂݍ��ݎ��s
	if (LOADSOUND_FAILED == load.SoundHandle)
		return LOADSOUND_FAILED;

	// �ǂݍ��ݍς݃��X�g�ɒǉ�
	m_listSdLoaded.push_back(load);
	return load.SoundHandle;
}
//==========================================================================================
//	�S�T�E���h�̓ǂݍ���
//==========================================================================================
void cSoundCtrl::LoadAll(void)
{
	for (int i = 0; i < (int)SOUND_ID::MAX; i++)
	{
		Load(SOUNDNAME_TABLE[i]);
	}
}
//==========================================================================================
//	�T�E���h�̍폜
//==========================================================================================
void cSoundCtrl::Delete(SOUND_ID id)
{
	Delete(SOUNDNAME_TABLE[(int)id]);
}

//==========================================================================================
//	�T�E���h�̍폜
//==========================================================================================
void cSoundCtrl::Delete(const std::string & filename)
{
	if (!m_listSdLoaded.empty()) {
		//---------------------------------------------------------------------
		std::list<SdLoaded>::iterator it = m_listSdLoaded.begin();
		std::list<SdLoaded>::iterator end = m_listSdLoaded.end();

		while (it != end)
		{
			if (it->FileName.compare(filename))
			{
				// ����������폜
				DeleteSoundMem(it->SoundHandle);

				// ���X�g����폜
				m_listSdLoaded.erase(it);
				return;
			}

			it++;
		}
	}
}
//==========================================================================================
//	�T�E���h�̍Đ�
//  return : �Đ����̉����̃n���h��
//==========================================================================================
int cSoundCtrl::Play(SOUND_ID id, bool loop)
{
	return Play(SOUNDNAME_TABLE[(int)id], loop);
}
//==========================================================================================
//	�T�E���h�̍Đ�
//  return : �Đ����̉����̃n���h��
//==========================================================================================
int cSoundCtrl::Play(const std::string & filename, bool loop)
{
	int handle = SearchSoundHandle(filename);
	if (handle == LOADSOUND_FAILED)
	{
		// ���ǂݍ��݂̃T�E���h��������ǂݍ���
		handle = Load(filename);
	}
	// �}�X�^�[�{�����[����ݒ肷��
	ChangeVolumeSoundMem(m_nMasterVolume, handle);

	// �Đ��^�C�v�̐ݒ�
	int PlayType;
	if( loop ) PlayType = DX_PLAYTYPE_LOOP;
	else PlayType = DX_PLAYTYPE_BACK;

	// �T�E���h�̍Đ�
	PlaySoundMem(handle,PlayType,TRUE);

	return handle;
}
//==========================================================================================
//	BGM�̍Đ�
//  return : �Đ����̉����̃n���h��
//==========================================================================================
int cSoundCtrl::BGMPlay(SOUND_ID id, BGMCHANNEL ch)
{
	int handle = BGMPlay(SOUNDNAME_TABLE[(int)id], ch);
	return handle;
}
//==========================================================================================
//	BGM�̍Đ�
//  return : �Đ����̉����̃n���h��
//==========================================================================================
int cSoundCtrl::BGMPlay(const std::string & filename, BGMCHANNEL ch)
{
	int chHandle = SearchSoundHandle(filename);

	// �Đ�����BGM���ݒ肳�ꂽ�ꍇ�ɂ͏����������ɉ����n���h����Ԃ�
	if (chHandle != -1 && CheckSoundMem(chHandle) == 1 && m_sPlayBgmName[(int)ch] == filename )
		return chHandle;
	
	int handle = Play(filename,true);
	if (handle != LOADSOUND_FAILED)
	{
		BGMStop(ch);
		m_sPlayBgmName[(int)ch] = filename;
	}
	return handle;
}
//==========================================================================================
//	�T�E���h�̒�~
//==========================================================================================
void cSoundCtrl::Stop(SOUND_ID id)
{
	Stop(SOUNDNAME_TABLE[(int)id]);
}
//==========================================================================================
//	�T�E���h�̒�~
//==========================================================================================
void cSoundCtrl::Stop(const std::string & filename)
{
	int handle = SearchSoundHandle(filename);
	if (handle != LOADSOUND_FAILED)
	{
		StopSoundMem(handle);
	}
}
//==========================================================================================
//	BGM�̒�~
//==========================================================================================
void cSoundCtrl::BGMStop(BGMCHANNEL ch)
{
	Stop(m_sPlayBgmName[(int)ch]);
}
//==========================================================================================
//	�}�X�^�[�{�����[���̕ύX
//  int vol : 0�`255  0�͖��� 255�͍ő剹��
//==========================================================================================
void cSoundCtrl::ChangeMasterVolume(int vol)
{
	m_nMasterVolume =  vol;

	// ���ݖ��Ă��鉹���ύX����
	for (int i = 0; i < (int)SOUND_ID::MAX; i++)
	{
		ChangeVolumeSoundMem(m_nMasterVolume, SearchSoundHandle(SOUNDNAME_TABLE[i]));
	}
}
//==========================================================================================
//	�{�����[���̕ύX
//  int vol : 0�`255  0�͖��� 255�͍ő剹��
//==========================================================================================
void cSoundCtrl::ChangeVolume(SOUND_ID id, int vol)
{
	ChangeVolume(SOUNDNAME_TABLE[(int)id],vol);
}
//==========================================================================================
//	�{�����[���̕ύX
//  int vol : 0�`255  0�͖��� 255�͍ő剹��
//==========================================================================================
void cSoundCtrl::ChangeVolume(const std::string & filename, int vol)
{
	int handle = SearchSoundHandle(filename);

	if( LOADSOUND_FAILED ==  handle ) return;

	ChangeVolumeSoundMem(vol,handle);
}
//==========================================================================================
//	BGM�̃t�F�[�h�A�E�g�̐ݒ�
//  int frame : �t�F�[�h�A�E�g����
//==========================================================================================
void cSoundCtrl::FadeOutBgm(unsigned int frame)
{
	int handle = SearchSoundHandle(m_sPlayBgmName[(int)BGMCHANNEL::MAIN]);

	if( handle == LOADSOUND_FAILED) return;

	int volume = GetVolumeSoundMem(handle);

	m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN] = (int)(((float)volume / frame) + 0.5f);
	m_eBgmState = BGMSTATE::FADEOUT;
}
//==========================================================================================
//	BGM�̃t�F�[�h�C���̐ݒ�
//  int frame : �t�F�[�h�C������
//  ����BGMID���t�F�[�h�C��������ꍇ�͑O�t���[���Œ�~���Ă���K�v������(DXLib�̍Đ��̎d�l)
//==========================================================================================
void cSoundCtrl::FadeInBgm(unsigned int frame, SOUND_ID id, BGMCHANNEL ch)
{
	int handle = BGMPlay(id,ch);

	if (handle == LOADSOUND_FAILED) return;

	// �}�X�^�[�{�����[����100����1�f�V�x���P�ʂŎ擾
	ChangeVolumeSoundMem(m_nMasterVolume, handle);
	int volume = GetVolumeSoundMem(handle);

	ChangeVolume(id, 0);

	m_nBgmVolumeFade[(int)ch] = (int)(((float)volume / frame) + 0.5f);
	m_eBgmState = BGMSTATE::FADEIN;
}
//==========================================================================================
//	BGM�̃t�F�[�h�C���̐ݒ�
//  int outframe : �t�F�[�h�C������
//  int inframe : �t�F�[�h�A�E�g����
//  SoundID id : �t�F�[�h�C��������SoundID
//==========================================================================================
void cSoundCtrl::CrossFadeBgm(unsigned int outframe, unsigned int inframe, SOUND_ID id)
{
	FadeOutBgm(outframe);
	FadeInBgm(inframe, id, BGMCHANNEL::SWAP);
	m_eBgmState = BGMSTATE::CROSSFADE;
}
//==========================================================================================
// ���g���̐ݒ�
//==========================================================================================
void cSoundCtrl::SetFrequency(SOUND_ID id, int value)
{
	SetFrequencySoundMem(value, SearchSoundHandle(SOUNDNAME_TABLE[(int)id]));
}
//==========================================================================================
// ���g���̐ݒ�
//==========================================================================================
void cSoundCtrl::SetFrequency(const std::string & filename, int value)
{
	SetFrequencySoundMem(value, SearchSoundHandle(filename));
}
//==========================================================================================
// ���g���̎擾
//==========================================================================================
int cSoundCtrl::GetFrequency(SOUND_ID id)
{
	return GetFrequencySoundMem(SearchSoundHandle(SOUNDNAME_TABLE[(int)id]));
}
//==========================================================================================
// ���g���̎擾
//==========================================================================================
int cSoundCtrl::GetFrequency(const std::string & filename)
{
	return GetFrequencySoundMem(SearchSoundHandle(filename));
}
//==========================================================================================
// �T�E���h�n���h���̌���
// �߂�l:�T�E���h�n���h��  LOADSOUND_FAILED:���s
//==========================================================================================
int cSoundCtrl::SearchSoundHandle(const std::string & filename)
{
	if (!m_listSdLoaded.empty())
	{
		//---------------------------------------------------------------------
		std::list<SdLoaded>::iterator it = m_listSdLoaded.begin();
		std::list<SdLoaded>::iterator end = m_listSdLoaded.end();

		while (it != end)
		{
			SdLoaded load = ((SdLoaded)(*it));
			if (load.FileName == filename)
			{
				return load.SoundHandle;
			}

			it++;
		}
	}
	return LOADSOUND_FAILED;
}
//==========================================================================================
// �t�F�[�h�A�E�g�̍X�V����
//==========================================================================================
void cSoundCtrl::UpdateFadeOut(void)
{
	if (m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[(int)BGMCHANNEL::MAIN]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume -= m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN];
			if (volume <= 0)
			{
				volume = 0;
				m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN] = 0;
				m_eBgmState = BGMSTATE::NORMAL;
				BGMStop(BGMCHANNEL::MAIN);
				// ���炵���{�����[����߂��Ă���
				ChangeVolumeSoundMem(m_nMasterVolume,handle);
				return;
			}
			SetVolumeSoundMem(volume, handle);
		}
	}
	else
	{
		m_eBgmState = BGMSTATE::NORMAL;
	}
}
//==========================================================================================
// �t�F�[�h�C���̍X�V����
//==========================================================================================
void cSoundCtrl::UpdateFadeIn(void)
{
	if (m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[(int)BGMCHANNEL::MAIN]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume += m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN];

			// �}�X�^�[�{�����[����100����1�f�V�x���P�ʂŎ擾����
			ChangeVolumeSoundMem(m_nMasterVolume, handle);
			int masterVolume = GetVolumeSoundMem(handle);

			if (volume >= masterVolume)
			{
				volume = masterVolume;
				m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN] = 0;
				m_eBgmState = BGMSTATE::NORMAL;
			}
			SetVolumeSoundMem(volume, handle);
		}
	}
	else
	{
		m_eBgmState = BGMSTATE:: NORMAL;
	}
}

//==========================================================================================
// �N���X�t�F�[�h�̍X�V����
//==========================================================================================
void cSoundCtrl::UpdateCrossFade(void)
{
	bool fadeOutComp = false;
	bool fadeInComp = false;
	//-----------------------------------------------------------------------------
	// �t�F�[�h�A�E�g����
	if (m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[(int)BGMCHANNEL::MAIN]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume -= m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN];
			if (volume <= 0)
			{
				volume = 0;
				m_nBgmVolumeFade[(int)BGMCHANNEL::MAIN] = 0;
				fadeOutComp = true;

				BGMStop(BGMCHANNEL::MAIN);
				// ���炵���{�����[����߂��Ă���
				ChangeVolumeSoundMem(m_nMasterVolume, handle);
			}
			if( !fadeOutComp) SetVolumeSoundMem(volume, handle);
		}
	}
	else
	{
		fadeOutComp = true;
	}
	//-----------------------------------------------------------------------------
	// �t�F�[�h�C������
	if (m_nBgmVolumeFade[(int)BGMCHANNEL::SWAP] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[(int)BGMCHANNEL::SWAP]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume += m_nBgmVolumeFade[(int)BGMCHANNEL::SWAP];

			// �}�X�^�[�{�����[����100����1�f�V�x���P�ʂŎ擾����
			ChangeVolumeSoundMem(m_nMasterVolume, handle);
			int masterVolume = GetVolumeSoundMem(handle);

			if (volume >= masterVolume)
			{
				volume = masterVolume;
				m_nBgmVolumeFade[(int)BGMCHANNEL::SWAP] = 0;
				fadeInComp = true;
			}
			SetVolumeSoundMem(volume, handle);
		}
	}
	else
	{
		fadeInComp = true;
	}
	// �N���X�t�F�[�h�I��
	if (fadeOutComp && fadeInComp)
	{
		m_sPlayBgmName[(int)BGMCHANNEL::MAIN] = m_sPlayBgmName[(int)BGMCHANNEL::SWAP];
		m_sPlayBgmName[(int)BGMCHANNEL::SWAP] = "";
		m_eBgmState = BGMSTATE::NORMAL;
	}
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cSoundCtrl::cSoundCtrl(void):
	m_nMasterVolume(DEFAULT_MASTER_VOLUME),
	m_nBgmVolumeFade(),
	m_eBgmState(BGMSTATE::NORMAL)
{
	for (int i = 0; i < (int)BGMCHANNEL::NUM; i++) m_nBgmVolumeFade[i] = 0;
	m_listSdLoaded.clear();
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cSoundCtrl::cSoundCtrl(IBaseObject* parent):
	cSoundCtrl::cSoundCtrl()
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cSoundCtrl::cSoundCtrl(IBaseObject* parent, const std::string& name):
	cSoundCtrl::cSoundCtrl(parent)
{
}

//==========================================================================================
// �R�s�[�R���X�g���N�^
//==========================================================================================
cSoundCtrl::cSoundCtrl(const cSoundCtrl& t) :
	cSoundCtrl::cSoundCtrl()
{
}
