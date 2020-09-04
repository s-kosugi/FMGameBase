/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleTile.cpp												*/
/*  @brief		:	�`��I�u�W�F�N�g											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/26													*/
/*																				*/
/*==============================================================================*/

#include "cTitleTile.h"
#include "..\..\..\..\cGame.h"


//==========================================================================================
// �萔
//==========================================================================================
const float cTitleTile::TILE_SCALEUP = 0.1f;
const float cTitleTile::CRUMBLE_MOVE_X = 3.0f;
const float cTitleTile::CRUMBLE_START_Y = -4.0f;
const float cTitleTile::CRUMBLE_GRAVITY = 0.5f;

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTitleTile::cTitleTile(IBaseObject* parent, const std::string& objectname, const std::string& filename) :
	cSpriteObject(parent, "TitleTile", "data\\graphic\\hex.png"),
	m_bPop( false ),
	m_bCrumble( false ),
	m_vPosUp(0.0f,0.0f)
{

}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cTitleTile::~cTitleTile(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cTitleTile::
Initialize(void)
{
	cSpriteObject::Initialize();

	SetPriority(PRIORITY);
	SetScale(0.0f);
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cTitleTile::Update(void)
{
	if (m_bCrumble)
	{
		m_vPosUp.y += CRUMBLE_GRAVITY;
		m_bPop = false;

		// �������Ɋ��S�ɏo�����Ă��Ȃ��^�C���͏�������
		if( m_vScale.x <= 0.0f ) DeleteObject();
	}
	if (m_bPop)
	{
		// �^�C���o����
		float scale = GetScale().x + TILE_SCALEUP;
		if (scale > 1.0f)
		{
			scale = 1.0f;
		}
		SetScale(scale);
	}

	m_vPos.x += m_vPosUp.x;
	m_vPos.y += m_vPosUp.y;

	// ��ʊO�ɏo���������
	if (m_vPos.y - GetSpriteSize().y / 2.0f >= cGame::GetInstance().GetWindowHeight())
		DeleteObject();

	cSpriteObject::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cTitleTile::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
//==========================================================================================
//  �����J�n����
//==========================================================================================
void cTitleTile::StartCrumble(void)
{
	m_bCrumble = true;

	// ���������������_���Ɍ��߂�
	m_vPosUp.x = (float)cGame::Random(0,(int)CRUMBLE_MOVE_X*10) / 10.0f;
	if (cGame::Random(0, 1))
	{
		m_vPosUp.x *= -1.0f;
	}
	m_vPosUp.y = CRUMBLE_START_Y;
}