#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	ISingleton.h												*/
/*  @brief		:	シングルトンクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/09/18													*/
/*																				*/
/*==============================================================================*/

// シングルトン化するクラスに継承をさせるためのベースクラス
template<class T> class ISingleton {
protected:
	ISingleton(void) {};     //  他からの生成を禁止(複数生成の禁止)(コンストラクタをprivateにする事で外部生成不可)
	virtual ~ISingleton(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	ISingleton(const T& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)(privateにする事で外部使用禁止)
	T& operator = (const T& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)(privateにする事で外部使用禁止)

public:
	static T& GetInstance(void) {
		static T instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};		// 静的メンバ関数、GetInstanceをする事で生成されていない自分のクラスの関数を呼び出す事が可能
};