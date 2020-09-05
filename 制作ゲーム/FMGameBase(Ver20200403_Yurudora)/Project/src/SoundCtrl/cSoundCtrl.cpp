/*==============================================================================*/
/*																				*/
/*	@file title	:	cSoundCtrl.cpp												*/
/*  @brief		:	サウンド操作クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/30													*/
/*																				*/
/*==============================================================================*/

#include "cSoundCtrl.h"
#include <DxLib.h>

//==========================================================================================
// 初期化
//==========================================================================================
void cSoundCtrl::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "SoundCtrl";

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
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
// 破棄
//==========================================================================================
IBaseObject* cSoundCtrl::Finalize(void)
{
	IBaseObject::Finalize();

	//------------------------------------------------------------------------------------
	// 読み込み済みサウンドの解放
	if (!m_listSdLoaded.empty())
	{
		InitSoundMem();
		m_listSdLoaded.clear();
	}
	return nullptr;
}
//==========================================================================================
//	サウンドの読み込み
//  戻り値 : 読み込み済みのサウンドハンドル
//==========================================================================================
int cSoundCtrl::Load(SOUND_ID id,int bufnum)
{
	return Load(SOUNDNAME_TABLE[(int)id]);;
}

//==========================================================================================
//	サウンドの読み込み
//  戻り値 : 読み込み済みのサウンドハンドル
//==========================================================================================
int cSoundCtrl::Load(const std::string & filename,int bufnum)
{
	int handle = SearchSoundHandle(filename);
	if( handle != LOADSOUND_FAILED ) return handle;

	// 新規読み込み音声をリストに追加する
	SdLoaded load;
	load.FileName = filename;
	load.SoundHandle = LoadSoundMem(filename.c_str(), bufnum);

	// サウンドハンドル読み込み失敗
	if (LOADSOUND_FAILED == load.SoundHandle)
		return LOADSOUND_FAILED;

	// 読み込み済みリストに追加
	m_listSdLoaded.push_back(load);
	return load.SoundHandle;
}
//==========================================================================================
//	全サウンドの読み込み
//==========================================================================================
void cSoundCtrl::LoadAll(void)
{
	for (int i = 0; i < (int)SOUND_ID::MAX; i++)
	{
		Load(SOUNDNAME_TABLE[i]);
	}
}
//==========================================================================================
//	サウンドの削除
//==========================================================================================
void cSoundCtrl::Delete(SOUND_ID id)
{
	Delete(SOUNDNAME_TABLE[(int)id]);
}

//==========================================================================================
//	サウンドの削除
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
				// メモリから削除
				DeleteSoundMem(it->SoundHandle);

				// リストから削除
				m_listSdLoaded.erase(it);
				return;
			}

			it++;
		}
	}
}
//==========================================================================================
//	サウンドの再生
//  return : 再生中の音声のハンドル
//==========================================================================================
int cSoundCtrl::Play(SOUND_ID id, bool loop)
{
	return Play(SOUNDNAME_TABLE[(int)id], loop);
}
//==========================================================================================
//	サウンドの再生
//  return : 再生中の音声のハンドル
//==========================================================================================
int cSoundCtrl::Play(const std::string & filename, bool loop)
{
	int handle = SearchSoundHandle(filename);
	if (handle == LOADSOUND_FAILED)
	{
		// 未読み込みのサウンドだったら読み込む
		handle = Load(filename);
	}
	// マスターボリュームを設定する
	ChangeVolumeSoundMem(m_nMasterVolume, handle);

	// 再生タイプの設定
	int PlayType;
	if( loop ) PlayType = DX_PLAYTYPE_LOOP;
	else PlayType = DX_PLAYTYPE_BACK;

	// サウンドの再生
	PlaySoundMem(handle,PlayType,TRUE);

	return handle;
}
//==========================================================================================
//	BGMの再生
//  return : 再生中の音声のハンドル
//==========================================================================================
int cSoundCtrl::BGMPlay(SOUND_ID id, BGMCHANNEL ch)
{
	int handle = BGMPlay(SOUNDNAME_TABLE[(int)id], ch);
	return handle;
}
//==========================================================================================
//	BGMの再生
//  return : 再生中の音声のハンドル
//==========================================================================================
int cSoundCtrl::BGMPlay(const std::string & filename, BGMCHANNEL ch)
{
	int chHandle = SearchSoundHandle(filename);

	// 再生中のBGMが設定された場合には処理をせずに音声ハンドルを返す
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
//	サウンドの停止
//==========================================================================================
void cSoundCtrl::Stop(SOUND_ID id)
{
	Stop(SOUNDNAME_TABLE[(int)id]);
}
//==========================================================================================
//	サウンドの停止
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
//	BGMの停止
//==========================================================================================
void cSoundCtrl::BGMStop(BGMCHANNEL ch)
{
	Stop(m_sPlayBgmName[(int)ch]);
}
//==========================================================================================
//	マスターボリュームの変更
//  int vol : 0～255  0は無音 255は最大音量
//==========================================================================================
void cSoundCtrl::ChangeMasterVolume(int vol)
{
	m_nMasterVolume =  vol;

	// 現在鳴っている音も変更する
	for (int i = 0; i < (int)SOUND_ID::MAX; i++)
	{
		ChangeVolumeSoundMem(m_nMasterVolume, SearchSoundHandle(SOUNDNAME_TABLE[i]));
	}
}
//==========================================================================================
//	ボリュームの変更
//  int vol : 0～255  0は無音 255は最大音量
//==========================================================================================
void cSoundCtrl::ChangeVolume(SOUND_ID id, int vol)
{
	ChangeVolume(SOUNDNAME_TABLE[(int)id],vol);
}
//==========================================================================================
//	ボリュームの変更
//  int vol : 0～255  0は無音 255は最大音量
//==========================================================================================
void cSoundCtrl::ChangeVolume(const std::string & filename, int vol)
{
	int handle = SearchSoundHandle(filename);

	if( LOADSOUND_FAILED ==  handle ) return;

	ChangeVolumeSoundMem(vol,handle);
}
//==========================================================================================
//	BGMのフェードアウトの設定
//  int frame : フェードアウト時間
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
//	BGMのフェードインの設定
//  int frame : フェードイン時間
//  同じBGMIDをフェードインさせる場合は前フレームで停止してある必要がある(DXLibの再生の仕様)
//==========================================================================================
void cSoundCtrl::FadeInBgm(unsigned int frame, SOUND_ID id, BGMCHANNEL ch)
{
	int handle = BGMPlay(id,ch);

	if (handle == LOADSOUND_FAILED) return;

	// マスターボリュームを100分の1デシベル単位で取得
	ChangeVolumeSoundMem(m_nMasterVolume, handle);
	int volume = GetVolumeSoundMem(handle);

	ChangeVolume(id, 0);

	m_nBgmVolumeFade[(int)ch] = (int)(((float)volume / frame) + 0.5f);
	m_eBgmState = BGMSTATE::FADEIN;
}
//==========================================================================================
//	BGMのフェードインの設定
//  int outframe : フェードイン時間
//  int inframe : フェードアウト時間
//  SoundID id : フェードインさせるSoundID
//==========================================================================================
void cSoundCtrl::CrossFadeBgm(unsigned int outframe, unsigned int inframe, SOUND_ID id)
{
	FadeOutBgm(outframe);
	FadeInBgm(inframe, id, BGMCHANNEL::SWAP);
	m_eBgmState = BGMSTATE::CROSSFADE;
}
//==========================================================================================
// 周波数の設定
//==========================================================================================
void cSoundCtrl::SetFrequency(SOUND_ID id, int value)
{
	SetFrequencySoundMem(value, SearchSoundHandle(SOUNDNAME_TABLE[(int)id]));
}
//==========================================================================================
// 周波数の設定
//==========================================================================================
void cSoundCtrl::SetFrequency(const std::string & filename, int value)
{
	SetFrequencySoundMem(value, SearchSoundHandle(filename));
}
//==========================================================================================
// 周波数の取得
//==========================================================================================
int cSoundCtrl::GetFrequency(SOUND_ID id)
{
	return GetFrequencySoundMem(SearchSoundHandle(SOUNDNAME_TABLE[(int)id]));
}
//==========================================================================================
// 周波数の取得
//==========================================================================================
int cSoundCtrl::GetFrequency(const std::string & filename)
{
	return GetFrequencySoundMem(SearchSoundHandle(filename));
}
//==========================================================================================
// サウンドハンドルの検索
// 戻り値:サウンドハンドル  LOADSOUND_FAILED:失敗
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
// フェードアウトの更新処理
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
				// 減らしたボリュームを戻しておく
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
// フェードインの更新処理
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

			// マスターボリュームを100分の1デシベル単位で取得する
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
// クロスフェードの更新処理
//==========================================================================================
void cSoundCtrl::UpdateCrossFade(void)
{
	bool fadeOutComp = false;
	bool fadeInComp = false;
	//-----------------------------------------------------------------------------
	// フェードアウト部分
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
				// 減らしたボリュームを戻しておく
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
	// フェードイン部分
	if (m_nBgmVolumeFade[(int)BGMCHANNEL::SWAP] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[(int)BGMCHANNEL::SWAP]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume += m_nBgmVolumeFade[(int)BGMCHANNEL::SWAP];

			// マスターボリュームを100分の1デシベル単位で取得する
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
	// クロスフェード終了
	if (fadeOutComp && fadeInComp)
	{
		m_sPlayBgmName[(int)BGMCHANNEL::MAIN] = m_sPlayBgmName[(int)BGMCHANNEL::SWAP];
		m_sPlayBgmName[(int)BGMCHANNEL::SWAP] = "";
		m_eBgmState = BGMSTATE::NORMAL;
	}
}

//==========================================================================================
// コンストラクタ
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
// コンストラクタ
//==========================================================================================
cSoundCtrl::cSoundCtrl(IBaseObject* parent):
	cSoundCtrl::cSoundCtrl()
{
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cSoundCtrl::cSoundCtrl(IBaseObject* parent, const std::string& name):
	cSoundCtrl::cSoundCtrl(parent)
{
}

//==========================================================================================
// コピーコンストラクタ
//==========================================================================================
cSoundCtrl::cSoundCtrl(const cSoundCtrl& t) :
	cSoundCtrl::cSoundCtrl()
{
}
