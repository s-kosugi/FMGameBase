/*==============================================================================*/
/*																				*/
/*	@file title	:	cCamera.cpp													*/
/*  @brief		:	カメラクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/05/22													*/
/*																				*/
/*==============================================================================*/
#include "cCamera.h"


//==========================================================================================
//  初期化
//==========================================================================================
void cCamera::Initialize(void)
{
	m_vPos = { 0, 10,-20 };
	m_vTargetPos = { 0, 10,0 };


	//奥行0.1〜1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);
}

//==========================================================================================
//  更新
//==========================================================================================
void cCamera::Update(void)
{


	//第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(m_vPos.x, m_vPos.y, m_vPos.z), VGet(m_vTargetPos.x, m_vTargetPos.y, m_vTargetPos.z));
}

//==========================================================================================
// カメラの回転
// 現在の位置から注視点を基準に回転した位置にカメラを変更する
//==========================================================================================
void cCamera::RotateHorizon(float angle)
{
	float ox = m_vPos.x - m_vTargetPos.x;
	float oy = m_vPos.z - m_vTargetPos.z;

	m_vPos.x = (float)(ox * cos(angle) + oy * sin(angle));
	m_vPos.z = (float)(-ox * sin(angle) + oy * cos(angle));
	m_vPos.x += m_vTargetPos.x;
	m_vPos.z += m_vTargetPos.z;
}
