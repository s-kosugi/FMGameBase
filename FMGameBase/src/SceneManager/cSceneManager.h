#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSceneManager.h												*/
/*  @brief		:	シーン管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"
#include "SceneID.h"
#include "..\DrawCtrl\Transition\cTransition.h"
#include "Scene/IBaseScene.h"

//===============================================================================
// シーン管理クラス
class cSceneManager : public IBaseObject
{
public:
	void Initialize(void);
	void Update(void);

	// シーン変更演出タイプ
	enum class CHANGE_TYPE
	{
		NOFADE,			// フェード無し
		FADE,			// フェード
		UNITRANS,		// ユニバーサルトランジション
	};

	// シーン変更
	void ChangeScene(SCENE_ID id, CHANGE_TYPE type = CHANGE_TYPE::FADE);
	// シーン変更(ユニバーサルトランジション)
	void ChangeSceneUniTrans(SCENE_ID id, std::string ruleFilename);


	// 現在シーンの取得
	inline SCENE_ID GetCurrentSceneID(void) { return m_eCurrentScene; };
	// スタックしているシーンを取得(最後尾)
	SCENE_ID GetStackSceneID(void);

	// フェードアウトタイプの変更
	inline void SetFadeOutType(CHANGE_TYPE type) { m_eChangeOutType = type; };
	// フェードインタイプの変更
	inline void SetFadeInType(CHANGE_TYPE type) { m_eChangeInType = type; };
	// フェードアウト時間の変更
	inline void SetFadeOutTime(float time) { m_nFadeOutTime = time; };
	// フェードイン時間の変更
	inline void SetFadeInTime(float time) { m_nFadeInTime = time; };
	// フェードアウトトランジションファイルの変更
	inline void SetFadeOutTrans(std::string filename) { m_sTransOutFileName = filename; };
	// フェードイントランジションファイルの変更
	inline void SetFadeInTrans(std::string filename) { m_sTransInFileName = filename; };

	// シーンスタック関連
	void		PushScene(SCENE_ID id);
	void		PopScene(void);

	// 現在のシーンをリセットする
	void Reset(CHANGE_TYPE changeType = CHANGE_TYPE::NOFADE);

private:

	// シーン生成
	IBaseScene* CreateScene(SCENE_ID id);

	// フェードアウト前準備
	void PrepareFadeOut(void);

	//------------------------------------------------------------------------------
	// シーン状態別処理
	void FadeIn(void);
	void UpdateScene(void);
	void FadeOut(void);
	void TransitionScene(void);
	//------------------------------------------------------------------------------

	enum class STATE
	{
		FADEIN,		// フェードイン
		UPDATE,		// シーン更新
		FADEOUT,	// フェードアウト
		TRANSITION,	// シーン遷移
	};

	SCENE_ID		m_eCurrentScene;		// シーンID
	SCENE_ID		m_eNextScene;			// 次シーンID
	STATE			m_eState;				// シーン状態
	CHANGE_TYPE		m_eChangeOutType;		// シーン変更(フェードアウト)演出タイプ
	CHANGE_TYPE		m_eChangeInType;		// シーン変更(フェードイン)演出タイプ
	cTransition* m_pTransObj;			// トランジションクラス
	std::string		m_sTransOutFileName;	// ルール画像(フェードアウト)ファイル名
	std::string		m_sTransInFileName;		// ルール画像(フェードアウト)ファイル名
	float			m_nFadeInTime;			// フェードイン時間
	float			m_nFadeOutTime;			// フェードアウト時間
	SCENE_ID		m_ePushSceneID;			// プッシュするシーンID
	bool			m_bPush;				// シーンのプッシュが行われたかどうか
	short			m_nStackCount;			// シーンスタックされている数をカウントする

	//------------------------------------------------------------------------------
	// 定数
	// 初期フェード秒数
	static const float    DEFAULT_FADE_TIME;

	//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cSceneManager(void);     //  他からの生成を禁止
	cSceneManager(IBaseObject* parent);
	cSceneManager(IBaseObject* parent, const std::string& name);
	~cSceneManager(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cSceneManager(const cSceneManager& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cSceneManager& operator = (const cSceneManager& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cSceneManager& GetInstance(void) {
		static cSceneManager instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};