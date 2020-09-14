#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.h											*/
/*  @brief		:	エフェクト管理クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "EffectID.h"
#include "..\..\..\Utility\Vector\cVector2.h"

class cEffectObject;

class cEffectManager : public IBaseObject
{
public:

	// 初期化
	void Initialize(void) override;

	// 更新
	void Update(void) override;

	// 破棄
	IBaseObject* Finalize(void) override;

	// 生成
	cEffectObject* Create(EFFECT_ID id,cVector2 pos);
	
	// エフェクトファイル読込
	void LoadEffect( EFFECT_ID id );

	// 全エフェクトファイル読込
	void LoadAllEffect( void );

	// エフェクトファイル名の取得
	inline std::string GetEffectFilename(EFFECT_ID id) { return EFFECT_FILE_NAME[(int)id]; };

private:
	
	// エフェクトファイル名テーブル
	static const std::string EFFECT_FILE_NAME[(int)EFFECT_ID::MAX];

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cEffectManager(void) { };     //  他からの生成を禁止
	cEffectManager(IBaseObject* parent) {  };
	cEffectManager(IBaseObject* parent, const std::string& name) { };
	~cEffectManager(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cEffectManager(const cEffectManager& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cEffectManager& operator = (const cEffectManager& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:

	static cEffectManager& GetInstance(void) {
		static cEffectManager instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
//-----------------------------------------------------------------------------------------------------
};