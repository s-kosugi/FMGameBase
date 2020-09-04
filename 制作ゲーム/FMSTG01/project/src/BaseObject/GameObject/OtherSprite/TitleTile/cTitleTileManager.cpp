/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleTileManager.cpp										*/
/*  @brief		:	�^�C�g���^�C���Ǘ�											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/28													*/
/*																				*/
/*==============================================================================*/

#include "cTitleTileManager.h"
#include "..\..\..\cSpriteObject.h"
#include "..\..\..\..\cGame.h"
#include "cTitleTile.h"
#include "..\..\..\..\SoundCtrl\cSoundCtrl.h"


//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTitleTileManager::cTitleTileManager(IBaseObject* parent) :
	IBaseObject(parent, "TitleTileManager"),
	m_nCounter( 0 ),
	m_eState(STATE_WAIT),
	m_bPopComp(false)
{
}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cTitleTileManager::~cTitleTileManager(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cTitleTileManager::
Initialize(void)
{
	IBaseObject::Initialize();

	// �^�C���̐���
	for (int i = 0; i <= cGame::GetInstance().GetWindowWidth() / TILE_SIZE;i++)
	{
		for (int j = 0; j <= cGame::GetInstance().GetWindowHeight() / TILE_HEIGHT + 1;j++)
		{
			int adjust = 0;
			if (j % 2 == 1) adjust = TILE_ADJUST;
			cSpriteObject* obj = CreateDrawObject<cTitleTile>(this, "TitleTile", "data\\graphic\\hex.png");
			obj->SetPos((float)(i*TILE_SIZE) + adjust, (float)(j * TILE_HEIGHT));
			obj->SetScale(0.0f);

		}
	}
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cTitleTileManager::Update(void)
{
	
	switch (m_eState)
	{
	case STATE_TILE_POP:
		Pop();
		break;
	case STATE_CRUMBLE:
		Crumble();
		break;
	}
	IBaseObject::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cTitleTileManager::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}
//==========================================================================================
//  �^�C���o��
//==========================================================================================
void cTitleTileManager::Pop(void)
{
	m_nCounter++;

	if (m_nCounter % 10 == 0)
	{
		cSoundCtrl::GetInstance().Play(SOUND_KACHI);
	}

	if (!m_listChildObject.empty())
	{
		// �^�C����傫�����������J�E���g����
		unsigned int tileCompCount = 0;

		for (auto it = m_listChildObject.begin(); it != m_listChildObject.end();it++)
		{
			// �^�C�����o������������J�E���g
			if (((cSpriteObject*)(*it))->GetScale().x == 1.0f)
			{
				tileCompCount++;
			}
		}
		// �^�C�������S�ɏo�����I�������ҋ@��Ԃֈڍs
		if (tileCompCount >= m_listChildObject.size())
		{
			m_eState = STATE_WAIT;
			m_bPopComp = true;
			m_nCounter = 0;
			return;
		}

		// �ǂ̃^�C�����o�����邩����
		if (m_nCounter % TILE_POP_INTERVAL == 0)
		{
			unsigned int i = cGame::Random(0, m_listChildObject.size() - 1);
			auto it = m_listChildObject.begin();

			// �����_���Ō��肵���v�f�ɂ���
			for (unsigned int j = 0; j < i; j++) it++;
			short pop = 0;
			unsigned int count = 0;
			while (1)
			{

				if (m_listChildObject.end() == it) it = m_listChildObject.begin();

				cTitleTile* tile = (cTitleTile*)(*it);

				if (!tile->isPop())
				{
					tile->StartPop();
					pop++;
					// �K�萔�����ɏo��������
					if( pop >= TILE_SAME_POP)	break;
				}
				if (count >= m_listChildObject.size()) break;

				it++;
				count++;

			}
		}
	}
}
//==========================================================================================
//  �^�C������
//==========================================================================================
void cTitleTileManager::Crumble(void)
{
	if (m_listChildObject.empty())
	{
		DeleteObject();
		return;
	}
	m_nCounter++;
	// �^�C�����󒆂̉���炷
	if (m_nCounter % 10 == 0)
	{
		cSoundCtrl::GetInstance().Play(SOUND_BOM);
	}
	// �ǂ̃^�C�����������邩����
	if (m_nCounter % TILE_CRUMBLE_INTERVAL == 0)
	{
		unsigned int i = cGame::Random(0, m_listChildObject.size() - 1);
		auto it = m_listChildObject.begin();

		// �����_���Ō��肵���v�f�ɂ���
		for (unsigned int j = 0; j < i; j++) it++;

		unsigned int count = 0;
		short crumble = 0;
		while (1)
		{

			if (m_listChildObject.end() == it) it = m_listChildObject.begin();

			cTitleTile* tile = (cTitleTile*)(*it);

			if (!tile->isCrumble())
			{
				tile->StartCrumble();
				// �����ł��Ȃ��i���o���̏ꍇ�͂��̂܂܎��̗v�f���m�F����
				if (tile->GetScale().x > 0.0f)
				{
					crumble++;
					// �K�萔�����ɕ���������
					if( crumble >= TILE_SAME_CRUMBLE )break;
				}
			}
			if (count >= m_listChildObject.size()) break;

			it++;
			count++;
		}
	}
}
