#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHitObject.h												*/
/*  @brief		:	当たり判定オブジェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\cSpriteObject.h"

//================================================================================================
// 当たり判定オブジェクトクラス
class cHitObject : public cSpriteObject
{
public:
	cHitObject(IBaseObject* parent,const std::string object_name,const std::string graphic_file_name);
	~cHitObject(void);
	
	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// 当たり判定区分
	enum HitCategory {
		HIT_NONE = 0,
		HIT_PLAYER,
		HIT_ENEMY,
	};
	// オブジェクトの状態
	enum State {
		STATE_NORMAL = 0,	// 通常状態(当たり判定あり)
		STATE_FLASH,		// 無敵での点滅状態(当たり判定なし）
		STATE_HIT,			// 当たっていて無敵状態(当たり判定なし)
		STATE_DEAD			// 死亡中(当たり判定なし)
	};

	// 当たり判定処理
	bool CheckHitObject( cHitObject& obj );

	inline void  SetHp(int Hp) { m_nHp = Hp; };
	inline void  GetMaxHp(int Hp) { m_nMaxHp = Hp; }
	inline void  SetAtk(int Atk) { m_nAtk = Atk; };
	inline void  SetHitRange(float Range) { m_fHitRange = Range; };
	inline void  SetHitCate(HitCategory cate) { m_eHitCate = cate; };
	inline void  SetState(State state) { m_eState = state; };
	inline void  SetAreaOutAdjust(int adjust) { m_nAreaOutAdjust = adjust; };

	inline int   GetHp(void) { return m_nHp; };
	inline int   GetMaxHp(void) { return m_nMaxHp; }
	inline int   GetAtk(void) { return m_nAtk; } ;
	inline float GetHitRange(void) { return m_fHitRange; };
	inline HitCategory GetHitCate(void) { return m_eHitCate; };
	inline State GetState(void) { return m_eState; };
	inline int	 GetAreaOutAdjust(void) { return m_nAreaOutAdjust; };

protected:
	// エリアアウト処理、特定方向にエリアアウトした場合にオブジェクトを消したい場合に使用すること
	// 左エリアアウト時の処理
	void		 AreaOutLeftProc(void);
	// 上エリアアウト時の処理
	void		 AreaOutUpProc(void);
	// 右エリアアウト時の処理
	void		 AreaOutRightProc(void);
	// 下エリアアウト時の処理
	void		 AreaOutBottomProc(void);
	// 全方向エリアアウト時の処理
	void		 AreaOutAllProc(void);

	// HP
	int			m_nHp;
	// 最大HP
	int			m_nMaxHp;
	// 攻撃力
	int			m_nAtk;
	// 当たり判定区分
	HitCategory m_eHitCate;
	// 当たり判定の大きさ(半径)
	float		m_fHitRange;
	// オブジェクトの状態
	State		m_eState;
	// エリアアウト許容値
	int			m_nAreaOutAdjust;

#ifdef DEBUG
	cSpriteObject* m_pDebugHitObj;
#endif
};
//================================================================================================