/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingLaserTale.cpp										*/
/*  @brief		:	ホーミングレーザー(尾ひれ付)クラス							*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/211													*/
/*																				*/
/*==============================================================================*/

#include "cHomingLaserTale.h"
#include "..\..\cBulletManager.h"
#include "..\..\..\Effect\cEffectManager.h"

//==========================================================================================
// 定数
const float cHomingLaserTale::HIT_RANGE = 6.0f;	// 当たり判定の大きさ
const int cHomingLaserTale::PRIORITY = 300;		// 表示優先度
const int cHomingLaserTale::NEXT_LASER_TIME = 5;// 次レーザーのポップ時間初期値
const int cHomingLaserTale::DEFAULT_ATK = 50;	// デフォルト攻撃力

//==========================================================================================
// コンストラクタ
//==========================================================================================
cHomingLaserTale::cHomingLaserTale(IBaseObject * parent)
	: cHomingBullet(parent, "HomingLaserTale", "data\\graphic\\Bullet_04.png"),
	m_nNextPopTime(NEXT_LASER_TIME),
	m_nLaserLifeTime(0),
	m_nLaserNum(0)
{
}

cHomingLaserTale::cHomingLaserTale(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cHomingBullet(parent, "HomingLaserTale", filename),
	m_nNextPopTime(NEXT_LASER_TIME),
	m_nLaserLifeTime(0),
	m_nLaserNum(0)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cHomingLaserTale::~cHomingLaserTale(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cHomingLaserTale::Initialize(void)
{
	cHomingBullet::Initialize();

	m_listHistory.clear();
	m_listTaleCreateTime.clear();
	m_nNextPopTime = NEXT_LASER_TIME;

	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	m_vPosUp.x = 0;
	m_vPosUp.y = 0;

	SetPriority(PRIORITY);

}

//==========================================================================================
// 更新
//==========================================================================================
void cHomingLaserTale::Update(void)
{
	HitProc();

	// オブジェクトが死亡状態だったら移動処理をしないようにする
	if (m_eState == STATE_DEAD)
	{
		// 子がいない時に当たったらそのまま削除
		if (m_listChildObject.empty() && m_eState == STATE_DEAD){
			m_eObjectState = OBJECT_STATE_DEAD;
			return;
		}

		// 停止して見えない状態にしておく
		m_bVisible = false;
		m_vPosUp.x = m_vPosUp.y = m_fSpeed = 0.0f;

		// エリア外または子がいる時はオブジェクトを消さない。
		m_eObjectState = OBJECT_STATE_ACTIVE;
	}

	cHomingBullet::Update();

	// 移動履歴の保存
	SaveHistory();

	// レーザーの尾の移動
	if (MoveLaserTale())
	{
		// 全ての子がいなくなったタイミングでオブジェクトを削除する
		if (m_listChildObject.empty())
		{
			m_eObjectState = OBJECT_STATE_DEAD;
			return;
		}
	}

	// 最大数を越えたら最古履歴を削除
	// 最大数はレーザー生成数＊レーザー生成間隔
	if (m_listHistory.size() > m_nNextPopTime * m_nLaserNum)
		m_listHistory.erase(m_listHistory.begin());

	// 次レーザーの尾生成
	CreateLaserTale();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cHomingLaserTale::Finalize(void)
{
	cHomingBullet::Finalize();

	return this;
}
//==========================================================================================
// 移動履歴の保存
//==========================================================================================
void cHomingLaserTale::SaveHistory(void)
{
	History vh;
	vh.vPos = m_vPos;
	vh.fAngle = m_fAngle;
	m_listHistory.push_back(vh);
}
//==========================================================================================
// レーザーの尾移動
// return : 削除したレーザーがある場合はtrue
//==========================================================================================
bool cHomingLaserTale::MoveLaserTale(void)
{
	int i = 0;
	for (auto it = m_listChildObject.begin(); it != m_listChildObject.end();it++, i++)
	{
		cSpriteObject* obj = (cSpriteObject*)(*it);
		History hs = m_listHistory[m_listHistory.size() - 1 - m_listTaleCreateTime[i]];
		obj->SetPos(hs.vPos);
		obj->SetAngle(hs.fAngle);

		if (hs.vPos.x == m_vPos.x && hs.vPos.y == m_vPos.y)
		{
			cEffectObject* ef = cEffectManager::GetInstance().Create(EFFECT_HIT, obj->GetPos());
			ef->SetDrawColor(obj->GetDrawColor());

			// レーザーの尾の削除
			obj->Finalize();
			SAFE_DELETE(obj);
			it = m_listChildObject.erase(it);
			m_listTaleCreateTime.erase(m_listTaleCreateTime.begin() + i);

			return true;
		}
	}
	return false;
}
//==========================================================================================
// レーザーの尾生成
//==========================================================================================
void cHomingLaserTale::CreateLaserTale(void)
{
	m_nLaserLifeTime++;
	// 一定時間が経過したら次レーザーの尾を生成する
	if (m_nLaserLifeTime % m_nNextPopTime == m_nNextPopTime -1 && m_nLaserNum * m_nNextPopTime > m_nLaserLifeTime)
	{
		// 何フレーム目で生成されたかを記憶する
		m_listTaleCreateTime.push_back((unsigned int)m_nLaserLifeTime);

		// レーザーの尾の画像を生成
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"LaserTale" + m_listTaleCreateTime.size(),m_sFileName);
		obj->SetDrawColor(m_nColor);
		// 生成時間からどの位置の履歴を使用して位置をセットするかを決定する
		obj->SetPos(m_listHistory[m_listHistory.size() - m_nLaserLifeTime].vPos);
		obj->SetAngle(m_listHistory[m_listHistory.size() - m_nLaserLifeTime].fAngle);
		obj->SetPriority(GetPriority());
	}
}
