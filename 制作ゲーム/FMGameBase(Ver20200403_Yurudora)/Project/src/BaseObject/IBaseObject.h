#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	IBaseObject.h												*/
/*  @brief		:	オブジェクトベース											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/21													*/
/*																				*/
/*==============================================================================*/

#include <list>
#include <string>
#include "..\Utility\memory.h"

// オブジェクトクラスの前方宣言
class IBaseObject;

// オブジェクトクラスのリスト
typedef std::list<IBaseObject*> OBJECT_LIST;

// 検索関数登録用関数ポインタ
typedef bool( *FIND_METHOD )( IBaseObject* arg );


// オブジェクト状態ID
enum class OBJECT_STATE
{
	WAIT,		//	待機(更新なし、描画のみ)
	ACTIVE,		//	更新・描画
	DEAD,		//	死亡(子オブジェクトもすべて解放)
};

//================================================================================================
// オブジェクトベース
class IBaseObject
{
public:
	// コンストラクタ
	IBaseObject();
	IBaseObject( IBaseObject* parent );
	IBaseObject( IBaseObject* parent, const std::string& name );

	virtual ~IBaseObject();

	virtual void Initialize( void );
	virtual void Update( void );
	virtual IBaseObject* Finalize( void );
	virtual void Reset( void );

	// 親オブジェクトの取得  ルートの場合はnull
	inline IBaseObject* GetParent( void ) { return m_pParentObject; };

	// ルートオブジェクトの取得
	IBaseObject* GetRoot( void );

	// 子オブジェクトリストの取得
	inline OBJECT_LIST* GetChildList( void ) { return &m_listChildObject; };

	// 子オブジェクトの追加
	void		 AddChild( IBaseObject* obj );

	// 子オブジェクトを先頭に追加する
	void		 AddFrontChild( IBaseObject* obj );

	// 子オブジェクトの削除
	// 名前を指定して子オブジェクトを削除する。
	// return : リストから削除した子のオブジェクト
	IBaseObject* RemoveChild( const std::string& name );

	// 子オブジェクトの削除
	// 検索条件を関数ポインタで指定する
	// return : リストから削除した子のオブジェクト
	IBaseObject* RemoveChild( FIND_METHOD func );

	// 子オブジェクトの検索
	// 子オブジェクトの名前を指定する
	// return : 検索オブジェクト 見つからなかった場合はnull
	IBaseObject* FindChild( const std::string& name );

	// 子オブジェクトの検索
	// 検索条件を関数ポインタで指定する
	// return : 検索オブジェクト 見つからなかった場合はnull
	IBaseObject* FindChild( FIND_METHOD func );

	// 兄弟オブジェクトの検索
	// 子オブジェクトの名前を指定する
	// return : 検索オブジェクト 見つからなかった場合はnull
	IBaseObject* FindSibling( const std::string& name );

	// 兄弟オブジェクトの検索
	// 検索条件を関数ポインタで指定する
	// return : 検索オブジェクト 見つからなかった場合はnull
	IBaseObject* FindSibling( FIND_METHOD func );

	// オブジェクト名の取得
	inline std::string	 GetObjectName( void ) const { return m_sObjectName; };

	// オブジェクト状態の取得
	inline OBJECT_STATE GetObjectState( void ) const { return m_eObjectState; };

	// オブジェクトの破棄
	inline void			DeleteObject( void ) { m_eObjectState = OBJECT_STATE::DEAD; };

	// オブジェクト状態の設定
	inline void			SetObjetState( OBJECT_STATE state ) { m_eObjectState = state; };

protected:
	IBaseObject* m_pParentObject;		// 親のオブジェクト
	OBJECT_LIST			m_listChildObject;		// 子オブジェクトリスト
	std::string			m_sObjectName;			// オブジェクト名
	OBJECT_STATE		m_eObjectState;			// オブジェクト状態
};


//================================================================================================
// オブジェクト生成関数
//================================================================================================

// オブジェクト生成
// 親オブジェクトを指定する。
// return : 生成したオブジェクト
template <class T> T* CreateObject( IBaseObject* parent )
{
	// ゲームオブジェクト生成
	T* t = NEW T( parent );

	// 親がいればリストに追加
	if( parent ) parent->AddChild( t );

	// オブジェクトの返却
	return t;
}

// オブジェクト生成
// 親オブジェクトとオブジェクト名指定する。
// return : 生成したオブジェクト
template <class T> T* CreateObject( IBaseObject* parent, const std::string& name )
{
	// ゲームオブジェクト生成
	T* t = NEW T( parent, name );

	// 親がいればリストに追加
	if( parent ) parent->AddChild( t );

	// オブジェクトの返却
	return t;
}

// オブジェクト生成(前方に追加)
// 親オブジェクトを指定する。
// return : 生成したオブジェクト
template <class T> T* CreateObjectF( IBaseObject* parent )
{
	// ゲームオブジェクト生成
	T* t = NEW T( parent );

	// 親がいればリストに追加
	if( parent ) parent->AddFrontChild( t );

	// オブジェクトの返却
	return t;
}

// オブジェクト生成(前方に追加)
// 親オブジェクトとオブジェクト名指定する。
// return : 生成したオブジェクト
template <class T> T* CreateObjectF( IBaseObject* parent, const std::string& name )
{
	// ゲームオブジェクト生成
	T* t = NEW T( parent, name );

	// 親がいればリストに追加
	if( parent ) parent->AddFrontChild( t );

	// オブジェクトの返却
	return t;
}