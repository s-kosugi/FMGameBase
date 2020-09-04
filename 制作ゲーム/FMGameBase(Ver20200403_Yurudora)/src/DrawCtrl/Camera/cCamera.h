#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cCamera.h													*/
/*  @brief		:	カメラクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/05/22													*/
/*																				*/
/*==============================================================================*/

#include "DxLib.h"
#include "BaseObject\IBaseObject.h"
#include "Utility/Vector/cVector3.h"

//===============================================================================
// カメラクラス
class cCamera : public IBaseObject
{
public:

	void Initialize(void);
	void Update(void);

	// カメラの回転
	// 現在の位置から注視点を基準に水平回転した位置にカメラを変更する
	void RotateHorizon( float angle );

	//-----------------------------------------------------------------------------------------
	// Getter
	//-----------------------------------------------------------------------------------------



	//-----------------------------------------------------------------------------------------
	// Setter
	//-----------------------------------------------------------------------------------------

private:

	//-----------------------------------------------------------------------------------------
	// 変数
	//-----------------------------------------------------------------------------------------

	// カメラ座標
	cVector3	m_vPos;

	// 注視点
	cVector3	m_vTargetPos;

	//-----------------------------------------------------------------------------------------
	// 定数
	//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cCamera(void) { };     //  他からの生成を禁止
	cCamera(IBaseObject* parent) {  };
	cCamera(IBaseObject* parent, const std::string& name) { };
	~cCamera(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cCamera(const cCamera& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cCamera& operator = (const cCamera& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cCamera& GetInstance(void) {
		static cCamera instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
//-----------------------------------------------------------------------------------------------------
};