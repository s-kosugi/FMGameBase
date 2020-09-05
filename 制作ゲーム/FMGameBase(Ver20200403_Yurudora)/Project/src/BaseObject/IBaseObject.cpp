/*==============================================================================*/
/*																				*/
/*	@file title	:	IBaseObject.cpp												*/
/*  @brief		:	�I�u�W�F�N�g�x�[�X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "IBaseObject.h"

//==========================================================================================
//	�R���X�g���N�^
//==========================================================================================
IBaseObject::IBaseObject( void )
	: m_pParentObject( nullptr )
	, m_sObjectName( "None" )
	, m_eObjectState( OBJECT_STATE::ACTIVE )
{
	m_listChildObject.clear();
}

//==========================================================================================
//	�R���X�g���N�^
//==========================================================================================
IBaseObject::IBaseObject( IBaseObject* parent )
	: m_pParentObject( parent )
	, m_sObjectName( "None" )
	, m_eObjectState( OBJECT_STATE::ACTIVE )
{
	m_listChildObject.clear();
}

//==========================================================================================
//	�R���X�g���N�^
//==========================================================================================
IBaseObject::IBaseObject( IBaseObject* parent, const std::string& name )
	: m_pParentObject( parent )
	, m_sObjectName( name )
	, m_eObjectState( OBJECT_STATE::ACTIVE )
{
	m_listChildObject.clear();
}

//==========================================================================================
//	�f�X�g���N�^
//==========================================================================================
IBaseObject::~IBaseObject( void )
{
}

//==========================================================================================
//	������
//==========================================================================================
void IBaseObject::Initialize( void )
{
	// ���X�g����Ȃ�I��
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
//	�X�V
//==========================================================================================
void IBaseObject::Update( void )
{
	// ���X�g����Ȃ�I��
	if( m_listChildObject.empty() ) return;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		IBaseObject* t = ( *it );

		// �I�u�W�F�N�g�̏�Ԃ��f�b�h�Ȃ烊�X�g���珜�O
		if( t->GetObjectState() == OBJECT_STATE::DEAD )
		{
			// �q�I�u�W�F�N�g�����ׂĉ��
			t->Finalize();

			// ���������
			SAFE_DELETE( t );

			// ���X�g����폜
			it = m_listChildObject.erase( it );

			continue;
		}

		// �I�u�W�F�N�g�̏�Ԃ��A�N�e�B�u�Ȃ�X�V
		if( t->GetObjectState() == OBJECT_STATE::ACTIVE )
			t->Update();

		++it;
	}
}

//==========================================================================================
//	���
//==========================================================================================
IBaseObject* IBaseObject::Finalize( void )
{
	// ���X�g����Ȃ�I��
	if( m_listChildObject.empty() ) return this;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		IBaseObject* obj = ( *it )->Finalize();

		SAFE_DELETE( obj );

		++it;
	}

	// ���X�g�̃N���A
	m_listChildObject.clear();

	return this;
}

//==========================================================================================
//	���Z�b�g
//==========================================================================================
void IBaseObject::Reset( void )
{
	// ���X�g����Ȃ�I��
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
// ���[�g�I�u�W�F�N�g�̎擾
// ret : ���[�g�I�u�W�F�N�g�̃|�C���^
//==========================================================================================
IBaseObject* IBaseObject::GetRoot( void )
{
	IBaseObject* pObj = this;
	while( pObj->GetParent() ) pObj = pObj->GetParent();
	return pObj;
}

//==========================================================================================
//	�q�I�u�W�F�N�g�̒ǉ�
// arg �ǉ�����q�I�u�W�F�N�g
//==========================================================================================
void IBaseObject::AddChild( IBaseObject* obj )
{
	if( !obj ) return;

	// �e�I�u�W�F�N�g�̓o�^
	obj->m_pParentObject = this;

	// �q���X�g�ɒǉ�
	m_listChildObject.push_back( obj );
}

//==========================================================================================
//	�q�I�u�W�F�N�g��擪�ɒǉ�
// arg �ǉ�����q�I�u�W�F�N�g
//==========================================================================================
void IBaseObject::AddFrontChild( IBaseObject* obj )
{
	if( !obj ) return;

	// �e�I�u�W�F�N�g�̓o�^
	obj->m_pParentObject = this;

	// �q���X�g�ɒǉ�
	m_listChildObject.push_front( obj );
}

//==========================================================================================
//	�q�I�u�W�F�N�g�̍폜
// arg �q�I�u�W�F�N�g��
// ret �폜�����q�̃A�h���X
//==========================================================================================
IBaseObject* IBaseObject::RemoveChild( const std::string& name )
{
	// ���X�g����Ȃ�I��
	if( m_listChildObject.empty() ) return nullptr;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		if( ( *it )->m_sObjectName == name )
		{
			IBaseObject* t = *it;

			// ���X�g����폜
			m_listChildObject.erase( it );

			return t;
		}

		++it;
	}

	return nullptr;
}


//==========================================================================================
// �q�I�u�W�F�N�g�̍폜
// arg �֐��|�C���^
// ret �폜�����q�̃A�h���X
//==========================================================================================
IBaseObject* IBaseObject::RemoveChild( FIND_METHOD func )
{
	// ���X�g����Ȃ�I��
	if( m_listChildObject.empty() ) return nullptr;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		if( func( *it ) )
		{
			IBaseObject* t = *it;

			// ���X�g����폜
			m_listChildObject.erase( it );

			return t;
		}

		++it;
	}

	return nullptr;
}

//==========================================================================================
//	�q�I�u�W�F�N�g�̌���
//	arg �I�u�W�F�N�g��
//	ret �����I�u�W�F�N�g �����ꍇ��nullptr
//==========================================================================================
IBaseObject* IBaseObject::FindChild( const std::string& name )
{
	// �Q�[���I�u�W�F�N�g���������Ȃ�A���̃I�u�W�F�N�g��Ԃ�
	if( m_sObjectName == name ) return this;

	// ���X�g����Ȃ�I��
	if( m_listChildObject.empty() ) return nullptr;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		// �Q�[���I�u�W�F�N�gID�ɂ���Ďq�I�u�W�F�N�g����������
		IBaseObject* t = ( *it )->FindChild( name );

		// �A�h���X������Ό�������
		if( t ) return t;

		++it;
	}

	return nullptr;
}

//==========================================================================================
//	�q�I�u�W�F�N�g�̌���
//	arg ���������ɂ���֐��|�C���^
//	ret �����I�u�W�F�N�g �����ꍇ��nullptr
//==========================================================================================
IBaseObject* IBaseObject::FindChild( FIND_METHOD func )
{
	// �����������^�Ȃ�A���̃I�u�W�F�N�g��Ԃ�
	if( func( this ) ) return this;

	// ���X�g����Ȃ�I��
	if( m_listChildObject.empty() ) return nullptr;

	OBJECT_LIST::iterator it = m_listChildObject.begin();
	OBJECT_LIST::iterator end = m_listChildObject.end();

	while( it != end )
	{
		// ����������^���Ďq�I�u�W�F�N�g����������
		IBaseObject* t = ( *it )->FindChild( func );

		// �A�h���X������Ό�������
		if( t ) return t;

		++it;
	}

	return nullptr;
}

//==========================================================================================
//	�Z��I�u�W�F�N�g�̌���
//	arg �I�u�W�F�N�g��
//	ret �����I�u�W�F�N�g �����ꍇ��nullptr
//==========================================================================================
IBaseObject* IBaseObject::FindSibling( const std::string& name )
{
	// �e�I�u�W�F�N�g�����Ȃ�
	if( !m_pParentObject ) return nullptr;

	// �e�̃��X�g����Z�������
	return m_pParentObject->FindChild( name );
}

//==========================================================================================
//	�Z��I�u�W�F�N�g�̌���
//	arg ���������ɂ���֐��|�C���^
//	ret �����I�u�W�F�N�g �����ꍇ��nullptr
//==========================================================================================
IBaseObject* IBaseObject::FindSibling( FIND_METHOD func )
{
	// �e�I�u�W�F�N�g�����Ȃ�
	if( !m_pParentObject ) return nullptr;

	// �e�̃��X�g����Z�������
	return m_pParentObject->FindChild( func );
}