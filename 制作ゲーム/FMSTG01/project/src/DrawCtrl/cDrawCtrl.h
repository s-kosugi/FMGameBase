#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDrawCtrl.h													*/
/*  @brief		:	描画コントロールクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include "IDrawBase.h"
#include "Sprite\cSprite.h"
#include "Effect\cEffect.h"
#include "Surface/cSurFace.h"
#include "Transition\cTransition.h"
#include "../BaseObject/IBaseSingleton.h"
#include <list>
#include "Surface\cSurFace.h"

//===============================================================================
// 描画コントロールクラス
class cDrawCtrl : public IBaseSingleton<cDrawCtrl>
{
public:
	~cDrawCtrl();

	void Initialize(void);
	void Draw(void);
	IBaseObject* Finalize(void);

	// 描画オブジェクトの登録
	void RegistDrawObject(cSprite& obj,const std::string& filename);

	// 描画オブジェクトの登録
	void RegistDrawObject(cEffect& obj, const std::string& filename);

	// サーフェイスの登録
	void RegistSurface(cSurface& obj,int width,int height,bool alpha);

	// トランジションの登録
	void RegistTransition(cTransition& obj, const std::string& filename);

	// 描画ファイル読込処理
	// 戻り値 : グラフィックハンドル
	int LoadDrawFile(const std::string& filename, DrawType type);

	// 描画オブジェクトの登録抹消
	void RemoveDrawObject(const IDrawBase* obj);

	// サーフェイスの登録抹消
	void RemoveSurface(const cSurface* obj);

	// 描画リストのクリア
	inline void ClearDrawList(void) { m_listDrawObject.clear(); m_listFileLoaded.clear();};

	// 描画優先変更要求
	inline void RequestChangeDrawPriority(void) { m_bPriChageRequest = true;};
private:
	// スプライトの描画
	void DrawSprite(cSprite* obj);
	// エフェクトの描画
	void DrawEffect(cEffect* obj);
	// サーフェイスの描画
	void DrawSurface(cSurface* obj);
	// サーフェイスの描画開始
	void BeginSurface(IDrawBase* obj);
	// トランジションの描画
	void DrawTransition(cTransition* obj);

	//--------------------------------------------------------------------------------------
	// リストの昇順比較関数
	// DrawObjectの表示優先が低いものから先に描画をする
	// staticをつけないとstdが非インスタンスで呼びたい為エラーが出る
	static bool CompAscPriority(IDrawBase* left, IDrawBase* right) { return left->GetPriority() < right->GetPriority(); };

	//--------------------------------------------------------------------------------------
	// 同じグラフィックハンドルを持つオブジェクトがあるかを探す
	// 戻り値 : true 見つかった false 見つからなかった
	bool SearchSameGrHandle( const IDrawBase* obj );

	//--------------------------------------------------------------------------------------
	// 読み込み済みファイルから抹消
	void RemoveFileLoaded( std::string filename );

	//--------------------------------------------------------------------------------------
	// ファイル読み込み関連
	// 読み込みファイル構造体
	struct FileLoaded
	{
		std::string FileName;
		int GraphHandle;
		DrawType Type;
	};
	// 読み込み済みファイルリスト
	std::list<FileLoaded> m_listFileLoaded;

	//--------------------------------------------------------------------------------------
	// 描画オブジェクトリスト
	std::list<IDrawBase*> m_listDrawObject;

	// 描画優先変更要求
	bool m_bPriChageRequest;

	//--------------------------------------------------------------------------------------
	// 定数
	const int LOADGRAPH_FAILED = -1;		 // 画像読込失敗
};