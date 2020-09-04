#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingLaser.h												*/
/*  @brief		:	ホーミングレーザークラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "..\cHomingBullet.h"
#include <vector>

//================================================================================================
// ホーミングレーザークラス
class cHomingLaser : public cHomingBullet
{
public:
	cHomingLaser(IBaseObject* parent);
	cHomingLaser(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cHomingLaser(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// レーザー移動履歴
	struct VectorHistory {
		cVector2 vPos;
		cVector2 vPosUp;
	};

	// レーザーの移動履歴を取得
	inline VectorHistory GetVectorHistory(void) { return (VectorHistory)(*m_listVectorHistory.begin()); };

	// 前レーザーのポインタをセット
	inline void SetPrevLaserPointer(cHomingLaser* pObj) { m_pPrevLaser = pObj; };

	// レーザーオブジェクトの出現数を設定
	inline void SetLaserNum(unsigned int num) { m_nLaserNum = num ;};

	// 次レーザーの出現時間
	inline void SetNextPopTime(unsigned int time) { m_nNextPopTime = time; };
private:

	// 前レーザーが生きているかどうかを調べる
	bool IsSearchPrevLaserAlive(void);

	// 次レーザーの生成
	void CreateNextLaser( void );
	


	// 1つ前のレーザーへのポインタ
	cHomingLaser* m_pPrevLaser;
	// 移動座標保存領域
	std::vector<VectorHistory> m_listVectorHistory;

	// 次レーザーの出現時間
	unsigned short m_nNextPopTime;

	// レーザーの生存タイマー
	unsigned int m_nLaserLifeTime;

	// ホーミングレーザーの残数
	unsigned int m_nLaserNum;

	//-------------------------------------------------------------------------------------------
	// 定数
	static const float HIT_RANGE;		// 当たり判定の大きさ
	static const int PRIORITY;			// 表示優先度
	static const int NEXT_LASER_TIME;	// 次レーザーのポップ時間初期値
	static const int DEFAULT_ATK;		// デフォルト攻撃力
};
//================================================================================================