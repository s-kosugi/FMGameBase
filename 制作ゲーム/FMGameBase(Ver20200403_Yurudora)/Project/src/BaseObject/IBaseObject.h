#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	IBaseObject.h												*/
/*  @brief		:	�I�u�W�F�N�g�x�[�X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/21													*/
/*																				*/
/*==============================================================================*/

#include <list>
#include <string>
#include "..\Utility\memory.h"

// �I�u�W�F�N�g�N���X�̑O���錾
class IBaseObject;

// �I�u�W�F�N�g�N���X�̃��X�g
typedef std::list<IBaseObject*> OBJECT_LIST;

// �����֐��o�^�p�֐��|�C���^
typedef bool( *FIND_METHOD )( IBaseObject* arg );


// �I�u�W�F�N�g���ID
enum class OBJECT_STATE
{
	WAIT,		//	�ҋ@(�X�V�Ȃ��A�`��̂�)
	ACTIVE,		//	�X�V�E�`��
	DEAD,		//	���S(�q�I�u�W�F�N�g�����ׂĉ��)
};

//================================================================================================
// �I�u�W�F�N�g�x�[�X
class IBaseObject
{
public:
	// �R���X�g���N�^
	IBaseObject();
	IBaseObject( IBaseObject* parent );
	IBaseObject( IBaseObject* parent, const std::string& name );

	virtual ~IBaseObject();

	virtual void Initialize( void );
	virtual void Update( void );
	virtual IBaseObject* Finalize( void );
	virtual void Reset( void );

	// �e�I�u�W�F�N�g�̎擾  ���[�g�̏ꍇ��null
	inline IBaseObject* GetParent( void ) { return m_pParentObject; };

	// ���[�g�I�u�W�F�N�g�̎擾
	IBaseObject* GetRoot( void );

	// �q�I�u�W�F�N�g���X�g�̎擾
	inline OBJECT_LIST* GetChildList( void ) { return &m_listChildObject; };

	// �q�I�u�W�F�N�g�̒ǉ�
	void		 AddChild( IBaseObject* obj );

	// �q�I�u�W�F�N�g��擪�ɒǉ�����
	void		 AddFrontChild( IBaseObject* obj );

	// �q�I�u�W�F�N�g�̍폜
	// ���O���w�肵�Ďq�I�u�W�F�N�g���폜����B
	// return : ���X�g����폜�����q�̃I�u�W�F�N�g
	IBaseObject* RemoveChild( const std::string& name );

	// �q�I�u�W�F�N�g�̍폜
	// �����������֐��|�C���^�Ŏw�肷��
	// return : ���X�g����폜�����q�̃I�u�W�F�N�g
	IBaseObject* RemoveChild( FIND_METHOD func );

	// �q�I�u�W�F�N�g�̌���
	// �q�I�u�W�F�N�g�̖��O���w�肷��
	// return : �����I�u�W�F�N�g ������Ȃ������ꍇ��null
	IBaseObject* FindChild( const std::string& name );

	// �q�I�u�W�F�N�g�̌���
	// �����������֐��|�C���^�Ŏw�肷��
	// return : �����I�u�W�F�N�g ������Ȃ������ꍇ��null
	IBaseObject* FindChild( FIND_METHOD func );

	// �Z��I�u�W�F�N�g�̌���
	// �q�I�u�W�F�N�g�̖��O���w�肷��
	// return : �����I�u�W�F�N�g ������Ȃ������ꍇ��null
	IBaseObject* FindSibling( const std::string& name );

	// �Z��I�u�W�F�N�g�̌���
	// �����������֐��|�C���^�Ŏw�肷��
	// return : �����I�u�W�F�N�g ������Ȃ������ꍇ��null
	IBaseObject* FindSibling( FIND_METHOD func );

	// �I�u�W�F�N�g���̎擾
	inline std::string	 GetObjectName( void ) const { return m_sObjectName; };

	// �I�u�W�F�N�g��Ԃ̎擾
	inline OBJECT_STATE GetObjectState( void ) const { return m_eObjectState; };

	// �I�u�W�F�N�g�̔j��
	inline void			DeleteObject( void ) { m_eObjectState = OBJECT_STATE::DEAD; };

	// �I�u�W�F�N�g��Ԃ̐ݒ�
	inline void			SetObjetState( OBJECT_STATE state ) { m_eObjectState = state; };

protected:
	IBaseObject* m_pParentObject;		// �e�̃I�u�W�F�N�g
	OBJECT_LIST			m_listChildObject;		// �q�I�u�W�F�N�g���X�g
	std::string			m_sObjectName;			// �I�u�W�F�N�g��
	OBJECT_STATE		m_eObjectState;			// �I�u�W�F�N�g���
};


//================================================================================================
// �I�u�W�F�N�g�����֐�
//================================================================================================

// �I�u�W�F�N�g����
// �e�I�u�W�F�N�g���w�肷��B
// return : ���������I�u�W�F�N�g
template <class T> T* CreateObject( IBaseObject* parent )
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T( parent );

	// �e������΃��X�g�ɒǉ�
	if( parent ) parent->AddChild( t );

	// �I�u�W�F�N�g�̕ԋp
	return t;
}

// �I�u�W�F�N�g����
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g���w�肷��B
// return : ���������I�u�W�F�N�g
template <class T> T* CreateObject( IBaseObject* parent, const std::string& name )
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T( parent, name );

	// �e������΃��X�g�ɒǉ�
	if( parent ) parent->AddChild( t );

	// �I�u�W�F�N�g�̕ԋp
	return t;
}

// �I�u�W�F�N�g����(�O���ɒǉ�)
// �e�I�u�W�F�N�g���w�肷��B
// return : ���������I�u�W�F�N�g
template <class T> T* CreateObjectF( IBaseObject* parent )
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T( parent );

	// �e������΃��X�g�ɒǉ�
	if( parent ) parent->AddFrontChild( t );

	// �I�u�W�F�N�g�̕ԋp
	return t;
}

// �I�u�W�F�N�g����(�O���ɒǉ�)
// �e�I�u�W�F�N�g�ƃI�u�W�F�N�g���w�肷��B
// return : ���������I�u�W�F�N�g
template <class T> T* CreateObjectF( IBaseObject* parent, const std::string& name )
{
	// �Q�[���I�u�W�F�N�g����
	T* t = NEW T( parent, name );

	// �e������΃��X�g�ɒǉ�
	if( parent ) parent->AddFrontChild( t );

	// �I�u�W�F�N�g�̕ԋp
	return t;
}