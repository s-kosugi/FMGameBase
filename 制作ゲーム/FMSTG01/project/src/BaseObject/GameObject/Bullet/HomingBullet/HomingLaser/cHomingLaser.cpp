/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingLaser.cpp											*/
/*  @brief		:	ホーミングレーザークラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "cHomingLaser.h"
#include "..\..\cBulletManager.h"

//==========================================================================================
// 定数
//==========================================================================================
const float cHomingLaser::HIT_RANGE = 6.0f;		// 当たり判定の大きさ
const int cHomingLaser::PRIORITY = 300;			// 表示優先度
const int cHomingLaser::NEXT_LASER_TIME = 5;	// 次レーザーのポップ時間初期値
const int cHomingLaser::DEFAULT_ATK = 50;		// デフォルト攻撃力

//==========================================================================================
// コンストラクタ
//==========================================================================================
cHomingLaser::cHomingLaser(IBaseObject * parent)
	: cHomingBullet(parent, "HomingLaser", "data\\graphic\\Bullet_04.png"),
	m_pPrevLaser( nullptr ),
	m_nNextPopTime(NEXT_LASER_TIME),
	m_nLaserLifeTime(0),
	m_nLaserNum(0)
{
}

cHomingLaser::cHomingLaser(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cHomingBullet(parent, "HomingLaser", filename),
	m_pPrevLaser(nullptr),
	m_nNextPopTime(NEXT_LASER_TIME),
	m_nLaserLifeTime(0),
	m_nLaserNum(0)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cHomingLaser::~cHomingLaser(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cHomingLaser::Initialize(void)
{
	m_listVectorHistory.clear();
	m_nNextPopTime = NEXT_LASER_TIME;

	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	m_vPosUp.x = 0;
	m_vPosUp.y = 0;

	SetPriority(PRIORITY);

	cHomingBullet::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cHomingLaser::Update(void)
{
	if(!IsSearchPrevLaserAlive() ) m_pPrevLaser = nullptr;

	if (m_pPrevLaser == nullptr)
	{
		// 先頭レーザーは通常のホーミング弾と同じ動きをする
		cHomingBullet::Update();

		// 移動履歴の保存
		VectorHistory vh;
		vh.vPos = m_vPos;
		vh.vPosUp = m_vPosUp;
		m_listVectorHistory.push_back(vh);
	}
	else
	{
		// 前レーザーの動きに追従させる
		VectorHistory vh = m_pPrevLaser->GetVectorHistory();
		m_vPos = vh.vPos;
		m_vPosUp = vh.vPosUp;
		m_listVectorHistory.push_back(vh);

		// 移動後の表示角度設定処理
		RotateMoveAfter();

		// ベースクラスを通らない為子レーザーは自分で削除処理をする
		m_nLifeTime--;
		if (m_nLifeTime <= 0) m_eObjectState = OBJECT_STATE_DEAD;

		// エリアアウトをしたら弾を消す
		AreaOutAllProc();
	}
	// 最大数を越えたら最古履歴を削除
	// 最大数はレーザー出現フレームと等しい
	if (m_listVectorHistory.size() > m_nNextPopTime)
		m_listVectorHistory.erase(m_listVectorHistory.begin());

	// 次レーザーの生成
	CreateNextLaser();	
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cHomingLaser::Finalize(void)
{
	cHomingBullet::Finalize();

	return this;
}

//==========================================================================================
// 前レーザーが生きているかどうかを調べる
//==========================================================================================
bool cHomingLaser::IsSearchPrevLaserAlive(void)
{
	for (auto it = cBulletManager::GetInstance().GetChildList()->begin(); it != cBulletManager::GetInstance().GetChildList()->end(); it++)
	{
		if ((cSpriteObject*)m_pPrevLaser == (cSpriteObject*)*it) return true;
	}

	return false;
}
//==========================================================================================
// 次レーザーの生成
//==========================================================================================
void cHomingLaser::CreateNextLaser(void)
{
	m_nLaserLifeTime++;
	// 一定時間が経過したら次レーザーを生成する
	if (m_nLaserLifeTime == m_nNextPopTime && m_nLaserNum > 0)
	{
		m_nLaserNum--;
		VectorHistory vh = m_listVectorHistory[m_listVectorHistory.size() - 1];
		cHomingLaser* bul = (cHomingLaser*)cBulletManager::GetInstance().Create(
			BT_HOMING_LASER, vh.vPos, HIT_PLAYER, m_fSpeed);
		bul->SetDrawColor(m_nColor);
		bul->SetPosUp(vh.vPosUp);
		bul->SetRotLimit(m_fRotLimit);
		bul->SetPrevLaserPointer(this);
		bul->SetLaserNum(m_nLaserNum);
		bul->SetNextPopTime(m_nNextPopTime);
		bul->SetAreaOutAdjust( m_nAreaOutAdjust );
	}
}
