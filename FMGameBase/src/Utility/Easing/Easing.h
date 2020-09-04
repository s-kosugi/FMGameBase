#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	Easing.h													*/
/*  @brief		:	イージング関数												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/16													*/
/*																				*/
/*==============================================================================*/

namespace Easing
{
	enum class Type
	{
		INQUAD,
		OUTQUAD,
		INOUTQUAD,
		INCUBIC,
		OUTCUBIC,
		INOUTCUBIC,
		INQUART,
		OUTQUART,
		INOUTQUART,
		INQUINT,
		OUTQUINT,
		INOUTQUINT,
		INSINE,
		OUTSINE,
		INOUTSINE,
		INEXP,
		OUTEXP,
		INOUTEXP,
		INCIRC,
		OUTCIRC,
		INOUTCIRC,
		INBACK,
		OUTBACK,
		INOUTBACK,
		OUTBOUNCE,
		INBOUNCE,
		INOUTBOUNCE,
		LINEAR,

		MAX,
	};
	// t : 現在の経過時間
	// totaltime : 最大値にたどり着くまでの時間
	// max : イージング関数返す値の最大値
	// min : 返す値の最小値
	float InQuad(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float OutQuad(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InOutQuad(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InCubic(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float OutCubic(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InOutCubic(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InQuart(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float OutQuart(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InOutQuart(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InQuint(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float OutQuint(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InOutQuint(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InSine(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float OutSine(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InOutSine(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InExp(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float OutExp(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InOutExp(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InCirc(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float OutCirc(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InOutCirc(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InBack(float t, float totaltime , float max = 1.0f, float min = 0.0f, float s = 0.5f);
	float OutBack(float t, float totaltime, float max = 1.0f, float min = 0.0f, float s = 0.5f);
	float InOutBack(float t, float totaltime, float max = 1.0f, float min = 0.0f, float s = 0.5f);
	float OutBounce(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InBounce(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float InOutBounce(float t, float totaltime, float max = 1.0f, float min = 0.0f);
	float Linear(float t, float totaltime, float max = 1.0f, float min = 0.0f);
}