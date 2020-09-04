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
#include "EffekseerForDXLib.h"

cDrawCtrl::~cDrawCtrl()
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void cDrawCtrl::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "DrawCtrl";

	m_bPriChageRequest = false;

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

	std::list<IDrawBase*>::iterator it = m_listDrawObject.begin();
	std::list<IDrawBase*>::iterator end = m_listDrawObject.end();

	while (it != end)
	{
		if ((*it)->GetVisible())
		{
			switch ((*it)->m_eDrawType)
			{
			case DRAW_TYPE_SPRITE:
				DrawSprite((cSprite*)(*it));
				break;
			case DRAW_TYPE_EFFECT:
				DrawEffect((cEffect*)(*it));
				break;
			case DRAW_TYPE_BEGINSURFACE:
				BeginSurface(*it);
				break;
			case DRAW_TYPE_SURFACE:
				DrawSurface((cSurface*)(*it));
				break;
			case DRAW_TYPE_TRANSITION:
				DrawTransition((cTransition*)(*it));
				break;
			}
		}
		it++;
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
		InitGraph();

		for (auto it = m_listFileLoaded.begin(); it != m_listFileLoaded.end(); it++)
		{
			if( (*it).Type == DRAW_TYPE_EFFECT) DeleteEffekseerEffect((*it).GraphHandle);
		}

		m_listFileLoaded.clear();
	}
	return nullptr;
}


//==========================================================================================
//	描画情報の登録(スプライト)
//  obj : 描画情報を設定するスプライトオブジェクト
//  filename : スプライトのリソースファイル名
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cSprite& obj,const std::string& filename)
{
	if(obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front((IDrawBase*)&obj);

	// 読み込み済みグラフィックハンドルを設定
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAW_TYPE_SPRITE);

	int x = 0,y = 0;
	GetGraphSize(obj.m_nGraphHandle,&x,&y);
	obj.SetCenter(x/2.0f,y/2.0f);
	// Rectを設定する
	obj.SetSrcRect(0,0,x,y);

	// 描画種別をスプライトに設定
	obj.m_eDrawType = DRAW_TYPE_SPRITE;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}
//==========================================================================================
//	描画情報の登録(エフェクト)
//  obj : 描画情報を設定するエフェクトオブジェクト
//  filename : エフェクトのリソースファイル名
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cEffect & obj, const std::string & filename)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// 読み込み済みグラフィックハンドルを設定
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAW_TYPE_EFFECT);

	// 描画種別をエフェクトに設定
	obj.m_eDrawType = DRAW_TYPE_EFFECT;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}

//==========================================================================================
//	描画情報の登録(サーフェイス)
//  obj : 描画情報を設定するサーフェイス
//==========================================================================================
void cDrawCtrl::RegistSurface(cSurface & obj,int width , int height ,bool alpha)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// 描画開始ポイントを登録
	m_listDrawObject.push_front(obj.GetBeginPointer());


	// 描画種別をサーフェイスに設定
	obj.m_eDrawType = DRAW_TYPE_SURFACE;
	obj.GetBeginPointer()->m_eDrawType = DRAW_TYPE_BEGINSURFACE;

	// 描画対象にできるグラフィックを作成する。
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
void cDrawCtrl::RegistTransition(cTransition & obj, const std::string & filename)
{
	if (obj.IsFileLoaded()) return;

	// 描画オブジェクトの登録
	m_listDrawObject.push_front(&obj);

	// 読み込み済みグラフィックハンドルを設定
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAW_TYPE_TRANSITION);

	// 描画種別をトランジションに設定
	obj.m_eDrawType = DRAW_TYPE_TRANSITION;

	// 描画順の変更要求をする
	m_bPriChageRequest = true;
}

//==========================================================================================
//	描画ファイルの読み込み
//  filename : ファイル名
//  type : 描画種別
//  戻り値 : 読み込み済みのグラフィックハンドル
//==========================================================================================
int cDrawCtrl::LoadDrawFile(const std::string & filename, DrawType type)
{
	if (!m_listFileLoaded.empty())
	{
		std::list<FileLoaded>::iterator end = m_listFileLoaded.end();
		std::list<FileLoaded>::iterator it = m_listFileLoaded.begin();
		while (it != end)
		{
			// ロード済みのファイルは読み込みしない
			if ((*it).FileName == filename) return (*it).GraphHandle;

			it++;
		}
	}
	// 新規読み込みファイルをリストに追加する
	FileLoaded load;
	load.FileName = filename;
	load.Type = type;
	switch (type)
	{
	case DRAW_TYPE_SPRITE:		load.GraphHandle = LoadGraph(filename.c_str(), FALSE);
		break;
	case DRAW_TYPE_EFFECT:		load.GraphHandle = LoadEffekseerEffect(filename.c_str());
		break;
	case DRAW_TYPE_TRANSITION:	load.GraphHandle = LoadBlendGraph(filename.c_str());
		break;
	}
	// グラフィックハンドル読み込み失敗
	if (LOADGRAPH_FAILED == load.GraphHandle)
		return LOADGRAPH_FAILED;

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
	std::list<IDrawBase*>::iterator it = m_listDrawObject.begin();
	std::list<IDrawBase*>::iterator end = m_listDrawObject.end();

	while (it != end)
	{
		if (obj == (*it))
		{
			if ((*it)->m_bUnload)
			{
				// 他に使っているオブジェクトがなければメモリからアンロードする
				if (!SearchSameGrHandle(obj))
				{
					DeleteGraph(obj->m_nGraphHandle);

					// 読み込み済みファイルリストから抹消
					RemoveFileLoaded(obj->m_sFileName);
				}
			}
			(*it)->m_nGraphHandle = LOADGRAPH_FAILED;
			m_listDrawObject.remove(*it);
			return;
		}

		it++;
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
	std::list<IDrawBase*>::iterator it = m_listDrawObject.begin();
	std::list<IDrawBase*>::iterator end = m_listDrawObject.end();

	while (it != end)
	{
		if (obj == (*it))
		{
			DeleteGraph((*it)->m_nGraphHandle);
			(*it)->m_nGraphHandle = LOADGRAPH_FAILED;
			RemoveDrawObject(((cSurface*)*it)->GetBeginPointer());
			m_listDrawObject.remove(*it);
			return;
		}

		it++;
	}
}

//==========================================================================================
//	スプライトの描画
//==========================================================================================
void cDrawCtrl::DrawSprite(cSprite * obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		SetDrawBlendMode(obj->GetBlendMode(), obj->GetAlpha());
		RECT rect = obj->GetSrcRect();

		unsigned int red = (obj->GetDrawColor()   & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor()  & 0x000000ff);
		// 色の設定
		SetDrawBright(red, green, blue);
		switch (obj->GetSpriteType())
		{
		case cSprite::SPTYPE_NORMAL:
			// 回転拡縮Rectを加味した描画
			DrawRectRotaGraph3F(obj->GetPos().x, obj->GetPos().y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
				obj->GetCenter().x, obj->GetCenter().y, obj->GetScale().x, obj->GetScale().y, DEG_TO_RAD(obj->GetAngle()), obj->m_nGraphHandle,
				TRUE);
			break;
		case cSprite::SPTYPE_CIRCLEGAUGE:
			DrawCircleGauge((int)obj->GetPos().x, (int)obj->GetPos().y, obj->GetEndAngle(), obj->m_nGraphHandle, obj->GetStartAngle());
			break;
		}
	}
}

//==========================================================================================
//	エフェクトの描画
//==========================================================================================
void cDrawCtrl::DrawEffect(cEffect * obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		if (obj->m_nPlayingEffectHandle != -1)
		{
			// 再生終了
			if (IsEffekseer2DEffectPlaying(obj->m_nPlayingEffectHandle) == -1)
			{
				StopEffekseer2DEffect(obj->m_nPlayingEffectHandle);
				return;
			}
		} else
		{
			// エフェクトの再生開始
			obj->m_nPlayingEffectHandle = PlayEffekseer2DEffect(obj->m_nGraphHandle);
		}
		SetScalePlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vScale.x, obj->m_vScale.y, obj->m_vScale.z);
		SetPosPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vPos.x, obj->m_vPos.y, 0);
		SetRotationPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vAngle.x, obj->m_vAngle.y, obj->m_vAngle.z);

		unsigned int alpha = (obj->GetDrawColor() & 0xff000000) >> 24;
		unsigned int red = (obj->GetDrawColor()   & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor()  & 0x000000ff);

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
void cDrawCtrl::DrawSurface(cSurface * obj)
{
	// レンダーターゲットをバックバッファに戻す
	SetDrawScreen(DX_SCREEN_BACK);

	RECT rect = obj->GetRect();
	SetDrawBlendMode(obj->GetBlendMode(), obj->GetAlpha());

	unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
	unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
	unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
	// 色の設定
	SetDrawBright(red, green, blue);

	// サーフェイスの内容を描画
	DrawRectRotaGraph3F(obj->GetPos().x, obj->GetPos().y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		obj->GetCenter().x, obj->GetCenter().y, obj->GetScale().x, obj->GetScale().y, DEG_TO_RAD(obj->GetAngle().x), obj->m_nGraphHandle,
		TRUE);
}
//==========================================================================================
//	サーフェイスの描画開始
//==========================================================================================
void cDrawCtrl::BeginSurface(IDrawBase * obj)
{
	if (obj->IsFileLoaded())
	{
		// レンダーターゲットをサーフェイスにする
		SetDrawScreen(obj->m_nGraphHandle);
		ClearDrawScreen();
	}
}
//==========================================================================================
//	トランジションの描画
//==========================================================================================
void cDrawCtrl::DrawTransition(cTransition * obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{

		unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
		// 色の設定
		SetDrawBright(red, green, blue);
		
		// 描画
		int ret = DrawBlendGraph(0, 0, obj->GetTransObject()->m_nGraphHandle, TRUE, obj->m_nGraphHandle, (int)obj->GetBorderParam(), (int)obj->GetBorderRange());
	}
}
//==========================================================================================
// 同じグラフィックハンドルを持つオブジェクトがあるかを探す
// 戻り値 : true 見つかった false 見つからなかった
//==========================================================================================
bool cDrawCtrl::SearchSameGrHandle(const IDrawBase * obj)
{
	auto it = m_listDrawObject.begin();
	auto end = m_listDrawObject.end();
	while (it != end)
	{
		if (obj != (*it))
		{
			if(obj->m_nGraphHandle == (*it)->m_nGraphHandle) return true;
		}
		it++;
	}

	return false;
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
		std::list<FileLoaded>::iterator end = m_listFileLoaded.end();
		std::list<FileLoaded>::iterator it = m_listFileLoaded.begin();
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