#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSoundCtrl.h												*/
/*  @brief		:	サウンド操作クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/30													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"
#include "SoundID.h"

//===============================================================================
// サウンド管理クラス
class cSoundCtrl : public IBaseSingleton<cSoundCtrl>
{
public:
	// BGMのチャンネル定義
	enum BgmChannel
	{
		BGMCHANNEL_MAIN = 0,
		BGMCHANNEL_SWAP,		// クロスフェードでの入れ替え用チャンネル

		BGM_CHANNEL_NUM
	};

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// サウンドの読み込み
	// 引数 : id サウンドのID   bufnum 同時再生可能数
	// 戻り値 : サウンドハンドル
	int Load(SoundID id, int bufnum = 3);

	// サウンドの読み込み
	// 引数 : filename サウンドファイルパス   bufnum 同時再生可能数
	// 戻り値 : サウンドハンドル
	int Load(const std::string& filename, int bufnum = 3);

	// 全サウンドの読み込み
	void LoadAll( void );

	// サウンドの削除処理
	void Delete(SoundID id);
	void Delete(const std::string& filename);

	// サウンドの再生
	int Play(SoundID id, bool loop = false);
	int Play(const std::string& filename ,bool loop = false);
	int BGMPlay(SoundID id, BgmChannel ch = BGMCHANNEL_MAIN);
	int BGMPlay(const std::string& filename, BgmChannel ch = BGMCHANNEL_MAIN);

	// サウンドの停止
	void Stop(SoundID id);
	void Stop(const std::string& filename );
	void BGMStop(BgmChannel ch = BGMCHANNEL_MAIN);

	// マスターボリュームの変更
	void ChangeMasterVolume( int vol );

	// ボリュームの変更
	void ChangeVolume( SoundID id, int vol);
	void ChangeVolume( const std::string& filename , int vol );

	// BGMのフェードアウトの設定
	void FadeOutBgm( unsigned int frame );

	// BGMのフェードインの設定
	void FadeInBgm( unsigned int frame,SoundID id, BgmChannel ch = BGMCHANNEL_MAIN);

	// BGMのクロスフェードの設定
	void CrossFadeBgm( unsigned int outframe,unsigned int inframe,SoundID id);

	// 周波数の設定
	void SetFrequency(SoundID id, int value);
	void SetFrequency(const std::string& filename, int value);

	// 周波数の取得
	int GetFrequency(SoundID id);
	int GetFrequency(const std::string& filename);

private:
	//--------------------------------------------------------------------------------------
	// ファイル読み込み関連
	// 読み込みファイル構造体
	struct SdLoaded
	{
		std::string FileName;
		int SoundHandle;
	};

	//--------------------------------------------------------------------------------------
	// 定数
	const int LOADSOUND_FAILED = -1;		 // LoaSoundMem失敗

	const int DEFAULT_MASTER_VOLUME = 100;

	// サウンド名テーブル
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

	// 読み込み済みサウンドリスト
	std::list<SdLoaded> m_listSdLoaded;

	// 再生中BGM名
	std::string			m_sPlayBgmName[BGM_CHANNEL_NUM];


	// マスターボリューム
	int m_nMasterVolume;

	// BGMボリュームのフェード値(100分の1デシベル単位)
	int m_nBgmVolumeFade[BGM_CHANNEL_NUM];

	// BGMの状態
	BgmState m_eBgmState;

	//--------------------------------------------------------------------------------------
	// サウンドハンドルの検索
	// 戻り値:サウンドハンドル  LOADSOUND_FAILED:失敗
	int SearchSoundHandle(const std::string& filename);

	//--------------------------------------------------------------------------------------
	// フェードアウトの更新処理
	void UpdateFadeOut( void );

	// フェードインの更新処理
	void UpdateFadeIn(void);

	// クロスフェードの更新処理
	void UpdateCrossFade(void);
};