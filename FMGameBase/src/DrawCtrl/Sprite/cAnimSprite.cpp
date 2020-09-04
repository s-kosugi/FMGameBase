/*==============================================================================*/
/*																				*/
/*	@file title	:	cAnimSprite.cpp												*/
/*  @brief		:	アニメーションスプライトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/04/14													*/
/*																				*/
/*==============================================================================*/

#include "cAnimSprite.h"
#include "..\cDrawCtrl.h"
#include "cGame.h"
#include "Utility/json_loader/rapidjson/document.h"
#include <fstream>
#include "Utility/StrControl/StrControl.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==========================================================================================
// 定数
//==========================================================================================
// キー名
const char*     cAnimSprite::m_sKeyName[] =
{
	"file",
	"frame",
	"width",
	"height",
	"cols",
	"rows",
	"animations",
	"frames",
	"interval",
	"loop",
};

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cAnimSprite::cAnimSprite(const std::string& filename) :
	cSprite(filename),
	m_FrameSize({ 0,0 }),
	m_nFrameCols(0),
	m_nFrameRows(0),
	m_nCurrentAnimeID(-1),
	m_fCurrentFrame(0.0f),
	m_fCurrentAnimeFPS(1.0f),
	m_bStopFlag( false ),
	m_fPlaySpeedRate(1.0f)
{

	if (Ends_With(filename, ".ass"))
	{
		// ASSファイル読込
		if (LoadASS(filename))
		{
			// アニメーションを変更
			ChangeAnime(0);
			// 描画情報を登録
			cDrawCtrl::GetInstance().RegistDrawObject(*this, m_sFileName);
		} else
		{
			// ASS読込失敗
			m_nCurrentAnimeID = 0;
		}
	} else
	{
		// 通常の画像ファイル
		m_nCurrentAnimeID = 0;
	}
	
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cAnimSprite::~cAnimSprite(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cAnimSprite::
Initialize(void)
{
	// アニメーションがセットされていたら表示画像を更新する
	if (0 < m_nFrameCols) {
		int index = (int)m_fCurrentFrame;
		index = (int)m_AnimationList[m_nCurrentAnimeID].Frames.size() - 1;

		// 指定されたアニメーションから描画範囲を算出
		int frame = m_AnimationList[m_nCurrentAnimeID].Frames[index];

		// 表示座標更新
		m_SrcRect.left = (frame % m_nFrameCols) * m_FrameSize.x;
		m_SrcRect.top = (frame / m_nFrameCols) * m_FrameSize.y;
		m_SrcRect.right = m_SrcRect.left + m_FrameSize.x;
		m_SrcRect.bottom = m_SrcRect.top + m_FrameSize.y;

		// アニメーションがセットされていたら中心位置を変更する。(小数点以下四捨五入)
		m_vCenter.x = (float)((int)(m_FrameSize.x / 2.0f + 0.5f));
		m_vCenter.y = (float)((int)(m_FrameSize.y / 2.0f + 0.5f));
	}
	IDrawBase::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cAnimSprite::Update(void)
{
	// 停止フラグまたはアニメーションがない場合には進めないようにする
	if (!m_bStopFlag && !m_AnimationList.empty())
	{

		// デルタタイム取得
		float delta_time = cGame::GetInstance().GetDeltaTime();

		// デルタタイムを使ってアニメーションフレームを更新
		// アニメーションの再生速度率も反映
		m_fCurrentFrame += m_fCurrentAnimeFPS * m_fPlaySpeedRate * delta_time;

		// アニメーションの最大フレームを超えていない
		if (!(m_fCurrentFrame < m_AnimationList[m_nCurrentAnimeID].Frames.size()))
		{
			// ループ設定であればフレームを先頭にもどす
			// そうでなければ最終フレームで固定する
			if (m_AnimationList[m_nCurrentAnimeID].Loop)
				m_fCurrentFrame = 0.0f;
		}

		// カレントフレームを取得
		int index = (int)m_fCurrentFrame;

		// 最大フレームを超えていたら制限
		if (index >= (int)m_AnimationList[m_nCurrentAnimeID].Frames.size())
			index = (int)m_AnimationList[m_nCurrentAnimeID].Frames.size() - 1;

		// 指定されたアニメーションから描画範囲を算出
		int frame = m_AnimationList[m_nCurrentAnimeID].Frames[index];

		m_SrcRect.left = (frame % m_nFrameCols) * m_FrameSize.x;
		m_SrcRect.top = (frame / m_nFrameCols) * m_FrameSize.y;
		m_SrcRect.right = m_SrcRect.left + m_FrameSize.x;
		m_SrcRect.bottom = m_SrcRect.top + m_FrameSize.y;
	}

	IDrawBase::Update();
}
//==========================================================================================
//  解放
//==========================================================================================
void cAnimSprite::Finalize(void)
{
	IDrawBase::Finalize();
}
//==========================================================================================
//  アニメーションの変更
//  animID : 変更するアニメーション名前
//==========================================================================================
void cAnimSprite::ChangeAnime(const std::string & animName)
{
	if (m_AnimationList.empty()) return;

	for (int i = 0; i < (int)m_AnimationList.size(); ++i)
	{
		// 名前が一致したIDでアニメーションを変更する
		if (m_AnimationList[i].Name == animName)
		{
			ChangeAnime( i );
			return;
		}
	}
}

//==========================================================================================
//  アニメーションの変更
//  animID : 変更するアニメーションのID
//==========================================================================================
void cAnimSprite::ChangeAnime(int animID)
{
	// アニメーションIDが同じなら変更しない
	if (m_nCurrentAnimeID == animID)
		return;

	m_nCurrentAnimeID = animID;
	m_fCurrentFrame = 0.0f;

	// アニメーションリストがあれば再生FPSを算出
	if (m_AnimationList.size())
		m_fCurrentAnimeFPS = (float)(1.0f / (float)m_AnimationList[m_nCurrentAnimeID].Interval);

	// 停止フラグをOFF
	m_bStopFlag = false;
}
//==========================================================================================
//  アニメーションのコピー
//  src : 元となるアニメーションクラス
//==========================================================================================
void cAnimSprite::CopyAnime(const cAnimSprite & src)
{
	m_FrameSize = src.m_FrameSize;
	m_nFrameCols = src.m_nFrameCols;
	m_nFrameRows = src.m_nFrameRows;

	m_AnimationList = src.m_AnimationList;

	m_nCurrentAnimeID = src.m_nCurrentAnimeID;
	m_fCurrentFrame = src.m_fCurrentFrame;
	m_fCurrentAnimeFPS = src.m_fCurrentAnimeFPS;
	m_bStopFlag = src.m_bStopFlag;
	m_fPlaySpeedRate = src.m_fPlaySpeedRate;
}
//==========================================================================================
//  アニメーションの設定(旧FMGB互換関数)
//==========================================================================================
void cAnimSprite::SetAnimation(int Startx, int Starty, int width, int height, short AnimMax, float AnimTime)
{
	m_AnimationList.clear();

	AnimationData data;
	for( int i = 0; i < AnimMax; i++)
		data.Frames.push_back(Startx / width + (Starty / height) * (AnimMax) + i);
	data.Interval = AnimTime;
	data.Loop = true;
	data.Name = "OLDFMGBANIM";

	m_AnimationList.push_back(data);

	m_FrameSize.x = width;
	m_FrameSize.y = height;
	m_nFrameCols = AnimMax;
	m_nFrameRows = 1;

	m_fCurrentFrame = 0.0f;
	m_nCurrentAnimeID = 0;
	m_fCurrentAnimeFPS = (float)(1.0f / (float)m_AnimationList[m_nCurrentAnimeID].Interval);
	m_fPlaySpeedRate = 1.0f;
	m_bStopFlag = false;
}

//=========================================================================
// ASSファイルの読み込みと解析
// filename : assファイルパス
// return : 成功 : true 失敗 : false
//=========================================================================
bool cAnimSprite::LoadASS(const std::string& filename)
{
	// ファイルを開く
	std::ifstream ifs(filename, std::ios::in);

	if (ifs.fail())
	{
#ifdef DEBUG
		cDebugFunc::GetInstance().PushDebugLog("LoadASS Error :" + filename);
#endif
		return false;
	}

	// データの読み込み
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	// ファイルを閉じる
	ifs.close();

	// RapicJSONドキュメント
	rapidjson::Document doc;

	// JSONデータを解析する
	doc.Parse(json.c_str());

	// 構文が正しく解析できたかどうか
	if (doc.HasParseError())
	{
#ifdef DEBUG
		cDebugFunc::GetInstance().PushDebugLog("ASS SyntaxError : " + filename);
#endif
		return false;
	}

	// ファイル名取得
	m_sFileName = doc[m_sKeyName[ASS_KEY_FILE]].GetString();

	// フレームオブジェクト取得
	const rapidjson::Value& frame_object = doc[m_sKeyName[ASS_KEY_FRAME]];

	// フレームの幅
	m_FrameSize.x = frame_object[m_sKeyName[ASS_KEY_WIDTH]].GetInt();

	// フレームの高さ
	m_FrameSize.y = frame_object[m_sKeyName[ASS_KEY_HEIGHT]].GetInt();

	// 横に並んでいるフレーム数
	m_nFrameCols = frame_object[m_sKeyName[ASS_KEY_COLS]].GetInt();

	// 縦に並んでいるフレーム数
	m_nFrameRows = frame_object[m_sKeyName[ASS_KEY_ROWS]].GetInt();

	// アニメーションオブジェクト取得
	const rapidjson::Value& animations_object = doc[m_sKeyName[ASS_KEY_ANIMATIONS]];

	rapidjson::Value::ConstMemberIterator it = animations_object.MemberBegin();
	rapidjson::Value::ConstMemberIterator end = animations_object.MemberEnd();

	while (it != end)
	{
		AnimationData data;

		// 名前を取得
		data.Name = it->name.GetString();

		// フレーム情報などのアニメーションデータ取得
		const rapidjson::Value& animation_data = it->value;

		// アニメーションフレームテーブル取得
		const rapidjson::Value& frames = animation_data[m_sKeyName[ASS_KEY_FRAMES]];

		for (rapidjson::SizeType i = 0; i < frames.Size(); ++i)
			data.Frames.push_back(frames[i].GetInt());

		// 更新間隔取得
		data.Interval = (float)animation_data[m_sKeyName[ASS_KEY_INTERVAL]].GetDouble();

		// ループ設定取得
		data.Loop = animation_data[m_sKeyName[ASS_KEY_LOOP]].GetBool();

		// アニメーションデータリストに追加
		m_AnimationList.push_back(data);

		++it;
	}
	return true;
}