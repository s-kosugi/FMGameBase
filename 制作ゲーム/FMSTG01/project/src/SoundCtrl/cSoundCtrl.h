#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSoundCtrl.h												*/
/*  @brief		:	�T�E���h����N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/30													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"
#include "SoundID.h"

//===============================================================================
// �T�E���h�Ǘ��N���X
class cSoundCtrl : public IBaseSingleton<cSoundCtrl>
{
public:
	// BGM�̃`�����l����`
	enum BgmChannel
	{
		BGMCHANNEL_MAIN = 0,
		BGMCHANNEL_SWAP,		// �N���X�t�F�[�h�ł̓���ւ��p�`�����l��

		BGM_CHANNEL_NUM
	};

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �T�E���h�̓ǂݍ���
	// ���� : id �T�E���h��ID   bufnum �����Đ��\��
	// �߂�l : �T�E���h�n���h��
	int Load(SoundID id, int bufnum = 3);

	// �T�E���h�̓ǂݍ���
	// ���� : filename �T�E���h�t�@�C���p�X   bufnum �����Đ��\��
	// �߂�l : �T�E���h�n���h��
	int Load(const std::string& filename, int bufnum = 3);

	// �S�T�E���h�̓ǂݍ���
	void LoadAll( void );

	// �T�E���h�̍폜����
	void Delete(SoundID id);
	void Delete(const std::string& filename);

	// �T�E���h�̍Đ�
	int Play(SoundID id, bool loop = false);
	int Play(const std::string& filename ,bool loop = false);
	int BGMPlay(SoundID id, BgmChannel ch = BGMCHANNEL_MAIN);
	int BGMPlay(const std::string& filename, BgmChannel ch = BGMCHANNEL_MAIN);

	// �T�E���h�̒�~
	void Stop(SoundID id);
	void Stop(const std::string& filename );
	void BGMStop(BgmChannel ch = BGMCHANNEL_MAIN);

	// �}�X�^�[�{�����[���̕ύX
	void ChangeMasterVolume( int vol );

	// �{�����[���̕ύX
	void ChangeVolume( SoundID id, int vol);
	void ChangeVolume( const std::string& filename , int vol );

	// BGM�̃t�F�[�h�A�E�g�̐ݒ�
	void FadeOutBgm( unsigned int frame );

	// BGM�̃t�F�[�h�C���̐ݒ�
	void FadeInBgm( unsigned int frame,SoundID id, BgmChannel ch = BGMCHANNEL_MAIN);

	// BGM�̃N���X�t�F�[�h�̐ݒ�
	void CrossFadeBgm( unsigned int outframe,unsigned int inframe,SoundID id);

	// ���g���̐ݒ�
	void SetFrequency(SoundID id, int value);
	void SetFrequency(const std::string& filename, int value);

	// ���g���̎擾
	int GetFrequency(SoundID id);
	int GetFrequency(const std::string& filename);

private:
	//--------------------------------------------------------------------------------------
	// �t�@�C���ǂݍ��݊֘A
	// �ǂݍ��݃t�@�C���\����
	struct SdLoaded
	{
		std::string FileName;
		int SoundHandle;
	};

	//--------------------------------------------------------------------------------------
	// �萔
	const int LOADSOUND_FAILED = -1;		 // LoaSoundMem���s

	const int DEFAULT_MASTER_VOLUME = 100;

	// �T�E���h���e�[�u��
	std::string SOUNDNAME_TABLE[SOUND_MAX] =
	{
		"data\\sound\\se01_bom.ogg",		// 0:SOUND_BOM
		"data\\sound\\se02_pi.ogg",			// 1:SOUND_PI
		"data\\sound\\se03_pipi.ogg",		// 2:SOUND_LOCK
		"data\\sound\\se04_shuwa.ogg",		// 3:SOUND_LASER
		"data\\sound\\se05_shot.ogg",		// 4:SOUND_SHOT
		"data\\sound\\se06_bosscharge.ogg",	// 5:SOUND_BOSSCHARGE
		"data\\sound\\se07_bossbeam.ogg",	// 6:SOUND_BOSSBEAM
		"data\\sound\\se08_bigbom.ogg",		// 7:SOUND_BIGBOM
		"data\\sound\\se00.ogg",			// 8:SOUND_PIRO
		"data\\sound\\se09_digi.ogg",		// 9:SOUND_DIGI
		"data\\sound\\se10_kachi.ogg",		//10:SOUND_KACHI
		"data\\sound\\se11_warning.ogg",	//11:SOUND_WARNING
		"data\\sound\\se12_shoot.ogg",		//12:SOUND_SHOOT


		"data\\sound\\Mechanical_doll_Free_ver.ogg",	// SOUND_TITLE
		"data\\sound\\cyber-dolls_free_bgm_v3.ogg",		// SOUND_STAGE1
		"data\\sound\\Experimenta_Model_short.ogg",		// SOUND_BOSS

	};

	//--------------------------------------------------------------------------------------
	enum BgmState
	{
		BGM_NORMAL = 0,
		BGM_FADEOUT,
		BGM_FADEIN,
		BGM_CROSSFADE,
	};

	// �ǂݍ��ݍς݃T�E���h���X�g
	std::list<SdLoaded> m_listSdLoaded;

	// �Đ���BGM��
	std::string			m_sPlayBgmName[BGM_CHANNEL_NUM];


	// �}�X�^�[�{�����[��
	int m_nMasterVolume;

	// BGM�{�����[���̃t�F�[�h�l(100����1�f�V�x���P��)
	int m_nBgmVolumeFade[BGM_CHANNEL_NUM];

	// BGM�̏��
	BgmState m_eBgmState;

	//--------------------------------------------------------------------------------------
	// �T�E���h�n���h���̌���
	// �߂�l:�T�E���h�n���h��  LOADSOUND_FAILED:���s
	int SearchSoundHandle(const std::string& filename);

	//--------------------------------------------------------------------------------------
	// �t�F�[�h�A�E�g�̍X�V����
	void UpdateFadeOut( void );

	// �t�F�[�h�C���̍X�V����
	void UpdateFadeIn(void);

	// �N���X�t�F�[�h�̍X�V����
	void UpdateCrossFade(void);
};