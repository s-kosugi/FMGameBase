/*==============================================================================*/
/*																				*/
/*	@file title	:	IBaseObject.cpp												*/
/*  @brief		:	オブジェクトベース											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"

//==========================================================================================
//	コンストラクタ
//==========================================================================================
IBaseObject::IBaseObject( void )
	: m_pParentObject( nullptr )
	, m_sObjectName( "None" )
	, m_eObjectState( OBJECT_STATE::ACTIVE )
{
	m_listChildObject.clear();
}

//==========================================================================================
//	コンストラクタ
//==========================================================================================
IBaseObject::IBaseObject( IBaseObject* parent )
	: m_pParentObject( parent )
	, m_sObjectName( "None" )
	, m_eObjectState( OBJECT_STATE::ACTIVE )
{
	m_listChildObject.clear();
}

//==========================================================================================
//	コンストラクタ
//==========================================================================================
IBaseObject::IBaseObject( IBaseObject* parent, const std::string& name )
	: m_pParentObject( parent )
	, m_sObjectName( name )
	, m_eObjectState( OBJECT_STATE::ACTIVE )
{
	m_listChildObject.clear();
}

//==========================================================================================
//	デストラクタ
//==========================================================================================
IBaseObject::~IBaseObject( void )
{
}

//==========================================================================================
//	初期化
//==========================================================================================
void IBaseObject::Initialize( void )
{
	// リストが空なら終了
	if( m_listChildObject.empty() ) return;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		( *it )->Initialize();

		++it;
	}
}

//==========================================================================================
//	更新
//==========================================================================================
void IBaseObject::Update( void )
{
	// リストが空なら終了
	if( m_listChildObject.empty() ) return;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		IBaseObject* t = ( *it );

		// オブジェクトの状態がデッドならリストから除外
		if( t->GetObjectState() == OBJECT_STATE::DEAD )
		{
			// 子オブジェクトをすべて解放
			t->Finalize();

			// メモリ解放
			SAFE_DELETE( t );

			// リストから削除
			it = m_listChildObject.erase( it );

			continue;
		}

		// オブジェクトの状態がアクティブなら更新
		if( t->GetObjectState() == OBJECT_STATE::ACTIVE )
			t->Update();

		++it;
	}
}

//==========================================================================================
//	解放
//==========================================================================================
IBaseObject* IBaseObject::Finalize( void )
{
	// リストが空なら終了
	if( m_listChildObject.empty() ) return this;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		IBaseObject* obj = ( *it )->Finalize();

		SAFE_DELETE( obj );

		++it;
	}

	// リストのクリア
	m_listChildObject.clear();

	return this;
}

//==========================================================================================
//	リセット
//==========================================================================================
void IBaseObject::Reset( void )
{
	// リストが空なら終了
	if( m_listChildObject.empty() ) return;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		( *it )->Reset();

		++it;
	}
}

//==========================================================================================
// ルートオブジェクトの取得
// ret : ルートオブジェクトのポインタ
//==========================================================================================
IBaseObject* IBaseObject::GetRoot( void )
{
	IBaseObject* pObj = this;
	while( pObj->GetParent() ) pObj = pObj->GetParent();
	return pObj;
}

//==========================================================================================
//	子オブジェクトの追加
// arg 追加する子オブジェクト
//==========================================================================================
void IBaseObject::AddChild( IBaseObject* obj )
{
	if( !obj ) return;

	// 親オブジェクトの登録
	obj->m_pParentObject = this;

	// 子リストに追加
	m_listChildObject.push_back( obj );
}

//==========================================================================================
//	子オブジェクトを先頭に追加
// arg 追加する子オブジェクト
//==========================================================================================
void IBaseObject::AddFrontChild( IBaseObject* obj )
{
	if( !obj ) return;

	// 親オブジェクトの登録
	obj->m_pParentObject = this;

	// 子リストに追加
	m_listChildObject.push_front( obj );
}

//==========================================================================================
//	子オブジェクトの削除
// arg 子オブジェクト名
// ret 削除した子のアドレス
//==========================================================================================
IBaseObject* IBaseObject::RemoveChild( const std::string& name )
{
	// リストが空なら終了
	if( m_listChildObject.empty() ) return nullptr;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		if( ( *it )->m_sObjectName == name )
		{
			IBaseObject* t = *it;

			// リストから削除
			m_listChildObject.erase( it );

			return t;
		}

		++it;
	}

	return nullptr;
}


//==========================================================================================
// 子オブジェクトの削除
// arg 関数ポインタ
// ret 削除した子のアドレス
//==========================================================================================
IBaseObject* IBaseObject::RemoveChild( FIND_METHOD func )
{
	// リストが空なら終了
	if( m_listChildObject.empty() ) return nullptr;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		if( func( *it ) )
		{
			IBaseObject* t = *it;

			// リストから削除
			m_listChildObject.erase( it );

			return t;
		}

		++it;
	}

	return nullptr;
}

//==========================================================================================
//	子オブジェクトの検索
//	arg オブジェクト名
//	ret 検索オブジェクト 無い場合はnullptr
//==========================================================================================
IBaseObject* IBaseObject::FindChild( const std::string& name )
{
	// ゲームオブジェクト名が同じなら、そのオブジェクトを返す
	if( m_sObjectName == name ) return this;

	// リストが空なら終了
	if( m_listChildObject.empty() ) return nullptr;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		// ゲームオブジェクトIDによって子オブジェクトを検索する
		IBaseObject* t = ( *it )->FindChild( name );

		// アドレスがあれば見つかった
		if( t ) return t;

		++it;
	}

	return nullptr;
}

//==========================================================================================
//	子オブジェクトの検索
//	arg 検索条件にする関数ポインタ
//	ret 検索オブジェクト 無い場合はnullptr
//==========================================================================================
IBaseObject* IBaseObject::FindChild( FIND_METHOD func )
{
	// 検索条件が真なら、そのオブジェクトを返す
	if( func( this ) ) return this;

	// リストが空なら終了
	if( m_listChildObject.empty() ) return nullptr;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		// 検索条件を与えて子オブジェクトを検索する
		IBaseObject* t = ( *it )->FindChild( func );

		// アドレスがあれば見つかった
		if( t ) return t;

		++it;
	}

	return nullptr;
}

//==========================================================================================
//	兄弟オブジェクトの検索
//	arg オブジェクト名
//	ret 検索オブジェクト 無い場合はnullptr
//==========================================================================================
IBaseObject* IBaseObject::FindSibling( const std::string& name )
{
	// 親オブジェクトがいない
	if( !m_pParentObject ) return nullptr;

	// 親のリストから兄弟を検索
	return m_pParentObject->FindChild( name );
}

//==========================================================================================
//	兄弟オブジェクトの検索
//	arg 検索条件にする関数ポインタ
//	ret 検索オブジェクト 無い場合はnullptr
//==========================================================================================
IBaseObject* IBaseObject::FindSibling( FIND_METHOD func )
{
	// 親オブジェクトがいない
	if( !m_pParentObject ) return nullptr;

	// 親のリストから兄弟を検索
	return m_pParentObject->FindChild( func );
}