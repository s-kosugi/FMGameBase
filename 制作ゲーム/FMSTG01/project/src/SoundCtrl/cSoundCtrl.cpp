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
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "SoundCtrl";

	m_listSdLoaded.clear();
	m_nMasterVolume = DEFAULT_MASTER_VOLUME;
	for (int i = 0; i < BGM_CHANNEL_NUM; i++) m_nBgmVolumeFade[i] = 0;
	m_eBgmState = m_eBgmState;

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cSoundCtrl::Update(void)
{
	switch (m_eBgmState)
	{
	case BGM_NORMAL:
		break;
	case BGM_FADEOUT:
		UpdateFadeOut();
		break;
	case BGM_FADEIN:
		UpdateFadeIn();
		break;
	case BGM_CROSSFADE:
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
int cSoundCtrl::Load(SoundID id, int bufnum)
{
	return Load(SOUNDNAME_TABLE[id]);;
}

//==========================================================================================
//	サウンドの読み込み
//  戻り値 : 読み込み済みのサウンドハンドル
//==========================================================================================
int cSoundCtrl::Load(const std::string & filename, int bufnum)
{
	int handle = SearchSoundHandle(filename);
	if (handle != LOADSOUND_FAILED) return handle;

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
	for (int i = 0; i < SOUND_MAX; i++)
	{
		Load(SOUNDNAME_TABLE[i]);
	}
}
//==========================================================================================
//	サウンドの削除
//==========================================================================================
void cSoundCtrl::Delete(SoundID id)
{
	Delete(SOUNDNAME_TABLE[id]);
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
int cSoundCtrl::Play(SoundID id, bool loop)
{
	return Play(SOUNDNAME_TABLE[id], loop);
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
int cSoundCtrl::BGMPlay(SoundID id, BgmChannel ch)
{
	int handle = BGMPlay(SOUNDNAME_TABLE[id], ch);
	return handle;
}
//==========================================================================================
//	BGMの再生
//  return : 再生中の音声のハンドル
//==========================================================================================
int cSoundCtrl::BGMPlay(const std::string & filename, BgmChannel ch)
{
	int handle = Play(filename,true);
	if (handle != LOADSOUND_FAILED)
	{
		BGMStop(ch);
		m_sPlayBgmName[ch] = filename;
	}
	return handle;
}
//==========================================================================================
//	サウンドの停止
//==========================================================================================
void cSoundCtrl::Stop(SoundID id)
{
	Stop(SOUNDNAME_TABLE[id]);
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
void cSoundCtrl::BGMStop(BgmChannel ch)
{
	Stop(m_sPlayBgmName[ch]);
}
//==========================================================================================
//	マスターボリュームの変更
//  int vol : 0～255  0は無音 255は最大音量
//==========================================================================================
void cSoundCtrl::ChangeMasterVolume(int vol)
{
	m_nMasterVolume =  vol;
}
//==========================================================================================
//	ボリュームの変更
//  int vol : 0～255  0は無音 255は最大音量
//==========================================================================================
void cSoundCtrl::ChangeVolume(SoundID id, int vol)
{
	ChangeVolume(SOUNDNAME_TABLE[id],vol);
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
	int handle = SearchSoundHandle(m_sPlayBgmName[BGMCHANNEL_MAIN]);

	if( handle == LOADSOUND_FAILED) return;

	int volume = GetVolumeSoundMem(handle);

	m_nBgmVolumeFade[BGMCHANNEL_MAIN] = (int)(((float)volume / frame) + 0.5f);
	m_eBgmState = BGM_FADEOUT;
}
//==========================================================================================
//	BGMのフェードインの設定
//  int frame : フェードイン時間
//  同じBGMIDをフェードインさせる場合は前フレームで停止してある必要がある(DXLibの再生の仕様)
//==========================================================================================
void cSoundCtrl::FadeInBgm(unsigned int frame, SoundID id, BgmChannel ch)
{
	int handle = BGMPlay(id,ch);

	if (handle == LOADSOUND_FAILED) return;

	// マスターボリュームを100分の1デシベル単位で取得
	ChangeVolumeSoundMem(m_nMasterVolume, handle);
	int volume = GetVolumeSoundMem(handle);

	ChangeVolume(id, 0);

	m_nBgmVolumeFade[ch] = (int)(((float)volume / frame) + 0.5f);
	m_eBgmState = BGM_FADEIN;
}
//==========================================================================================
//	BGMのフェードインの設定
//  int outframe : フェードイン時間
//  int inframe : フェードアウト時間
//  SoundID id : フェードインさせるSoundID
//==========================================================================================
void cSoundCtrl::CrossFadeBgm(unsigned int outframe, unsigned int inframe, SoundID id)
{
	FadeOutBgm(outframe);
	FadeInBgm(inframe, id, BGMCHANNEL_SWAP);
	m_eBgmState = BGM_CROSSFADE;
}
//==========================================================================================
// 周波数の設定
//==========================================================================================
void cSoundCtrl::SetFrequency(SoundID id, int value)
{
	SetFrequencySoundMem(value, SearchSoundHandle(SOUNDNAME_TABLE[id]));
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
int cSoundCtrl::GetFrequency(SoundID id)
{
	return GetFrequencySoundMem(SearchSoundHandle(SOUNDNAME_TABLE[id]));
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
	if (m_nBgmVolumeFade[BGMCHANNEL_MAIN] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[BGMCHANNEL_MAIN]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume -= m_nBgmVolumeFade[BGMCHANNEL_MAIN];
			if (volume <= 0)
			{
				volume = 0;
				m_nBgmVolumeFade[BGMCHANNEL_MAIN] = 0;
				m_eBgmState = BGM_NORMAL;
				BGMStop(BGMCHANNEL_MAIN);
				// 減らしたボリュームを戻しておく
				ChangeVolumeSoundMem(m_nMasterVolume,handle);
				return;
			}
			SetVolumeSoundMem(volume, handle);
		}
	}
	else
	{
		m_eBgmState = BGM_NORMAL;
	}
}
//==========================================================================================
// フェードインの更新処理
//==========================================================================================
void cSoundCtrl::UpdateFadeIn(void)
{
	if (m_nBgmVolumeFade[BGMCHANNEL_MAIN] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[BGMCHANNEL_MAIN]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume += m_nBgmVolumeFade[BGMCHANNEL_MAIN];

			// マスターボリュームを100分の1デシベル単位で取得する
			ChangeVolumeSoundMem(m_nMasterVolume, handle);
			int masterVolume = GetVolumeSoundMem(handle);

			if (volume >= masterVolume)
			{
				volume = masterVolume;
				m_nBgmVolumeFade[BGMCHANNEL_MAIN] = 0;
				m_eBgmState = BGM_NORMAL;
			}
			SetVolumeSoundMem(volume, handle);
		}
	}
	else
	{
		m_eBgmState = BGM_NORMAL;
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
	if (m_nBgmVolumeFade[BGMCHANNEL_MAIN] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[BGMCHANNEL_MAIN]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume -= m_nBgmVolumeFade[BGMCHANNEL_MAIN];
			if (volume <= 0)
			{
				volume = 0;
				m_nBgmVolumeFade[BGMCHANNEL_MAIN] = 0;
				fadeOutComp = true;

				BGMStop(BGMCHANNEL_MAIN);
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
	if (m_nBgmVolumeFade[BGMCHANNEL_SWAP] > 0)
	{
		int handle = SearchSoundHandle(m_sPlayBgmName[BGMCHANNEL_SWAP]);

		if (handle != LOADSOUND_FAILED)
		{
			int volume = GetVolumeSoundMem(handle);
			volume += m_nBgmVolumeFade[BGMCHANNEL_SWAP];

			// マスターボリュームを100分の1デシベル単位で取得する
			ChangeVolumeSoundMem(m_nMasterVolume, handle);
			int masterVolume = GetVolumeSoundMem(handle);

			if (volume >= masterVolume)
			{
				volume = masterVolume;
				m_nBgmVolumeFade[BGMCHANNEL_SWAP] = 0;
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
		m_sPlayBgmName[BGMCHANNEL_MAIN] = m_sPlayBgmName[BGMCHANNEL_SWAP];
		m_sPlayBgmName[BGMCHANNEL_SWAP] = "";
		m_eBgmState = BGM_NORMAL;
	}
}
