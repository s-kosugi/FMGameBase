#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	IBaseSingleton.h											*/
/*  @brief		:	シングルトンオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"

// シングルトンオブジェクトクラス
template<class T> class IBaseSingleton : public IBaseObject
{
protected:
	IBaseSingleton(void) { IBaseObject::IBaseObject(); };     //  他からの生成を禁止
	IBaseSingleton(IBaseObject* parent) { IBaseObject::IBaseObject( parent, "None" );};
	IBaseSingleton(IBaseObject* parent, const std::string& name) { IBaseObject::IBaseObject(parent, name); };
	virtual ~IBaseSingleton(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	IBaseSingleton(const T& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	T& operator = (const T& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)

public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	virtual IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static T& GetInstance(void) {
		static T instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};		// 静的メンバ関数、GetInstanceをする事で生成されていない自分のクラスの関数を呼び出す事が可能
};