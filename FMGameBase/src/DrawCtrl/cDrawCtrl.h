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
#include "Surface/cSurface.h"
#include "Transition\cTransition.h"
#include "Model/cModel.h"
#include "../BaseObject/IBaseObject.h"
#include <list>
#include "Text/cText.h"

//===============================================================================
// 描画コントロールクラス
class cDrawCtrl : public IBaseObject
{
public:
	void Initialize(void);
	void Draw(void);
	IBaseObject* Finalize(void);

	// 描画オブジェクトの登録
	void RegistDrawObject(cSprite& obj, const std::string& filename);

	// 描画オブジェクトの登録
	void RegistDrawObject(cEffect& obj, const std::string& filename);

	// サーフェイスの登録
	void RegistSurface(cSurface& obj, int width, int height, bool alpha);

	// トランジションの登録
	void RegistTransition(cTransition& obj, const std::string& filename);

	// モデルの登録
	void RegistDrawObject(cModel& obj, const std::string& filename);

	// テキストの登録
	void RegistDrawObject(cText& obj);

	// テキストの登録(フォント生成あり)
	void RegistDrawObject(cText& obj, const std::string& fontname, int Size, int Thick, int FontType, int EdgeSize, int Italic);

	// 描画ファイル読込処理
	// 戻り値 : グラフィックハンドル
	int LoadDrawFile(const std::string& filename, DRAWTYPE type);

	// 描画オブジェクトの登録抹消
	void RemoveDrawObject(const IDrawBase* obj);

	// サーフェイスの登録抹消
	void RemoveSurface(const cSurface* obj);

	// テキストの文字幅を取得する
	int GetTextWidth(cText* obj);

	// 描画リストのクリア
	inline void ClearDrawList(void) { m_listDrawObject.clear(); m_listFileLoaded.clear(); };

	// 描画優先変更要求
	inline void RequestChangeDrawPriority(void) { m_bPriChageRequest = true; };

	// スクリーンショットの撮影要求
	inline void RequestScreenShot(void) { m_bScreenShot = true; };

private:
	// スプライトの描画
	void DrawSprite(cSprite* obj);
	// エフェクトの描画
	void DrawEffect(cEffect* obj);
	// サーフェイスの描画
	// ret : サーフェイス描画成功 : true
	bool DrawSurface(cSurface* obj);
	// サーフェイスの描画開始
	void BeginSurface(IDrawBase* obj);
	// トランジションの描画
	void DrawTransition(cTransition* obj);
	// モデルの描画
	void DrawModel(cModel* obj);
	// テキストの描画
	void DrawTextObj(cText* obj);

	//--------------------------------------------------------------------------------------
	// リストの昇順比較関数
	// DrawObjectの表示優先が低いものから先に描画をする
	// staticをつけないとstdが非インスタンスで呼びたい為エラーが出る
	static bool CompAscPriority(IDrawBase* left, IDrawBase* right) { return left->GetPriority() < right->GetPriority(); };

	//--------------------------------------------------------------------------------------
	// 同じグラフィックハンドルを持つオブジェクトがあるかを探す
	// 戻り値 : true 見つかった false 見つからなかった
	bool SearchSameGrHandle(const IDrawBase* obj);

	// 生成済フォント構造体
	struct FontCreated
	{
		std::string	FontName;
		int			Size = 30;
		int			Thick = 0;
		int			FontType = 0;
		int			EdgeSize = 0;
		int			Italic = 0;
		int			Handle = -1;		// 生成済みフォントハンドル
	};

	//--------------------------------------------------------------------------------------
	// 同じフォントが生成済みかを探す
	// 戻り値 : -1 同じフォントが見つからなかった -1以外 フォントハンドル
	int SearchSameFont(FontCreated& font);

	//--------------------------------------------------------------------------------------
	// 読み込み済みファイルから抹消
	void RemoveFileLoaded(std::string filename);

	//--------------------------------------------------------------------------------------
	// スクリーンショット保存
	void SaveScreenFile(void);

	//--------------------------------------------------------------------------------------
	// ファイル読み込み関連
	// 読み込みファイル構造体
	struct FileLoaded
	{
		std::string FileName;
		int GraphHandle = -1;
		DRAWTYPE Type = DRAWTYPE::SPRITE;
	};
	// 読み込み済みファイルリスト
	std::list<FileLoaded> m_listFileLoaded;

	//--------------------------------------------------------------------------------------
	// 描画オブジェクトリスト
	std::list<IDrawBase*> m_listDrawObject;

	// 描画優先変更要求
	bool m_bPriChageRequest;

	// スクリーンショット保存要求
	bool m_bScreenShot;


	// 生成済みフォントリスト
	std::list<FontCreated> m_listFontCreated;

	// 処理中サーフェイスポインタ
	IDrawBase* m_pBeginSurface;
	// サーフェイス処理待ちリスト
	std::list<IDrawBase*> m_listSurfaceWait;

	//--------------------------------------------------------------------------------------
	// 定数
	const int LOADGRAPH_FAILED = -1;		 // 画像読込失敗
	const int FONT_NOTFAUND = -1;			 // フォントが見つからない
	const int EFFEKSEER_NOTPLAYING = -1;	 // エフェクト未再生

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cDrawCtrl(void);     //  他からの生成を禁止
	cDrawCtrl(IBaseObject* parent);
	cDrawCtrl(IBaseObject* parent, const std::string& name);
	~cDrawCtrl(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cDrawCtrl(const cDrawCtrl& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cDrawCtrl& operator = (const cDrawCtrl& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:

	static cDrawCtrl& GetInstance(void) {
		static cDrawCtrl instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};