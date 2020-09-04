#include "Easing.h"
#include "..\utility.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Easing
{
	float InQuad( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime;
		return max * t*t + min;
	}
	float OutQuad( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime;
		return -max * t*( t - 2.0f ) + min;
	}
	float InOutQuad( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime / 2.0f;
		if ( t < 1.0f)
			return max / 2.0f * t * t + min;
		--t;
		return -max / 2.0f * ( t * ( t - 2.0f ) - 1.0f ) + min;
	}
	float InCubic( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime;
		return max * t*t*t + min;
	}
	float OutCubic( float t , float totaltime , float max , float min )
	{
		max -= min;
		t = t / totaltime - 1.0f;
		return max * ( t*t*t + 1.0f ) + min;
	}
	float InOutCubic( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime / 2.0f;
		if ( t < 1.0f )
			return max / 2.0f * t*t*t + min;
		t -= 2.0f;
		return max / 2.0f * ( t*t*t + 2.0f ) + min;
	}
	float InQuart( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime;
		return max * t*t*t*t + min;
	}
	float OutQuart( float t , float totaltime , float max , float min )
	{
		max -= min;
		t = t / totaltime - 1.0f;
		return -max * ( t*t*t*t - 1.0f ) + min;
	}
	float InOutQuart( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime / 2.0f;
		if ( t < 1.0f )
			return max / 2.0f * t*t*t*t + min;
		t -= 2.0f;
		return -max / 2.0f * ( t*t*t*t - 2.0f ) + min;
	}
	float InQuint( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime;
		return max * t*t*t*t*t + min;
	}
	float OutQuint( float t , float totaltime , float max , float min )
	{
		max -= min;
		t = t / totaltime - 1.0f;
		return max * ( t*t*t*t*t + 1.0f ) + min;
	}
	float InOutQuint( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime / 2.0f;
		if ( t < 1.0f )
			return max / 2.0f * t*t*t*t*t + min;
		t -= 2.0f;
		return max / 2.0f * ( t*t*t*t*t + 2.0f ) + min;
	}
	float InSine( float t , float totaltime , float max , float min )
	{
		max -= min;
		return -max * cosf( ( t*DEG_TO_RAD( 90 ) ) / totaltime ) + max + min;
	}
	float OutSine( float t , float totaltime , float max , float min )
	{
		max -= min;
		return max * sinf( ( t*DEG_TO_RAD( 90 ) ) / totaltime ) + min;
	}
	float InOutSine( float t , float totaltime , float max , float min )
	{
		max -= min;
		return -max / 2.0f * ( cosf( t* (float)M_PI / totaltime ) - 1.0f ) + min;
	}
	float InExp( float t , float totaltime , float max , float min )
	{
		max -= min;
		return t == 0.0f ? min : max * powf( 2.0f , 10.0f * ( t / totaltime - 1.0f ) ) + min;
	}
	float OutExp( float t , float totaltime , float max , float min )
	{
		max -= min;
		return t == totaltime ? max + min : max * ( -powf( 2.0f , -10.0f * t / totaltime ) + 1.0f ) + min;
	}
	float InOutExp( float t , float totaltime , float max , float min )
	{
		if ( t == 0.0f ) return min;
		if ( t == totaltime ) return max;
		max -= min;
		t /= totaltime / 2.0f;

		if ( t < 1.0f ) return max / 2.0f * powf( 2.0f , 10.0f * ( t - 1.0f ) ) + min;
		--t;
		return max / 2.0f * ( -powf( 2.0f , -10.0f * t ) + 2.0f ) + min;

	}
	float InCirc( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime;
		return -max * ( sqrtf( 1.0f - t * t ) - 1.0f ) + min;
	}
	float OutCirc( float t , float totaltime , float max , float min )
	{
		max -= min;
		t = t / totaltime - 1.0f;
		return max * sqrtf( 1.0f - t * t ) + min;
	}
	float InOutCirc( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime / 2.0f;
		if ( t < 1.0f ) return -max / 2.0f * ( sqrtf( 1.0f - t * t ) - 1.0f ) + min;
		t -= 2.0f;
		return max / 2.0f * ( sqrtf( 1.0f - t * t ) + 1.0f ) + min;
	}
	float InBack( float t , float totaltime , float max , float min , float s )
	{
		max -= min;
		t /= totaltime;
		return max * t*t*( ( s + 1.0f )*t - s ) + min;
	}
	float OutBack( float t , float totaltime , float max , float min , float s )
	{
		max -= min;
		t = t / totaltime - 1.0f;
		return max * ( t*t* ( ( s + 1.0f ) * t + s ) + 1.0f) + min;
	}
	float InOutBack( float t , float totaltime , float max , float min , float s )
	{
		max -= min;
		s *= 1.525f;
		t /= totaltime / 2.0f;
		if ( t < 1.0f ) return max / 2.0f * ( t*t*( ( s + 1.0f )*t - s ) ) + min;
		t -= 2.0f;
		return max / 2.0f * ( t*t*( ( s + 1.0f )*t + s ) + 2.0f ) + min;
	}
	float OutBounce( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime;

		if ( t < 1.0f / 2.75f )
			return max * ( 7.5625f*t*t ) + min;
		else if ( t < 2.0f / 2.75f )
		{
			t -= 1.5f / 2.75f;
			return max * ( 7.5625f*t*t + 0.75f ) + min;
		}
		else if ( t < 2.5f / 2.75f )
		{
			t -= 2.25f / 2.75f;
			return max * ( 7.5625f*t*t + 0.9375f ) + min;
		}
		else
		{
			t -= 2.625f / 2.75f;
			return max * ( 7.5625f*t*t + 0.984375f ) + min;
		}
	}
	float InBounce( float t , float totaltime , float max , float min )
	{
		max -= min;
		t /= totaltime;
		return max * powf( 2.0f , 6.0f * ( t - 1.0f ) ) * fabsf( sinf( t * (float)M_PI * 3.5f ) ) + min;
	}
	float InOutBounce( float t , float totaltime , float max , float min )
	{
		max -= min;

		t /= totaltime;

		if ( t < 0.5f )
			return max * 8.0f * powf( 2.0f , 8.0f * ( t - 1.0f ) ) * fabsf( sinf( t * (float)M_PI * 7.0f ) ) + min;
		else
			return max * ( 1.0f - 8.0f * powf( 2.0f , -8.0f * t ) * fabsf( sinf( t * (float)M_PI * 7.0f ) ) ) + min;
	}
	float Linear( float t , float totaltime , float max , float min )
	{
		return ( max - min )*t / totaltime + min;
	}
}