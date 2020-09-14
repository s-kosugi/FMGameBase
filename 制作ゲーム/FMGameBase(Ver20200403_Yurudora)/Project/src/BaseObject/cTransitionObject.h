#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransitionObject.h											*/
/*  @brief		:	トランジションオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/02/12													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"
#include "..\DrawCtrl\Transition\cTransition.h"
#include "..\DrawCtrl\Sprite\cSprite.h"

//================================================================================================
// 描画オブジェクト
// １クラスにつき１つのスプライトを持ちたい場合に使用する。
class cTransitionObject : public IBaseObject, public cTransition
{
public:

	//---------------------------------------------
	// コンストラクタ
	// parent : 親オブジェクト
	// name : オブジェクト名
	// ruleFIlename : ルール画像ファイル名
	// spriteFileName : スプライト画像のファイル名
	// dir : トランジション方向
	// transtime : トランジション時間
	cTransitionObject(IBaseObject* parent, const std::string& objectname, const std::string& ruleFilename, const std::string& spriteFileName, TransDirection dir,float transtime);
	//---------------------------------------------
	// コンストラクタ
	// parent : 親オブジェクト
	// name : オブジェクト名
	// ruleFIlename : ルール画像ファイル名
	// transObj : 遷移先オブジェクト
	// dir : トランジション方向
	// transtime : トランジション時間
	cTransitionObject(IBaseObject* parent, const std::string& objectname, const std::string& ruleFilename, IDrawBase* pTransObj, TransDirection dir, float transtime);

	~cTransitionObject(void);


	virtual void Initialize(void);
	virtual void Initialize( const cVector2& pos );
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

private:
	cSprite* m_pSprite;			// 画像クラスへのポインタ
};
//================================================================================================

//================================================================================================
// オブジェクト生成関数
//================================================================================================
// トランジションオブジェクト生成
// 親オブジェクトとオブジェクトとトランジションに必要な項目を指定する。
// parent : 親オブジェクト
// name : オブジェクト名
// ruleFIlename : ルール画像ファイル名
// spriteFileName : スプライト画像のファイル名
// dir : トランジション方向
// transtime : トランジション時間(秒)
// return : 生成したオブジェクト
template <class T> T* CreateTransitionObject(IBaseObject* parent, const std::string& name, const std::string& ruleFilename, const std::string& spriteFileName, cTransition::TransDirection dir, float transtime)
{
	// ゲームオブジェクト生成
	T* t = NEW T(parent, name, ruleFilename, spriteFileName, dir, transtime);

	// 親がいればリストに追加
	if (parent) parent->AddChild(t);

	// オブジェクトの返却
	return t;
}

// トランジションオブジェクト生成
// 親オブジェクトとオブジェクトとトランジションに必要な項目を指定する。
// parent : 親オブジェクト
// name : オブジェクト名
// ruleFIlename : ルール画像ファイル名
// 遷移先画像ポインタ
// dir : トランジション方向
// transtime : トランジション時間
// return : 生成したオブジェクト
template <class T> T* CreateTransitionObject(IBaseObject* parent, const std::string& name, const std::string& ruleFilename, IDrawBase* pTransObj, cTransition::TransDirection dir, float transtime)
{
	// ゲームオブジェクト生成
	T* t = NEW T(parent, name, ruleFilename, pTransObj, dir, transtime);

	// 親がいればリストに追加
	if (parent) parent->AddChild(t);

	// オブジェクトの返却
	return t;
}
