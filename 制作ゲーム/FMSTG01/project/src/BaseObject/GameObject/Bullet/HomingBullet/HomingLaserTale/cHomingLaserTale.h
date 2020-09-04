#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingLaserTale.h											*/
/*  @brief		:	ホーミングレーザー(尾ひれ付)クラス							*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/11													*/
/*																				*/
/*==============================================================================*/

#include "..\cHomingBullet.h"
#include <vector>

//================================================================================================
// ホーミングレーザー(尾ひれ付)クラス
class cHomingLaserTale : public cHomingBullet
{
public:
	cHomingLaserTale(IBaseObject* parent);
	cHomingLaserTale(IBaseObject* parent, const std::string& name, const std::string& filename);
	~cHomingLaserTale(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// レーザー移動履歴
	struct History {
		cVector2 vPos;
		float	  fAngle;
	};

	// レーザーオブジェクトの出現数を設定
	inline void SetLaserNum(unsigned int num) { m_nLaserNum = num; };

	// 次レーザーの出現時間
	inline void SetNextPopTime(unsigned int time) { m_nNextPopTime = time; };
private:
	// 移動履歴の保存
	void SaveHistory( void );

	// レーザーの尾移動
	// return : 削除したレーザーがある場合はtrue
	bool MoveLaserTale(void);

	// レーザーの尾生成
	void CreateLaserTale(void);

	// 移動座標保存領域
	std::vector<History> m_listHistory;
	// レーザーの尾生成時間記憶領域
	std::vector<unsigned int> m_listTaleCreateTime;

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