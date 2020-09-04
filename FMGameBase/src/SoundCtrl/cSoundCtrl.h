#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSoundCtrl.h												*/
/*  @brief		:	サウンド操作クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/30													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"
#include "SoundID.h"

//===============================================================================
// サウンド管理クラス
class cSoundCtrl : public IBaseObject
{
public:
	// BGMのチャンネル定義
	enum class BGMCHANNEL
	{
		MAIN = 0,
		SWAP,		// クロスフェードでの入れ替え用チャンネル

		NUM
	};

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// サウンドの読み込み
	// 引数 : id サウンドのID   bufnum 同時再生可能数
	// 戻り値 : サウンドハンドル
	int Load(SOUND_ID id,int bufnum = 3);

	// サウンドの読み込み
	// 引数 : filename サウンドファイルパス   bufnum 同時再生可能数
	// 戻り値 : サウンドハンドル
	int Load(const std::string& filename,int bufnum = 3);

	// 全サウンドの読み込み
	void LoadAll( void );

	// サウンドの削除処理
	void Delete(SOUND_ID id);
	void Delete(const std::string& filename);

	// サウンドの再生
	int Play(SOUND_ID id, bool loop = false);
	int Play(const std::string& filename ,bool loop = false);
	int BGMPlay(SOUND_ID id, BGMCHANNEL ch = BGMCHANNEL::MAIN);
	int BGMPlay(const std::string& filename, BGMCHANNEL ch = BGMCHANNEL::MAIN);

	// サウンドの停止
	void Stop(SOUND_ID id);
	void Stop(const std::string& filename );
	void BGMStop(BGMCHANNEL ch = BGMCHANNEL::MAIN);

	// マスターボリュームの変更
	void ChangeMasterVolume( int vol );

	// ボリュームの変更
	void ChangeVolume( SOUND_ID id, int vol);
	void ChangeVolume( const std::string& filename , int vol );

	// BGMのフェードアウトの設定
	void FadeOutBgm( unsigned int frame );

	// BGMのフェードインの設定
	void FadeInBgm( unsigned int frame,SOUND_ID id, BGMCHANNEL ch = BGMCHANNEL::MAIN);

	// BGMのクロスフェードの設定
	void CrossFadeBgm( unsigned int outframe,unsigned int inframe,SOUND_ID id);

	// 周波数の設定
	void SetFrequency( SOUND_ID id , int value );
	void SetFrequency( const std::string& filename, int value);

	// 周波数の取得
	int GetFrequency(SOUND_ID id);
	int GetFrequency(const std::string& filename);

	// 指定したサウンドが再生中かどうかを調べる
	bool CheckPlaySound(SOUND_ID id);
	bool CheckPlaySound(const std::string& filename);

private:
	//--------------------------------------------------------------------------------------
	// ファイル読み込み関連
	// 読み込みファイル構造体
	struct SdLoaded
	{
		std::string FileName = "";
		int SoundHandle = -1;
	};

	//--------------------------------------------------------------------------------------
	// 定数
	const int LOADSOUND_FAILED = -1;		 // LoaSoundMem失敗

	const int DEFAULT_MASTER_VOLUME = 100;

	// サウンド名テーブル
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

	// 読み込み済みサウンドリスト
	std::list<SdLoaded> m_listSdLoaded;

	// 再生中BGM名
	std::string			m_sPlayBgmName[(int)BGMCHANNEL::NUM];


	// マスターボリューム
	int m_nMasterVolume;

	// BGMボリュームのフェード値(100分の1デシベル単位)
	int m_nBgmVolumeFade[(int)BGMCHANNEL::NUM];

	// BGMの状態
	BGMSTATE m_eBgmState;

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


//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cSoundCtrl(void);     //  他からの生成を禁止
	cSoundCtrl(IBaseObject* parent);
	cSoundCtrl(IBaseObject* parent, const std::string& name);
	~cSoundCtrl(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cSoundCtrl(const cSoundCtrl& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cSoundCtrl& operator = (const cSoundCtrl& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:

	static cSoundCtrl& GetInstance(void) {
		static cSoundCtrl instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
//-----------------------------------------------------------------------------------------------------
};