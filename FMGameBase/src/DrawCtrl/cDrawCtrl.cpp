/*==============================================================================*/
/*																				*/
/*	@file title	:	cDrawCtrl.cpp												*/
/*  @brief		:	描画コントロールクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include "cDrawCtrl.h"
#include "..\Utility\memory.h"
#include "..\Utility\utility.h"
#include <algorithm>
#include <DxLib.h>
#pragma warning(disable: 26495)
#include "EffekseerForDXLib.h"
#include "SceneManager/cSceneManager.h"
#include <direct.h>
#include "cGame.h"

#ifdef DEBUG
#include "..\DebugFunc\cDebugFunc.h"
#endif


//==========================================================================================
//  初期化
//==========================================================================================
void cDrawCtrl::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "DrawCtrl";

	IBaseObject::Initialize();
}
//==========================================================================================
//  描画
//==========================================================================================
void cDrawCtrl::Draw(void)
{
	if (m_listDrawObject.empty()) return;

	// 描画優先度変更要求があったら優先度順にソートする
	if (m_bPriChageRequest) m_listDrawObject.sort(CompAscPriority);

	// 各オブジェクトの描画
	for (auto it = m_listDrawObject.begin(); it != m_listDrawObject.end(); it++)
	{
		if ((*it)->GetVisible())
		{
			switch ((*it)->m_eDrawType)
			{
			case DRAWTYPE::SPRITE:
				DrawSprite((cSprite*)(*it));
				break;
			case DRAWTYPE::EFFECT:
				DrawEffect((cEffect*)(*it));
				break;
			case DRAWTYPE::BEGINSURFACE:
				BeginSurface((*it));
				break;
			case DRAWTYPE::SURFACE:
				if (DrawSurface((cSurface*)(*it)))
				{
					// 処理待ちのサーフェイスがあった場合イテレーターを処理中のオブジェクトの場所まで戻す
					if (!m_listSurfaceWait.empty())
					{
						it = std::find(m_listDrawObject.begin(), m_listDrawObject.end(), (*m_listSurfaceWait.begin()));
						BeginSurface(*it);
						m_listSurfaceWait.pop_front();
					}
				}
				break;
			case DRAWTYPE::TRANSITION:
				DrawTransition((cTransition*)(*it));
				break;
			case DRAWTYPE::MODEL:
				DrawModel((cModel*)(*it));
				break;
			case DRAWTYPE::TEXT:
				DrawTextObj((cText*)(*it));
				break;
			}
		}
	}

	if (m_bScreenShot)
	{
		// スクリーンショット保存
		SaveScreenFile();

		// スクリーンショット保存要求をリセット
		m_bScreenShot = false;
	}

	// 変更要求をリセット
	m_bPriChageRequest = false;
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cDrawCtrl::Finalize(void)
{
	IBaseObject::Finalize();

	//------------------------------------------------------------------------------------
	// 描画リストのクリア
	m_listDrawObject.clear();

	//------------------------------------------------------------------------------------
	// 読み込み済み描画ファイルの解放
	if (!m_listFileLoaded.empty())
	{
		// ※フルスクリーン時にエラー落ちする可能性がある為コメントアウト
		/*for (auto it = m_listFileLoaded.begin(); it != m_listFileLoaded.end(); it++)
		{
			if( (*it).Type == DRAW_TYPE_EFFECT) DeleteEffekseerEffect((*it).GraphHandle);
		}*/

		InitGraph();

		m_listFileLoaded.clear();
	}
	return nullptr;
}


//==========================================================================================
//	描画情報の登録(スプライト)
//  obj : 描画情報を設定するスプライトオブジェクト
//  filename : スプライトのリソースファイル名
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cSprite& obj, const std::string& filename)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front((IDrawBase*)&obj);

	// 読み込み済みグラフィックハンドルを設定
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAWTYPE::SPRITE);

	int x = 0, y = 0;
	GetGraphSize(obj.m_nGraphHandle, &x, &y);
	obj.SetCenter(x / 2.0f, y / 2.0f);

	// Rectを設定する
	obj.SetSrcRect(0, 0, x, y);

	// 描画種別をスプライトに設定
	obj.m_eDrawType = DRAWTYPE::SPRITE;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}
//==========================================================================================
//	描画情報の登録(エフェクト)
//  obj : 描画情報を設定するエフェクトオブジェクト
//  filename : エフェクトのリソースファイル名
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cEffect& obj, const std::string& filename)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// 読み込み済みグラフィックハンドルを設定
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAWTYPE::EFFECT);

	// 描画種別をエフェクトに設定
	obj.m_eDrawType = DRAWTYPE::EFFECT;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}
//==========================================================================================
//	描画情報の登録(サーフェイス)
//  obj : 描画情報を設定するサーフェイス
//==========================================================================================
void cDrawCtrl::RegistSurface(cSurface& obj, int width, int height, bool alpha)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// 描画開始ポイントを登録
	m_listDrawObject.push_front(obj.GetBeginPointer());


	// 描画種別をサーフェイスに設定
	obj.m_eDrawType = DRAWTYPE::SURFACE;
	obj.GetBeginPointer()->m_eDrawType = DRAWTYPE::BEGINSURFACE;

	// サーフェイスを作成する
	obj.m_nGraphHandle = MakeScreen(width, height, alpha);
	obj.GetBeginPointer()->m_nGraphHandle = obj.m_nGraphHandle;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}
//==========================================================================================
//	描画情報の登録(トランジション)
//  obj : 描画情報を設定するトランジションオブジェクト
//  filename : ルール画像のリソースファイル名
//==========================================================================================
void cDrawCtrl::RegistTransition(cTransition& obj, const std::string& filename)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// 読み込み済みグラフィックハンドルを設定
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAWTYPE::TRANSITION);

	// 描画種別をトランジションに設定
	obj.m_eDrawType = DRAWTYPE::TRANSITION;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}

//==========================================================================================
//	描画情報の登録(モデル)
//  obj : 描画情報を設定するモデルオブジェクト
//  filename : モデルデータのリソースファイル名
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cModel& obj, const std::string& filename)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// 読み込み済みグラフィックハンドルを設定
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAWTYPE::MODEL);

	// 描画種別をモデルに設定
	obj.m_eDrawType = DRAWTYPE::MODEL;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}
//==========================================================================================
//	描画情報の登録(テキスト)
//  obj : 描画情報を設定するテキストオブジェクト
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cText& obj)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// デフォルトフォントを使用
	obj.m_nGraphHandle = LOADGRAPH_FAILED;

	// 描画種別をモデルに設定
	obj.m_eDrawType = DRAWTYPE::TEXT;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}
//==========================================================================================
//	描画情報の登録(テキスト)
//  obj : 描画情報を設定するテキストオブジェクト
//  以降引数 : CreateFontに必要
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cText& obj, const std::string& fontname, int Size, int Thick, int FontType, int EdgeSize, int Italic)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// フォント生成用の構造体を作成
	FontCreated font;
	font.FontName = fontname;
	font.Size = Size;
	font.Thick = Thick;
	font.FontType = FontType;
	font.EdgeSize = EdgeSize;
	font.Italic = Italic;

	// フォント生成済みでなければ作成
	int handle = SearchSameFont(font);
	if (handle == FONT_NOTFAUND)
	{
		// 乗算済みα用のフォントハンドルを作成する
		SetFontCacheUsePremulAlphaFlag(TRUE);

		font.Handle = CreateFontToHandle(font.FontName.c_str(), font.Size, font.Thick, font.FontType, -1, font.EdgeSize, font.Italic);
		handle = font.Handle;
		m_listFontCreated.push_back(font);
	}

	obj.m_nGraphHandle = handle;

	// 描画種別をモデルに設定
	obj.m_eDrawType = DRAWTYPE::TEXT;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}
//==========================================================================================
//	描画ファイルの読み込み
//  filename : ファイル名
//  type : 描画種別
//  戻り値 : 読み込み済みのグラフィックハンドル
//==========================================================================================
int cDrawCtrl::LoadDrawFile(const std::string& filename, DRAWTYPE type)
{
	if (!m_listFileLoaded.empty())
	{
		for (auto it : m_listFileLoaded)
		{
			// グラフィック読み込み済み
			if (it.FileName == filename) return it.GraphHandle;
		}
	}

	// 新規読み込みファイルをリストに追加する
	FileLoaded load;
	load.FileName = filename;

	load.Type = type;
	switch (type)
	{
	case DRAWTYPE::SPRITE:		load.GraphHandle = LoadGraph(filename.c_str(), FALSE);	break;
	case DRAWTYPE::EFFECT:		load.GraphHandle = LoadEffekseerEffect(filename.c_str());	break;
	case DRAWTYPE::TRANSITION:	load.GraphHandle = LoadBlendGraph(filename.c_str());	break;
	case DRAWTYPE::MODEL:		load.GraphHandle = MV1LoadModel(filename.c_str());	break;
	}
	// グラフィックハンドル読み込み失敗
	if (LOADGRAPH_FAILED == load.GraphHandle)
	{
#ifdef DEBUG
		cDebugFunc::GetInstance().PushDebugLog("LOADGRAPH_FAILED : " + filename);
#endif
		return LOADGRAPH_FAILED;
	}

	// 読み込み済みリストに追加
	m_listFileLoaded.push_back(load);
	return load.GraphHandle;
}

//==========================================================================================
//	描画情報の登録抹消
//  obj : 描画情報を抹消したいオブジェクト自身
//==========================================================================================
void cDrawCtrl::RemoveDrawObject(const IDrawBase* obj)
{
	//---------------------------------------------------------------------
	// m_listDrawObjectからの抹消処理
	for (auto it : m_listDrawObject)
	{
		if (obj == it)
		{
			if (it->m_bUnload)
			{
				// 他に使っているオブジェクトがなければメモリからアンロードする
				if (!SearchSameGrHandle(obj))
				{
					DeleteGraph(obj->m_nGraphHandle);

					// 読み込み済みファイルリストから抹消
					RemoveFileLoaded(obj->m_sFileName);
				}
			}
			it->m_nGraphHandle = LOADGRAPH_FAILED;
			m_listDrawObject.remove(it);
			return;
		}
	}
}
//==========================================================================================
//	サーフェイスの登録抹消
//  obj : 登録を消すサーフェイス自身
//==========================================================================================
void cDrawCtrl::RemoveSurface(const cSurface* obj)
{
	//---------------------------------------------------------------------
	// m_listDrawObjectからの抹消処理
	for (auto it : m_listDrawObject)
	{
		if (obj == it)
		{
			DeleteGraph(it->m_nGraphHandle);
			it->m_nGraphHandle = LOADGRAPH_FAILED;
			RemoveDrawObject(((cSurface*)it)->GetBeginPointer());
			m_listDrawObject.remove(it);
			return;
		}
	}
}

//==========================================================================================
// テキストの文字幅を取得する
//==========================================================================================
int cDrawCtrl::GetTextWidth(cText* obj)
{
	// デフォルトフォントの場合
	if (obj->m_nGraphHandle == FONT_NOTFAUND)
	{
		return GetDrawStringWidth(obj->GetText().c_str(), (int)obj->GetText().length());
	}
	// 作成済みフォントの場合
	else
	{
		return GetDrawStringWidthToHandle(obj->GetText().c_str(), (int)obj->GetText().length(), obj->m_nGraphHandle);
	}
}

//==========================================================================================
//	スプライトの描画
//==========================================================================================
void cDrawCtrl::DrawSprite(cSprite* obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		SetDrawBlendMode(obj->GetBlendMode(), obj->GetAlpha());
		RECT rect = obj->GetSrcRect();

		unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
		// 色の設定
		SetDrawBright(red, green, blue);
		// 回転拡縮Rectを加味した描画
		DrawRectRotaGraph3F(round(obj->GetPos().x), round(obj->GetPos().y), rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
			round(obj->GetCenter().x + obj->GetAnchor().x), round(obj->GetCenter().y + obj->GetAnchor().y), obj->GetScale().x, obj->GetScale().y, DEG_TO_RAD(obj->GetAngle()), obj->m_nGraphHandle,
			TRUE);
	}
}

//==========================================================================================
//	エフェクトの描画
//==========================================================================================
void cDrawCtrl::DrawEffect(cEffect* obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		if (obj->m_nPlayingEffectHandle != EFFEKSEER_NOTPLAYING)
		{
			// シーンIDが一致しない場合にはエフェクトを一時停止する
			if (obj->m_ePlayScene != SCENE_ID::NONE && obj->m_ePlayScene != cSceneManager::GetInstance().GetStackSceneID())
			{
				SetSpeedPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, 0.0f);
			}
			else
			{
				SetSpeedPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, 1.0f);
			}
			// 再生終了又は停止フラグが立っていた場合
			if (IsEffekseer2DEffectPlaying(obj->m_nPlayingEffectHandle) == EFFEKSEER_NOTPLAYING ||
				obj->m_bStop)
			{
				StopEffekseer2DEffect(obj->m_nPlayingEffectHandle);
				if (!obj->IsLoop())
				{
					return;
				}
				else {

					// ループ設定のエフェクトだったら再度再生
					obj->m_nPlayingEffectHandle = PlayEffekseer2DEffect(obj->m_nGraphHandle);
				}
			}
		}
		else
		{
			// エフェクトの再生開始
			obj->m_nPlayingEffectHandle = PlayEffekseer2DEffect(obj->m_nGraphHandle);
		}
		SetScalePlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vScale.x, obj->m_vScale.y, obj->m_vScale.z);
		SetPosPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vPos.x, obj->m_vPos.y, 0);
		SetRotationPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vAngle.x, obj->m_vAngle.y, obj->m_vAngle.z);

		unsigned int alpha = (obj->GetDrawColor() & 0xff000000) >> 24;
		unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor() & 0x000000ff);

		SetColorPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, red, green, blue, alpha);

		// エフェクトを描画する
		DrawEffekseer2D_Begin();
		DrawEffekseer2D_Draw(obj->m_nPlayingEffectHandle);
		DrawEffekseer2D_End();
	}
}
//==========================================================================================
//	サーフェイスの描画
//==========================================================================================
bool cDrawCtrl::DrawSurface(cSurface* obj)
{
	// 対象外のサーフェイスは一旦飛ばす
	if (m_pBeginSurface != obj->GetBeginPointer()) return false;

	// レンダーターゲットをバックバッファに戻す
	SetDrawScreen(DX_SCREEN_BACK);

	RECT rect = obj->GetRect();
	SetDrawBlendMode(obj->GetBlendMode(), obj->GetAlpha());

	unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
	unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
	unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
	// 色の設定
	SetDrawBright(red, green, blue);

	// フィルターの設定
	switch (obj->GetFilterMode())
	{
	case cSurface::FILTER_MODE::MONO: GraphFilter(obj->m_nGraphHandle, DX_GRAPH_FILTER_MONO, obj->GetMonoBlue(), obj->GetMonoRed()); break;
	case cSurface::FILTER_MODE::GAUSS: GraphFilter(obj->m_nGraphHandle, DX_GRAPH_FILTER_GAUSS, obj->GetGaussPixelWidth(), obj->GetGaussParam()); break;
	case cSurface::FILTER_MODE::HSB: GraphFilter(obj->m_nGraphHandle, DX_GRAPH_FILTER_HSB, 0, obj->GetHSBHue(), obj->GetHSBSaturation(), obj->GetHSBBright()); break;
	case cSurface::FILTER_MODE::INVERT: GraphFilter(obj->m_nGraphHandle, DX_GRAPH_FILTER_INVERT); break;
	default: break;
	}

	// 表示フラグが立っている時のみ表示する
	if (obj->IsShow())
	{
		// サーフェイスの内容を描画
		DrawRectRotaGraph3F(obj->GetPos().x, obj->GetPos().y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
			obj->GetCenter().x, obj->GetCenter().y, obj->GetScale().x, obj->GetScale().y, DEG_TO_RAD(obj->GetAngle()), obj->m_nGraphHandle,
			TRUE);
	}
	// 処理中のサーフェイスポインタを初期化
	m_pBeginSurface = nullptr;

	return true;
}
//==========================================================================================
//	サーフェイスの描画開始
//==========================================================================================
void cDrawCtrl::BeginSurface(IDrawBase* obj)
{
	if (obj->IsFileLoaded())
	{
		// 処理中サーフェイスがあった場合にはサーフェイスを処理待ちにする
		if (m_pBeginSurface)
		{
			// 未登録のサーフェイスの場合は処理待ちリストに追加する
			if (m_listSurfaceWait.end() == std::find(m_listSurfaceWait.begin(), m_listSurfaceWait.end(), obj))
				m_listSurfaceWait.push_back(obj);
			return;
		}

		m_pBeginSurface = obj;
		// レンダーターゲットをサーフェイスにする
		SetDrawScreen(obj->m_nGraphHandle);
		ClearDrawScreen();
	}
}
//==========================================================================================
//	トランジションの描画
//==========================================================================================
void cDrawCtrl::DrawTransition(cTransition* obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		// トランジションはブレンドモードを設定しない
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
		// 色の設定
		SetDrawBright(red, green, blue);

		// 描画
		DrawBlendGraph((int)obj->m_vPos.x, (int)obj->m_vPos.y, obj->GetTransObject()->m_nGraphHandle, TRUE, obj->m_nGraphHandle, (int)obj->GetBorderParam(), (int)obj->GetBorderRange());
	}
}
//==========================================================================================
//	モデルの描画
//==========================================================================================
void cDrawCtrl::DrawModel(cModel* obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		// モデルの描画
		MV1DrawModel(obj->m_nGraphHandle);
	}
}
//==========================================================================================
//	テキストの描画
//==========================================================================================
void cDrawCtrl::DrawTextObj(cText* obj)
{
	// テキストはAlphaブレンドモードに変更
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, obj->GetAlpha());

	unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
	unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
	unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
	// 色の設定
	SetDrawBright(red, green, blue);

	if (obj->m_nGraphHandle == LOADGRAPH_FAILED)
	{
		// 標準文字描画
		DrawStringF(obj->GetPos().x, obj->GetPos().y, obj->GetText().c_str(), obj->GetDrawColor());
	}
	else
	{
		// フォントハンドルを用いた描画
		DrawStringToHandle((int)obj->GetPos().x, (int)obj->GetPos().y, obj->GetText().c_str(), obj->GetDrawColor(), obj->m_nGraphHandle, obj->GetEdgeColor(), obj->GetVerticalFlag());
	}
}
//==========================================================================================
// 同じグラフィックハンドルを持つオブジェクトがあるかを探す
// 戻り値 : true 見つかった false 見つからなかった
//==========================================================================================
bool cDrawCtrl::SearchSameGrHandle(const IDrawBase* obj)
{
	for (auto it : m_listDrawObject)
	{
		if (obj != it)
		{
			if (obj->m_nGraphHandle == it->m_nGraphHandle) return true;
		}
	}
	return false;
}
//==========================================================================================
// 生成済みの同フォントがあるかを探す
// 戻り値 : -1 同じフォントが見つからなかった -1以外 フォントハンドル
//==========================================================================================
int cDrawCtrl::SearchSameFont(FontCreated& font)
{
	for (auto it : m_listFontCreated)
	{
		if (font.FontName == it.FontName &&
			font.Size == it.Size &&
			font.Thick == it.Thick &&
			font.FontType == it.FontType &&
			font.EdgeSize == it.EdgeSize &&
			font.Italic == it.Italic)
		{
			return it.Handle;
		}
	}
	return FONT_NOTFAUND;
}
//==========================================================================================
// 読み込み済みファイルリストから抹消する
// filename : 抹消するファイル名
//==========================================================================================
void cDrawCtrl::RemoveFileLoaded(std::string filename)
{
	// アンロードしたら読み込み済みリストから抹消
	if (!m_listFileLoaded.empty())
	{
		auto end = m_listFileLoaded.end();
		auto it = m_listFileLoaded.begin();
		while (it != end)
		{
			// ロード済みのファイルを抹消する
			if ((*it).FileName == filename)
			{
				m_listFileLoaded.erase(it);
				return;
			}
			it++;
		}
	}
}

//==========================================================================================
// スクリーンショット保存
//==========================================================================================
void cDrawCtrl::SaveScreenFile(void)
{
	// スクリーンショット要求があれば保存する
	DATEDATA date;
	GetDateTime(&date);
	if (_mkdir("ScreenShot") != 0) return;
	// 年以外は０埋めしておく
	char mon[8], day[8], hour[8], min[8], sec[8];
	sprintf_s(mon, 8, "%02d", date.Mon);
	sprintf_s(day, 8, "%02d", date.Day);
	sprintf_s(hour, 8, "%02d", date.Hour);
	sprintf_s(min, 8, "%02d", date.Min);
	sprintf_s(sec, 8, "%02d", date.Sec);
	// スクリーンショットを日付のファイル名にする
	std::string datestr = "ScreenShot\\" + std::to_string(date.Year) + mon + day + hour + min + sec + ".png";

	SaveDrawScreenToPNG(0, 0, cGame::GetInstance().GetWindowWidth(), cGame::GetInstance().GetWindowHeight(), datestr.c_str(), 0);
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cDrawCtrl::cDrawCtrl(void) :
	m_bPriChageRequest(false),
	m_bScreenShot(false),
	m_pBeginSurface(nullptr)
{
	m_listFileLoaded.clear();
	m_listDrawObject.clear();
	m_listFontCreated.clear();
	m_listSurfaceWait.clear();
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cDrawCtrl::cDrawCtrl(IBaseObject* parent) :
	cDrawCtrl::cDrawCtrl()
{
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cDrawCtrl::cDrawCtrl(IBaseObject* parent, const std::string& name) :
	cDrawCtrl::cDrawCtrl(parent)
{
}

//==========================================================================================
// コピーコンストラクタ
//==========================================================================================
cDrawCtrl::cDrawCtrl(const cDrawCtrl& t) :
	cDrawCtrl::cDrawCtrl()
{
}
