#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSoundCtrl.h												*/
/*  @brief		:	�T�E���h����N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/30													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"
#include "SoundID.h"

//===============================================================================
// �T�E���h�Ǘ��N���X
class cSoundCtrl : public IBaseObject
{
public:
	// BGM�̃`�����l����`
	enum class BGMCHANNEL
	{
		MAIN = 0,
		SWAP,		// �N���X�t�F�[�h�ł̓���ւ��p�`�����l��

		NUM
	};

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �T�E���h�̓ǂݍ���
	// ���� : id �T�E���h��ID   bufnum �����Đ��\��
	// �߂�l : �T�E���h�n���h��
	int Load(SOUND_ID id,int bufnum = 3);

	// �T�E���h�̓ǂݍ���
	// ���� : filename �T�E���h�t�@�C���p�X   bufnum �����Đ��\��
	// �߂�l : �T�E���h�n���h��
	int Load(const std::string& filename,int bufnum = 3);

	// �S�T�E���h�̓ǂݍ���
	void LoadAll( void );

	// �T�E���h�̍폜����
	void Delete(SOUND_ID id);
	void Delete(const std::string& filename);

	// �T�E���h�̍Đ�
	int Play(SOUND_ID id, bool loop = false);
	int Play(const std::string& filename ,bool loop = false);
	int BGMPlay(SOUND_ID id, BGMCHANNEL ch = BGMCHANNEL::MAIN);
	int BGMPlay(const std::string& filename, BGMCHANNEL ch = BGMCHANNEL::MAIN);

	// �T�E���h�̒�~
	void Stop(SOUND_ID id);
	void Stop(const std::string& filename );
	void BGMStop(BGMCHANNEL ch = BGMCHANNEL::MAIN);

	// �}�X�^�[�{�����[���̕ύX
	void ChangeMasterVolume( int vol );

	// �{�����[���̕ύX
	void ChangeVolume( SOUND_ID id, int vol);
	void ChangeVolume( const std::string& filename , int vol );

	// BGM�̃t�F�[�h�A�E�g�̐ݒ�
	void FadeOutBgm( unsigned int frame );

	// BGM�̃t�F�[�h�C���̐ݒ�
	void FadeInBgm( unsigned int frame,SOUND_ID id, BGMCHANNEL ch = BGMCHANNEL::MAIN);

	// BGM�̃N���X�t�F�[�h�̐ݒ�
	void CrossFadeBgm( unsigned int outframe,unsigned int inframe,SOUND_ID id);

	// ���g���̐ݒ�
	void SetFrequency( SOUND_ID id , int value );
	void SetFrequency( const std::string& filename, int value);

	// ���g���̎擾
	int GetFrequency(SOUND_ID id);
	int GetFrequency(const std::string& filename);

	// �w�肵���T�E���h���Đ������ǂ����𒲂ׂ�
	bool CheckPlaySound(SOUND_ID id);
	bool CheckPlaySound(const std::string& filename);

private:
	//--------------------------------------------------------------------------------------
	// �t�@�C���ǂݍ��݊֘A
	// �ǂݍ��݃t�@�C���\����
	struct SdLoaded
	{
		std::string FileName = "";
		int SoundHandle = -1;
	};

	//--------------------------------------------------------------------------------------
	// �萔
	const int LOADSOUND_FAILED = -1;		 // LoaSoundMem���s

	const int DEFAULT_MASTER_VOLUME = 100;

	// �T�E���h���e�[�u��
	std::string SOUNDNAME_TABLE[(int)SOUND_ID::MAX] =
	{
		"data\\sound\\se00.ogg",

		"data\\sound\\bgm00.ogg",

	};

	//--------------------------------------------------------------------------------------
	enum class BGMSTATE
	{
		NORMAL = 0,
		FADEOUT,
		FADEIN,
		CROSSFADE,
	};

	// �ǂݍ��ݍς݃T�E���h���X�g
	std::list<SdLoaded> m_listSdLoaded;

	// �Đ���BGM��
	std::string			m_sPlayBgmName[(int)BGMCHANNEL::NUM];


	// �}�X�^�[�{�����[��
	int m_nMasterVolume;

	// BGM�{�����[���̃t�F�[�h�l(100����1�f�V�x���P��)
	int m_nBgmVolumeFade[(int)BGMCHANNEL::NUM];

	// BGM�̏��
	BGMSTATE m_eBgmState;

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


//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cSoundCtrl(void);     //  ������̐������֎~
	cSoundCtrl(IBaseObject* parent);
	cSoundCtrl(IBaseObject* parent, const std::string& name);
	~cSoundCtrl(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cSoundCtrl(const cSoundCtrl& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cSoundCtrl& operator = (const cSoundCtrl& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:

	static cSoundCtrl& GetInstance(void) {
		static cSoundCtrl instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
//-----------------------------------------------------------------------------------------------------
};