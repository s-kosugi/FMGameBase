#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEventManager.h												*/
/*  @brief		:	イベント管理クラス											*/
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
	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// イベントの開始
	void StartEvent(short no);

private:
	// イベント構造体
	struct Event
	{
		unsigned int StartTime;		// 開始時間
		unsigned int EndTime;		// 終了時間
		int			 EvtNo;			// イベント番号
		short		 Interval;		// 発生間隔
		int			 PosX;			// 発生位置X
		int			 PosY;			// 発生位置Y
	};

	// イベントファイル種別
	enum EventFileType
	{
		EVT_ENM = 0,		// 敵
		EVT_PER,			// 演出
		EVT_MAX,
	};

	// ファイル名生成
	std::string GenerateFilePath( short no , EventFileType type );

	// イベント生成
	void Create(std::vector<std::string>& readBuf);

	// イベント実行
	void ExecEvent( Event& evt );

	// 現在のステージ番号
	short		 m_nStageNo;
	// イベント経過時間
	unsigned int m_nEventTimer;
	// イベント構造体配列
	std::vector<Event> m_ArEvent;


	// 定数
	const short  MAX_READ_STAGE = 99;		// 最大ステージ読込数
	const short	 MAX_EVENT_MENBER = 6;		// イベント構造体のメンバー数

	// ランダム座標を判定する値
	const int RANDOM_SENTINEL = 999999;
};