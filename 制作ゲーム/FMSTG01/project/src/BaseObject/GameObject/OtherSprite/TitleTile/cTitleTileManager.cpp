/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleTileManager.cpp										*/
/*  @brief		:	タイトルタイル管理											*/
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
//  コンストラクタ
//==========================================================================================
cTitleTileManager::cTitleTileManager(IBaseObject* parent) :
	IBaseObject(parent, "TitleTileManager"),
	m_nCounter( 0 ),
	m_eState(STATE_WAIT),
	m_bPopComp(false)
{
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cTitleTileManager::~cTitleTileManager(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cTitleTileManager::
Initialize(void)
{
	IBaseObject::Initialize();

	// タイルの生成
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
//  更新
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
//  解放
//==========================================================================================
IBaseObject* cTitleTileManager::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}
//==========================================================================================
//  タイル出現
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
		// タイルを大きくした数をカウントする
		unsigned int tileCompCount = 0;

		for (auto it = m_listChildObject.begin(); it != m_listChildObject.end();it++)
		{
			// タイルが出現しきったらカウント
			if (((cSpriteObject*)(*it))->GetScale().x == 1.0f)
			{
				tileCompCount++;
			}
		}
		// タイルが完全に出現し終わったら待機状態へ移行
		if (tileCompCount >= m_listChildObject.size())
		{
			m_eState = STATE_WAIT;
			m_bPopComp = true;
			m_nCounter = 0;
			return;
		}

		// どのタイルが出現するか判定
		if (m_nCounter % TILE_POP_INTERVAL == 0)
		{
			unsigned int i = cGame::Random(0, m_listChildObject.size() - 1);
			auto it = m_listChildObject.begin();

			// ランダムで決定した要素にする
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
					// 規定数同時に出現させる
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
//  タイル崩壊
//==========================================================================================
void cTitleTileManager::Crumble(void)
{
	if (m_listChildObject.empty())
	{
		DeleteObject();
		return;
	}
	m_nCounter++;
	// タイル崩壊中の音を鳴らす
	if (m_nCounter % 10 == 0)
	{
		cSoundCtrl::GetInstance().Play(SOUND_BOM);
	}
	// どのタイルが崩落するか判定
	if (m_nCounter % TILE_CRUMBLE_INTERVAL == 0)
	{
		unsigned int i = cGame::Random(0, m_listChildObject.size() - 1);
		auto it = m_listChildObject.begin();

		// ランダムで決定した要素にする
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
				// 崩落できない（未出現の場合はそのまま次の要素を確認する
				if (tile->GetScale().x > 0.0f)
				{
					crumble++;
					// 規定数同時に崩落させる
					if( crumble >= TILE_SAME_CRUMBLE )break;
				}
			}
			if (count >= m_listChildObject.size()) break;

			it++;
			count++;
		}
	}
}
