#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cVector2.h													*/
/*  @brief		:	�Q�����x�N�g���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/04													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <math.h>
#include "..\utility.h"

//================================================================================================
// �x�N�g���N���X
class cVector2
{
public:
	float	x;
	float	y;


	cVector2(void);
	cVector2(float x, float y);
	cVector2(const cVector2& v);
	cVector2(const POINT& p);
	~cVector2();

	// �x�N�g���̑傫���擾
	static inline float Length(const cVector2& vec, const cVector2& tvec) { return CalcTwoPointDist(vec, tvec); };
	inline float Length(const cVector2& vec) { return CalcTwoPointDist(vec); };

	// 2�_�Ԃ̋���
	// pos , tpos ���߂����Q�_��
	// return : ����
	static inline float CalcTwoPointDist(const cVector2& vec, const cVector2& tvec) { return (float)sqrtf((tvec.x - vec.x) * (tvec.x - vec.x) + (tvec.y - vec.y) * (tvec.y - vec.y)) ;};

	// 2�_�Ԃ̋���
	// pos : ���߂����Ώۂ̈ʒu
	// return : ����
	inline float CalcTwoPointDist(const cVector2& vec) { return (float)sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y)) ;};
	
	// 2�_�Ԃ̊p�x
	// pos , tpos ���߂����Q�_��
	// return : Degree�l
	float CalcTwoPointAngle(const cVector2& vec, const cVector2& tvec);

	// 2�_�Ԃ̊p�x(���g�̈ʒu�Ƃ̍�)
	// pos : ���߂����Ώۂ̈ʒu
	// return : Degree�l
	float CalcTwoPointAngle(const cVector2& vec);

	// ����
	// pos , tpos ���ς����߂�Q�̃x�N�g��
	inline float DotProduct(const cVector2& vec, const cVector2& tvec) { return vec.x * tvec.x + vec.y * tvec.y;};

	// ����
	// pos : ���g�Ɠ��ς����߂�x�N�g��
	inline float DotProduct(const cVector2 & vec) { return vec.x * x + vec.y * y; };

	// ���K��
	inline void Normalize( void ){ x *= 1.0f / sqrtf( x * x + y * y ); y *= 1.0f / sqrtf( x * x + y * y ); };

	//------------------------------------------------------------------------------------
	// �I�y���[�^�[�I�[�o�[���[�h

	// ���
	inline  cVector2&   operator=(const cVector2& v)
	{
		x = v.x; y = v.y;
		return *this;
	};
	// ���Z
	inline  cVector2&   operator+=(const cVector2& v)
	{
		x += v.x; y += v.y;
		return *this;
	};
	// ���Z
	inline  cVector2&   operator-=(const cVector2& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	};
	// ��Z(�X�J���[�{)
	inline  cVector2&	operator*=(float scalar)
	{
		x *= scalar; y *= scalar;
		return *this;
	};
	inline	bool		operator==(cVector2 v) const { return (x == v.x && y == v.y); };	// ����
	inline	bool		operator!=(cVector2 v) const { return (x != v.x && y != v.y); };	// �s��
	// ���Z
	inline	cVector2	operator+(const cVector2& v) {
		cVector2 ret;
		ret.x = x + v.x; ret.y = y + v.y;
		return ret;
	};
	// ���Z
	inline	cVector2	operator-(const cVector2& v) {
		cVector2 ret;
		ret.x = x - v.x; ret.y = y - v.y;
		return ret;
	};
	// ��Z
	inline	cVector2	operator*(const cVector2& v) {
		cVector2 ret;
		ret.x = x * v.x; ret.y = y * v.y;
		return ret;
	};
	// ��Z(�X�J���[�{)
	inline	cVector2	operator*(float scalar) {
		cVector2 ret;
		ret.x = x * scalar; ret.y = y * scalar;
		return ret;
	};
	// ���Z
	inline	cVector2	operator/(const cVector2& v) {
		cVector2 ret;
		ret.x = x / v.x; ret.y = y / v.y;
		return ret;
	};
	// ���Z(�X�J���[)
	inline	cVector2	operator/(float scalar) {
		cVector2 ret;
		ret.x = x / scalar; ret.y = y / scalar;
		return ret;
	};
	// ������
	inline	cVector2	operator-(void) {
		return cVector2(-x, -y);
	};

	// �L���X�g���Z�q
	// DXLib�p�̃x�N�g���\���̂ɃL���X�g����
	operator VECTOR() const { return VECTOR{ x,y,0.0f }; };

	//------------------------------------------------------------------------------------
};